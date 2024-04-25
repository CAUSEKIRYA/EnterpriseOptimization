#define DEBUG_MODE 1
#include "program_defs.h"

#include "optimizationresultsdialog.h"
#include "ui_optimizationresultsdialog.h"
#include "dbviewwidget.h"
#include "matrix.h"
#include "optmethods/optimizationobjectstorage.h"
#include "optmethods/optimizationthread.h"
#include "matrixview.h"

#include <QMessageBox>

OptimizationResultsDialog::OptimizationResultsDialog(DBViewWidget *db, QWidget *parent) :
    QDialog(parent),
    dbViewWidget(db),
    method(nullptr),
    integerMethod(nullptr),
    input(nullptr),
    output(nullptr),
    function(nullptr),
    result(nullptr),
    ui(new Ui::OptimizationResultsDialog)
{
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui->setupUi(this);
}

OptimizationResultsDialog::~OptimizationResultsDialog()
{
    delete input;
    delete output;
    delete function;
    delete ui;
}

void OptimizationResultsDialog::finishCalculation()
{
    if (integerMethod != nullptr)
    {
        disconnect(integerMethod, SIGNAL(completedBy(int)), ui->progressBar, SLOT(setValue(int)));
        disconnect(integerMethod, SIGNAL(calculationFinished()), this, SLOT(finishCalculation()));

        result = integerMethod->getResult();
    }

    DBG("Result:\n" << result->toString());

    MatrixView *model = new MatrixView(*result, this);
    model->setHeaderData(0, Qt::Horizontal, tr("Results"), Qt::DisplayRole);
    ui->resultsView->setModel(model);

    delete input; input = nullptr;
    delete output; output = nullptr;
    delete function; function = nullptr;

    integerMethod = nullptr;
    method = nullptr;

    ui->closeButton->setEnabled(true);
}

void OptimizationResultsDialog::calculateInteger()
{
    disconnect(method, SIGNAL(completedBy(int)), ui->progressBar, SLOT(setValue(int)));
    disconnect(method, SIGNAL(calculationFinished()), this, SLOT(calculateInteger()));

    result = method->getResult();

    if (integerMethod != nullptr)
    {
        connect(integerMethod, SIGNAL(completedBy(int)), ui->progressBar, SLOT(setValue(int)));
        connect(integerMethod, SIGNAL(calculationFinished()), this, SLOT(finishCalculation()));

        integerMethod->init(input, output, function, result);
        integerMethod->setBounds(50, 100);
        integerMethod->start();
    }
    else finishCalculation();
}

void OptimizationResultsDialog::calculateAndShow(QString* optMethod, QString* integerMethod)
{
    ui->closeButton->setEnabled(false);

    DBG("Using \"" << *optMethod << "\" method");
    DBG("Integer values: " << (integerMethod != nullptr ? "true (method " + *integerMethod + ")" : "false"));

    QPair<int, int> size = dbViewWidget->valuesSizes();

    input = new Matrix(size.first, size.second);
    output = new Matrix(size.first, 1);
    function = new Matrix(1, size.second);

    if (bool ok = dbViewWidget->formValuesFromDb(input, output, function))
    {
        ui->progressBar->setValue(0);
        show();

        this->method = OptimizationObjectStorage::indexes[*optMethod];
        this->integerMethod = (integerMethod == nullptr ? nullptr : OptimizationObjectStorage::indexes[*integerMethod]);

        connect(method, SIGNAL(completedBy(int)), ui->progressBar, SLOT(setValue(int)));
        connect(method, SIGNAL(calculationFinished()), this, SLOT(calculateInteger()));

        method->init(input, output, function);
        method->setBounds(0, integerMethod != nullptr ? 50 : 100);
        method->start();
    }
    else
    {
        QMessageBox msg(QMessageBox::Critical, tr("Calculation error"), tr("Could not obtain values from database"), QMessageBox::Ok, this);
        msg.exec();
    }

    delete optMethod;
    delete integerMethod;
}
