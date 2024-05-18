#include "dbviewwidget.h"
#include "ui_dbviewwidget.h"
#include "dbconnectiondialog.h"
#define DEBUG_MODE 1
#include "program_defs.h"
#include "mainwindow.h"
#include "matrix.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QBoxLayout>
#include <QTableView>
#include <QMessageBox>

const QMap<QString, QString> DBViewWidget::availableDrivers = {
    {"MySQL", "QMYSQL"},
    {"PostgresSQL", "QPSQL"},
    {"SQLite", "QSQLITE"},
    {"ODBC-compliant", "QODBC"}
};

DBViewWidget::DBViewWidget(MainWindow* mw, QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::DBViewWidget),
    dbConnectionPtr(nullptr),
    mainWindow(mw),
    tabs(QList<QWidget*>())
{
    ui->setupUi(this);
    connectionDialog = new DBConnectionDialog(this, availableDrivers.keys());
    connect(connectionDialog, SIGNAL(passValues(QMap<QString, QString>*)), this, SLOT(connectToDb(QMap<QString, QString>*)));
    connect(this, SIGNAL(tablesShown(bool)), mainWindow, SLOT(enableButtons(bool)));
}

DBViewWidget::~DBViewWidget()
{
    delete ui;
    disconnectFromDb();
}

void DBViewWidget::openLoadDialog()
{
    connectionDialog->show();
}

void DBViewWidget::clearAllTables()
{
    while (count() > 0)
    {
        removeTab(0);
        delete tabs.takeFirst();
    }
}

void DBViewWidget::refreshDb()
{
    clearAllTables();

    QSqlQuery tables = dbConnectionPtr->exec("SHOW TABLES");
    while (tables.next())
    {
        QString tableName = tables.value(0).toString();
        QWidget* tabWidget = new QWidget(this);
        tabs.append(tabWidget);

        QLayout* tabLayout = new QBoxLayout(QBoxLayout::TopToBottom, tabWidget);
        tabWidget->setLayout(tabLayout);

        QTableView* tableView = new QTableView(tabWidget);
        QSqlTableModel* model = new QSqlTableModel(tabWidget);
        model->setTable(tableName);
        model->setEditStrategy(QSqlTableModel::OnFieldChange);
        model->select();

        tableView->setModel(model);
        tabLayout->addWidget(tableView);

        addTab(tabWidget, tableName);
    }

    emit tablesShown(true);
}

void DBViewWidget::connectToDb(QMap<QString, QString>* values)
{
    disconnectFromDb();

    dbConnectionPtr = new QSqlDatabase(QSqlDatabase::addDatabase(availableDrivers[(*values)["dbms"]]));
    dbConnectionPtr->setHostName((*values)["hostname"]);
    dbConnectionPtr->setUserName((*values)["username"]);
    dbConnectionPtr->setPassword((*values)["password"]);
    dbConnectionPtr->setDatabaseName((*values)["dbname"]);

    if (dbConnectionPtr->open())
    {
        DBG("Database opened successfully.");
        refreshDb();
    }
    else
    {
        QString errorText = dbConnectionPtr->lastError().text();
        DBG("Database didn't open due to following error:");
        DBG(errorText);

        QMessageBox box(QMessageBox::Critical, QObject::tr("DB connection error"), errorText, QMessageBox::Ok, this);
        box.exec();
    }

    delete values;
}

void DBViewWidget::disconnectFromDb()
{
    clearAllTables();

    if (dbConnectionPtr != nullptr)
    {
        if (dbConnectionPtr->isOpen())
        {
            dbConnectionPtr->close();
        }

        delete dbConnectionPtr;
        dbConnectionPtr = nullptr;

        DBG("Previous database connection is closed.");
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    }

    emit tablesShown(false);
}

QPair<int, int> DBViewWidget::valuesSizes() const
{
    int rows, columns;
    {
        QSqlQuery r = dbConnectionPtr->exec("SELECT GetRowsCount()");
        QSqlQuery c = dbConnectionPtr->exec("SELECT GetColumnsCount()");

        r.first();
        rows = r.value(0).toInt();

        c.first();
        columns = c.value(0).toInt();
    }

    return QPair<int, int>(rows, columns);
}

bool DBViewWidget::formValuesFromDb(Matrix *input, Matrix *output, Matrix *function)
{
    // form Input
    dbConnectionPtr->exec("CALL GenerateEntries()");
    {
        QSqlQuery entries = dbConnectionPtr->exec("SELECT * FROM Entries");

        while (entries.next())
        {
            int rowIndex = entries.value(0).toInt() - 1;
            int columnIndex = entries.value(1).toInt() - 1;

            if (rowIndex == -1 || columnIndex == -1) return false;

            double value = entries.value(2).toDouble();
            input->setAt(rowIndex, columnIndex, value);
        }
    }

    // form Output
    dbConnectionPtr->exec("CALL GenerateRestrictions()");
    {
        QSqlQuery restrictions = dbConnectionPtr->exec("SELECT * FROM Restrictions");

        while (restrictions.next())
        {
            int rowIndex = restrictions.value(0).toInt() - 1;

            if (rowIndex == -1) return false;

            double value = restrictions.value(1).toDouble();
            output->setAt(rowIndex, 0, value);
        }
    }

    // form Function
    dbConnectionPtr->exec("CALL GenerateCostFunction()");
    {
        QSqlQuery costFunction = dbConnectionPtr->exec("SELECT * FROM CostFunction");

        while (costFunction.next())
        {
            int columnIndex = costFunction.value(0).toInt() - 1;

            if (columnIndex == -1) return false;

            double value = costFunction.value(1).toDouble();
            function->setAt(0, columnIndex, value);
        }
    }

    return true;
}
