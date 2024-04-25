#ifndef IOPTIMIZATIONOBJECT_H
#define IOPTIMIZATIONOBJECT_H

#include <QThread>

class Matrix;

enum class OptimizationType
{
    Integer = 'i',
    Generic = 'g'
};

class OptimizationThread : public QThread
{
    Q_OBJECT

public:
    OptimizationThread(OptimizationType type);
    virtual ~OptimizationThread();

signals:
    void calculationFinished();
    void completedBy(int percentage);

public:
    Matrix* getResult() const;
    OptimizationType getType() const;
    void setBounds(int min, int max);
    void init(Matrix * input, Matrix * output, Matrix * function, Matrix * solution = nullptr);

protected:
    Matrix* solution;
    Matrix* input;
    Matrix* output;
    Matrix* function;
    Matrix* result;

    virtual void run() = 0;

    void setProgress(float value);

private:
    float progress;
    int min, max;
    OptimizationType type;
};

#endif // IOPTIMIZATIONOBJECT_H
