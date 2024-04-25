#include "optimizationthread.h"
#include "matrix.h"

OptimizationThread::OptimizationThread(OptimizationType type) :
    min(0),
    max(100),
    progress(0),
    input(nullptr),
    output(nullptr),
    function(nullptr),
    solution(nullptr),
    result(nullptr),
    type(type)
{ }

void OptimizationThread::init(Matrix * input, Matrix * output, Matrix * function, Matrix * solution)
{
    this->input = input;
    this->output = output;
    this->function = function;
    this->solution = solution;
}

OptimizationThread::~OptimizationThread()
{
    delete result;
}

Matrix* OptimizationThread::getResult() const
{
    return result;
}

OptimizationType OptimizationThread::getType() const
{
    return type;
}

void OptimizationThread::setBounds(int min, int max)
{
    this->min = min;
    this->max = max;
}

void OptimizationThread::setProgress(float value)
{
    progress = value;
    emit completedBy(min + progress * (max - min));
}
