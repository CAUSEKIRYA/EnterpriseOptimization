#ifndef OPTIMIZATIONOBJECTSTORAGE_H
#define OPTIMIZATIONOBJECTSTORAGE_H

#include "optimizationresultsdialog.h"

class OptimizationThread;

class OptimizationObjectStorage
{
private:
    OptimizationObjectStorage() = delete;
    OptimizationObjectStorage(OptimizationObjectStorage & other) = delete;
    OptimizationObjectStorage operator=(OptimizationObjectStorage & other) = delete;

public:
    static void init();

    static QMap<QString, OptimizationThread*> indexes;
};
#endif // OPTIMIZATIONOBJECTSTORAGE_H
