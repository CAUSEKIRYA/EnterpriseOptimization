#include "dbconnectiondialog.h"
#include "ui_dbconnectiondialog.h"

DBConnectionDialog::DBConnectionDialog(QWidget *parent, QList<QString> items) :
    QDialog(parent),
    ui(new Ui::DBConnectionDialog)
{
    ui->setupUi(this);
    ui->DBMSCombo->addItems(items);
}

DBConnectionDialog::~DBConnectionDialog()
{
    delete ui;
}

void DBConnectionDialog::accept()
{
    QMap<QString, QString>* vals = new QMap<QString, QString>();
    vals->insert("dbms", ui->DBMSCombo->currentText());
    vals->insert("hostname", ui->hostEdit->text());
    vals->insert("username", ui->usernameEdit->text());
    vals->insert("password", ui->passwordEdit->text());
    vals->insert("dbname", ui->dbnameEdit->text());
    emit passValues(vals);

    QDialog::accept();
}
