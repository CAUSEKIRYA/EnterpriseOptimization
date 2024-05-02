#include "branchandbound.h"
#include "matrix.h"

#include <QBitArray>
#include <QtMath>

#define DEBUG_MODE 1
#include "program_defs.h"

void BranchAndBound::run()
{
    delete result;

    if (input == nullptr || output == nullptr || function == nullptr || solution == nullptr) return;

    setProgress(0.0);

    int r = solution->getRows();
    QBitArray current(r);
    QBitArray full(r, true);

    double f = qPow(2, r), k = 0;
    double minF = 1e300;

    result = new Matrix(r, 1);
    while (true)
    {
        setProgress(k / f);
        Matrix temp(*solution);
        for (int i = 0; i < r; i++)
        {
            temp.setAt(i, 0, static_cast<int>(temp.getAt(i, 0) + (current.at(i) ? 1 : 0)));
        }

        double curF = (*function * temp).getAt(0, 0);
        if (curF < minF && *input * temp <= *output)
        {
            minF = curF;
            delete result;
            result = new Matrix(temp);
        }

        if (current == full) break;
        else
        {
            for (int i = 0; i < r; i++)
            {
                current.toggleBit(i);
                if (!current.at(i)) continue;
                else break;
            }
            k += 1;
        }
    }

    setProgress(1.0);

    emit calculationFinished();
}
