#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "program_defs.h"
#include "appsettings.h"

#include <QDir>
#include <QMessageBox>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    // Load available locales
    localesMap.insert("en_US", "English");
    for (QString& entry : QDir("locales", "EnterpriseOptimization_*.*").entryList())
    {
        QString locale = entry.right(8).left(5);
        QString lng = QLocale(locale).nativeLanguageName();
        lng[0] = lng[0].toUpper();

        localesMap.insert(locale, lng);
    }

    ui->setupUi(this);

    ui->languageCombo->addItems(localesMap.values());
    ui->languageCombo->setCurrentText(localesMap[AppSettings::get()->takeByName("locale")]);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::accept()
{
    QString newLocaleValue = localesMap.key(ui->languageCombo->currentText());
    bool needRestart = false;

    if (AppSettings::get()->takeByName("locale") != newLocaleValue)
    {
        AppSettings::get()->takeByName("locale") = newLocaleValue;
        needRestart = true;
    }
    if (needRestart)
    {
        QMessageBox err(QMessageBox::Information, tr("Information"), "Changes will be applied after restart", QMessageBox::Ok, this);
        err.exec();
    }

    QDialog::accept();
}
