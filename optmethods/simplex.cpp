#include "simplex.h"
#include "matrix.h"

#define DEBUG_MODE 1
#include "../program_defs.h"
#define MAX_ITERATIONS 1e4

void Simplex::run()
{
    delete result;

    if (input == nullptr || output == nullptr || function == nullptr) return;

    int eqCount = input->getRows();
    int varCount = function->getColumns();
    Matrix simplexMatrix(eqCount + 1, eqCount + varCount + 1);
    Matrix idx(eqCount, 1);

    setProgress(0.02);

    // Initializing function
    for (int i = 0; i < varCount; i++) simplexMatrix.setAt(0, i, function->getAt(0, i));
    setProgress(0.04);
    for (int i = 0; i < eqCount; i++)
    {
        simplexMatrix.setAt(i + 1, varCount + i, 1);
        simplexMatrix.setAt(i + 1, varCount + eqCount, output->getAt(i, 0));
        idx.setAt(i, 0, varCount + i);
    }
    setProgress(0.06);
    for (int i = 0; i < eqCount; i++)
    {
        for (int j = 0; j < varCount; j++)
        {
            simplexMatrix.setAt(i + 1, j, input->getAt(i, j));
        }
    }
    setProgress(0.1);

    for (int k = 0; k < MAX_ITERATIONS; k++)
    {
        int optimalVariables = 0;
        for (int i = 0; i < varCount; i++)
        {
            if (simplexMatrix.getAt(0, i) >= 0) optimalVariables++;
        }

        setProgress(0.1 + (0.85 * optimalVariables) / varCount);
        if (optimalVariables == varCount) break;

        int pivotElementRow = -1, pivotElementColumn = -1;
        double flag = 0;
        for (int j = 0; j < eqCount + varCount; j++)
        {
            if (simplexMatrix.getAt(0, j) <= flag)
            {
                pivotElementColumn = j;
                flag = simplexMatrix.getAt(0, j);
            }
        }

        if (pivotElementColumn == -1) break;

        flag = 1e300;
        for (int i = 1; i < eqCount + 1; i++)
        {
            if (simplexMatrix.getAt(i, pivotElementColumn) == 0) continue;

            double v = simplexMatrix.getAt(i, eqCount + varCount) / simplexMatrix.getAt(i, pivotElementColumn);
            if (v < flag)
            {
                pivotElementRow = i;
                flag = v;
            }
        }
        idx.setAt(pivotElementRow - 1, 0, pivotElementColumn);

        for (int j = 0; j < eqCount + varCount + 1; j++)
        {
            for (int i = 0; i < eqCount + 1; i++)
            {
                if (i != pivotElementRow && j != pivotElementColumn)
                {
                    simplexMatrix.setAt(i, j, simplexMatrix.getAt(i, j) - (simplexMatrix.getAt(pivotElementRow, j) * simplexMatrix.getAt(i, pivotElementColumn)) / simplexMatrix.getAt(pivotElementRow, pivotElementColumn));
                }
            }
            simplexMatrix.setAt(pivotElementRow, j, simplexMatrix.getAt(pivotElementRow, j) / simplexMatrix.getAt(pivotElementRow, pivotElementColumn));
        }

        for (int i = 0; i < eqCount + 1; i++)
        {
            simplexMatrix.setAt(i, pivotElementColumn, i == pivotElementRow ? 1 : 0);
        }
    }

    setProgress(0.95);

    // Generating results;
    result = new Matrix(varCount, 1);
    for (int i = 0; i < varCount; i++)
    {
        int k;
        for (k = 0; k < eqCount; k++)
        {
            if (idx.getAt(k, 0) == i) break;
        }

        result->setAt(i, 0, simplexMatrix.getAt(k + 1, eqCount + varCount));
    }
    setProgress(1.0);

    emit calculationFinished();
}
