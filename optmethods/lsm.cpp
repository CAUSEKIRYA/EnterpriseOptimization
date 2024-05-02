#include "lsm.h"
#include "../matrix.h"

#define DEBUG_MODE 0
#include "../program_defs.h"

void LSM::run()
{
    delete result;

    if (input == nullptr || output == nullptr || function == nullptr) return;

    DBG(input->toString() << "\n");
    DBG(output->toString() << "\n");

    Matrix inputT = input->transpose();
    setProgress(0.25);

    Matrix A = inputT * (*input) + Matrix::diagonal(inputT.getRows(), 1e-3);
    setProgress(0.5);

    Matrix B = inputT * (*output);
    setProgress(0.75);

    result = new Matrix(std::forward<Matrix &&>(Matrix::solveLinEq(A, B)));
    setProgress(1.0);

    emit calculationFinished();
}
