#define DEBUG_MODE 1
#include "program_defs.h"

#include "mainwindow.h"
#include "appsettings.h"
#include "optmethods/optimizationobjectstorage.h"

#include <QApplication>
#include <QTranslator>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Loading settings from file, or creating it, if it does not exist
    const QString settingsFileName = "settings.txt";
    QFile settingsFile(settingsFileName);

    DBG("Settings file exists: " << settingsFile.exists());

    AppSettings* settings;
    if (settingsFile.exists())
    {
        settings = AppSettings::initializeFromFile(settingsFileName);
        if (settings == nullptr)
        {
            DBG("App Settings was not loaded from file due to following error:\n");
            DBG(AppSettings::lastError());
            goto default_settings;
        }
        DBG("Loaded app settings from file " << settingsFileName << "\n");
    }
    else
    {
default_settings:
        settings = AppSettings::get();
        DBG("Loaded default app settings\n");
    }

    // Installing translations and applying other settings
    QTranslator translator;
    if (translator.load(TS_FILE(settings->takeByName("locale")))) {
        a.installTranslator(&translator);
    }

    OptimizationObjectStorage::init();

    MainWindow w;

    w.resize(settings->takeByName("resolutionX").toInt(), settings->takeByName("resolutionY").toInt());
    if (settings->takeByName("maximized").toInt()) w.showMaximized();
    else w.show();


    // Loading program
    int returnCode = a.exec();

    if (settingsFile.open(QFile::WriteOnly))
    {
        QByteArray stringRepr = QByteArray::fromStdString(settings->toString().toStdString());
        settingsFile.write(stringRepr);
        settingsFile.close();
    }

    return returnCode;
}
