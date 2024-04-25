#ifndef APPSETTINGS_H
#define APPSETTINGS_H
#include <QString>
#include <QMap>

class AppSettings : private QMap<QString, QString>
{
private:
    AppSettings();
    AppSettings(const AppSettings &) = delete;
    static AppSettings* instance;

    static const QMap<QString, QString> defaultSettings;

#ifdef Q_DECL_NOEXCEPT
    static QString lastErrorMessage;
#endif

public:
    QString toString();
    QString& takeByName(QString name);

    static AppSettings* get();
    static AppSettings* initializeFromFile(const QString&);

#ifdef Q_DECL_NOEXCEPT
    static QString lastError();
#endif
};
#endif // APPSETTINGS_H
