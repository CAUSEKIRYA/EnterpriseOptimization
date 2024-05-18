#ifndef MATRIX_H
#define MATRIX_H

#include <qglobal.h>
#include <QVariant>

class Matrix
{
private:
    double ** data;
    uint rows, columns;

public:
    Matrix(uint rows, uint columns);
    Matrix(Matrix & other);
    Matrix(Matrix && other);
    ~Matrix();

    static Matrix diagonal(uint size, double value = 1);
    static Matrix solveLinEq(Matrix& A, Matrix& B);

    int getRows() const;
    int getColumns() const;
    double getAt(int i, int j) const;
    void setAt(int i, int j, double value);
    Matrix transpose();
    QString toString();

    Matrix operator=(Matrix& other);
    Matrix operator-();
    Matrix operator+(Matrix other);
    Matrix operator-(Matrix other);
    Matrix operator*(Matrix other);

    bool operator==(Matrix& other);
    bool operator>(Matrix &other);
    bool operator>=(Matrix &other);
    bool operator<(Matrix &other);
    bool operator<=(Matrix &other);

#ifdef Q_DECL_NOEXCEPT
    bool hasError() const;
#endif
};

#endif // MATRIX_H
