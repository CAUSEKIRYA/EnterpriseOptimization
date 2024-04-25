#include "appsettings.h"

#include <QFile>

AppSettings* AppSettings::instance = nullptr;
QString AppSettings::lastErrorMessage = "";

const QMap<QString, QString> AppSettings::defaultSettings = {
{"resolutionX", "1280"},
{"resolutionY", "720"},
{"maximized", "0"},
{"locale", "en_US"}
};

AppSettings::AppSettings()
    : QMap<QString, QString>(defaultSettings)
{
    lastErrorMessage = "";
};

AppSettings* AppSettings::get()
{
    if (instance == nullptr)
    {
        instance = new AppSettings();
    }
    return instance;
}

QString& AppSettings::takeByName(QString name)
{
    QString& val = (*this)[name];

    if (val.isEmpty())
    {
        val = defaultSettings[name];
    }
    return val;
}

AppSettings* AppSettings::initializeFromFile(const QString& path)
{
    delete instance;
    instance = new AppSettings();

    QFile settingsFile(path);
    if (settingsFile.open(QFile::ReadOnly))
    {
        QStringList parameters = QString(settingsFile.readAll()).split("\n");

        for (auto& param : parameters)
        {
            QStringList kv = param.split("=");
            if (!kv.first().isEmpty())
            {
                instance->insert(kv.first(), kv.last());
            }
        }

        return instance;
    }
#ifdef Q_DECL_NOEXCEPT
    lastErrorMessage = settingsFile.errorString();
    return nullptr;
#else
    throw settingsFile.error();
#endif
}

QString AppSettings::toString()
{
    QString result = "";

    for (auto& key : this->keys())
    {
        result = result + key + "=" + takeByName(key) + "\n";
    }

    return result;
}

QString AppSettings::lastError()
{
    return lastErrorMessage;
}
