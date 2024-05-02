#include "optimizationobjectstorage.h"
#include "lsm.h"
#include "simplex.h"
#include "truncate.h"
#include "branchandbound.h"

#include <QMap>

QMap<QString, OptimizationThread*> OptimizationObjectStorage::indexes = {};

void OptimizationObjectStorage::init()
{
    indexes = {
        { QObject::tr("LSM"), new LSM },
        { QObject::tr("Simplex"), new Simplex },
        //{ QObject::tr("Interior Point"), new InteriorPoint },
        //{ QObject::tr("Gradient Descend"), nullptr },
        { QObject::tr("Truncate"), new Truncate },
        { QObject::tr("B&B"), new BranchAndBound }
    };
}
