#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class DBViewWidget;
class SettingsDialog;
class QVBoxLayout;
class OptimizationResultsDialog;
class AboutProgramDialog;
class HelpWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void passOptimizationParameters(QString* optimizeMethod, QString* integerMethod);

public:
    MainWindow();
    ~MainWindow();

    DBViewWidget* dbView;

    void resizeEvent(QResizeEvent*);
    void changeEvent(QEvent *);

public slots:
    void onOptimizeClicked();
    void enableButtons(bool enable);

private:
    AboutProgramDialog* aboutDialog;
    HelpWindow* helpWindow;
    SettingsDialog* sw;
    OptimizationResultsDialog* optRes;
    QVBoxLayout* viewWidgetLayout;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
