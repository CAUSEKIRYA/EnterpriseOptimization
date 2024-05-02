#ifndef DBVIEWWIDGET_H
#define DBVIEWWIDGET_H

#include <QTabWidget>
#include <QMap>
#include <QPair>

namespace Ui {
class DBViewWidget;
}

class QSqlDatabase;
class DBConnectionDialog;
class MainWindow;
class Matrix;

class DBViewWidget : public QTabWidget
{
    Q_OBJECT

signals:
    void tablesShown(bool shown);

private slots:
    void connectToDb(QMap<QString, QString>* values);

public slots:
    void refreshDb();
    void disconnectFromDb();
    void openLoadDialog();

    // functions
private:
    void clearAllTables();

public:
    explicit DBViewWidget(MainWindow* mw, QWidget *parent = nullptr);
    ~DBViewWidget();

    QPair<int, int> valuesSizes() const;
    bool formValuesFromDb(Matrix* input, Matrix* output, Matrix* function);

    // variables
private:
    QSqlDatabase* dbConnectionPtr;
    MainWindow* mainWindow;
    DBConnectionDialog* connectionDialog;
    Ui::DBViewWidget *ui;
    QList<QWidget*> tabs;

    static const QMap<QString, QString> availableDrivers;
};

#endif // DBVIEWWIDGET_H
