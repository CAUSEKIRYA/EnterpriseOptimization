#ifndef OPTIMIZATIONRESULTSDIALOG_H
#define OPTIMIZATIONRESULTSDIALOG_H

#include <QDialog>

namespace Ui {
class OptimizationResultsDialog;
}

class Matrix;
class DBViewWidget;
class OptimizationThread;

class OptimizationResultsDialog : public QDialog
{
    Q_OBJECT

private slots:
    void finishCalculation();
    void calculateInteger();

public slots:
    void calculateAndShow(QString* optMethod, QString* integerMethod);

public:
    explicit OptimizationResultsDialog(DBViewWidget *db, QWidget *parent = nullptr);
    ~OptimizationResultsDialog();
    void keyPressEvent(QKeyEvent* e) override;

private:
    DBViewWidget* dbViewWidget;
    Ui::OptimizationResultsDialog *ui;

    OptimizationThread* method, *integerMethod;

    Matrix *input, *output, *function, *result;
};

#endif // OPTIMIZATIONRESULTSDIALOG_H
