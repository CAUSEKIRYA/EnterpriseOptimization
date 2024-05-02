#ifndef TRUNCATE_H
#define TRUNCATE_H

#include "optimizationthread.h"

class Truncate : public OptimizationThread
{
    Q_OBJECT

public:
    Truncate() : OptimizationThread(OptimizationType::Integer) { };
    ~Truncate() = default;

protected:
    void run() override;
};

#endif // TRUNCATE_H
