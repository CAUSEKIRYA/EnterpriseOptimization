#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "optimizationthread.h"

class Simplex : public OptimizationThread
{
    Q_OBJECT

public:
    Simplex() : OptimizationThread(OptimizationType::Generic) { };
    ~Simplex() = default;

protected:
    void run() override;
};

#endif // SIMPLEX_H
