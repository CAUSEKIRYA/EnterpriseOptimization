#ifndef DBCONNECTIONDIALOG_H
#define DBCONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class DBConnectionDialog;
}

class DBConnectionDialog : public QDialog
{
    Q_OBJECT

signals:
    void passValues(QMap<QString, QString>*);

public:
    explicit DBConnectionDialog(QWidget *parent, QList<QString> items);
    ~DBConnectionDialog();

    void accept() override;

private:
    Ui::DBConnectionDialog *ui;
};

#endif // DBCONNECTIONDIALOG_H
