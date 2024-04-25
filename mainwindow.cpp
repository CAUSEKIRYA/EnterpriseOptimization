#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appsettings.h"
#include "dbviewwidget.h"
#include "settingsdialog.h"
#include "optimizationresultsdialog.h"
#include "optmethods/optimizationthread.h"
#include "optmethods/optimizationobjectstorage.h"

#define DEBUG_MODE 1
#include "program_defs.h"

#include <QWindowStateChangeEvent>
#include <QVBoxLayout>
#include <QSet>

MainWindow::MainWindow()
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
{
    QStringList optMethods, integerMethods;

    for (auto& key : OptimizationObjectStorage::indexes.keys())
    {
        OptimizationType t = OptimizationObjectStorage::indexes[key]->getType();
        if (t == OptimizationType::Generic)
        {
            optMethods.append(key);
        }
        else if (t == OptimizationType::Integer)
        {
            integerMethods.append(key);
        }
    }

    ui->setupUi(this);

    ui->optMethod->addItems(optMethods);
    ui->integerMethod->addItems(integerMethods);

    viewWidgetLayout = new QVBoxLayout(ui->viewWidget);
    viewWidgetLayout->setMargin(0);

    dbView = new DBViewWidget(this, ui->viewWidget);
    viewWidgetLayout->addWidget(dbView);
    connect(ui->loadDbButton, SIGNAL(clicked()), dbView, SLOT(openLoadDialog()));
    connect(ui->refreshButton, SIGNAL(clicked()), dbView, SLOT(refreshDb()));
    connect(ui->disconnectButton, SIGNAL(clicked()), dbView, SLOT(disconnectFromDb()));

    sw = new SettingsDialog(this);
    connect(ui->actionSettings, SIGNAL(triggered()), sw, SLOT(show()));

    optRes = new OptimizationResultsDialog(dbView, this);
    connect(ui->optimizeButton, SIGNAL(clicked()), this, SLOT(onOptimizeClicked()));
    connect(this, SIGNAL(passOptimizationParameters(QString*, QString*)), optRes, SLOT(calculateAndShow(QString*, QString*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    AppSettings* settings = AppSettings::get();
    settings->takeByName("resolutionX") = QString::number(size().width());
    settings->takeByName("resolutionY") = QString::number(size().height());
}

void MainWindow::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::WindowStateChange)
    {
        QWindowStateChangeEvent* event = static_cast< QWindowStateChangeEvent* >( e );

        AppSettings* settings = AppSettings::get();

        if (event->oldState() == Qt::WindowNoState && this->windowState() == Qt::WindowMaximized)
        {
            settings->takeByName("maximized") = "1";
        }
        else if (event->oldState() == Qt::WindowMaximized && this->windowState() == Qt::WindowNoState)
        {
            settings->takeByName("maximized") = "0";
        }
    }

    QMainWindow::changeEvent(e);
}

void MainWindow::enableButtons(bool enabled)
{
    ui->disconnectButton->setEnabled(enabled);
    ui->refreshButton->setEnabled(enabled);
    ui->optimizeButton->setEnabled(enabled);
}

void MainWindow::onOptimizeClicked()
{
    QString* optMethod = new QString(ui->optMethod->currentText());
    QString* integerMethod = (ui->integerCheckbox->isChecked() ? new QString(ui->integerMethod->currentText()) : nullptr);
    emit passOptimizationParameters(optMethod, integerMethod);
}
