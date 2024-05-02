#ifndef DEBUG_DEFS_H
#define DEBUG_DEFS_H

#define TS_FILE(path) QString("locales/EnterpriseOptimization_") + path

#if DEBUG_MODE
#include <QDebug>
#define DBG(msg) qDebug().noquote().nospace() << msg
#else
#define DBG(msg)
#endif // DEBUG_MODE

#endif // DEBUG_DEFS_H
