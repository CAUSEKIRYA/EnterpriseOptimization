#include "simplex.h"
#include "matrix.h"

#define DEBUG_MODE 1
#include "../program_defs.h"

void Simplex::run()
{
    delete result;

    if (input == nullptr || output == nullptr || function == nullptr) return;

    int eqCount = input->getRows();
    int varCount = function->getColumns();
    Matrix simplexMatrix(eqCount + 1, eqCount + varCount + 1);

    setProgress(0.02);

    // Initializing function
    for (int i = 0; i < varCount; i++) simplexMatrix.setAt(0, i, function->getAt(0, i));
    setProgress(0.04);
    for (int i = 0; i < eqCount; i++) simplexMatrix.setAt(i + 1, varCount + i + 1, 1);
    setProgress(0.06);
    for (int i = 0; i < eqCount; i++)
    {
        for (int j = 0; j < varCount; j++)
        {
            simplexMatrix.setAt(i + 1, j, input->getAt(i, j));
        }
    }
    setProgress(0.1);

    DBG(simplexMatrix.toString());

    setProgress(0.95);

    // Generating results;
    result = new Matrix(varCount, 1);
    for (int i = 0; i < varCount; i++)
    {
        result->setAt(i, 0, simplexMatrix.getAt(i + 1, eqCount + varCount));
    }
    setProgress(1.0);

    emit calculationFinished();
}
