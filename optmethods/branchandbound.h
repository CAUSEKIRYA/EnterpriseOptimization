#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include "optimizationthread.h"

class BranchAndBound : public OptimizationThread
{
    Q_OBJECT

public:
    BranchAndBound() : OptimizationThread(OptimizationType::Integer) { };
    ~BranchAndBound() = default;

protected:
    void run() override;
};

#endif // BRANCHANDBOUND_H
