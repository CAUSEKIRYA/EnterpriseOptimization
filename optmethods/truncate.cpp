#include "truncate.h"
#include "matrix.h"

void Truncate::run()
{
    delete result;

    if (input == nullptr || output == nullptr || function == nullptr || solution == nullptr) return;

    setProgress(0.0);

    int r = solution->getRows();
    float f = static_cast<float>(r);

    result = new Matrix(r, 1);
    for (int i = 0; i < r; i++)
    {
        setProgress(i / f);
        int e = static_cast<int>(solution->getAt(i, 0));
        result->setAt(i, 0, e);
    }

    setProgress(1.0);

    emit calculationFinished();
}
