#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

signals:
    void retranslate();

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private slots:
    void accept() override;

private:
    QMap<QString, QString> localesMap;
    Ui::SettingsDialog *ui;

    void loadForeignLocales();
};

#endif // SETTINGSDIALOG_H
