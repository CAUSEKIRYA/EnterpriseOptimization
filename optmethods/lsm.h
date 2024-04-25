#ifndef LSM_H
#define LSM_H

#include "optimizationthread.h"

class LSM : public OptimizationThread
{
    Q_OBJECT

public:
    LSM() : OptimizationThread(OptimizationType::Generic) { };
    ~LSM() = default;

protected:
    void run() override;
};

#endif // LSM_H
