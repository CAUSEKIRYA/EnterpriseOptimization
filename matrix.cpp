#include "matrix.h"

#include <QString>

#ifndef Q_DECL_NOEXCEPT
#include <QException>
#endif

Matrix::Matrix(uint rows, uint columns) :
    rows(rows),
    columns(columns),
    data(new double*[rows])
{
    for (int i = 0; i < rows; i++)
    {
        data[i] = new double[columns];
        for (int j = 0; j < columns; j++)
        {
            data[i][j] = 0;
        }
    }
}

Matrix::~Matrix()
{
    for (uint i = 0; data != nullptr && i < rows; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}

Matrix::Matrix(Matrix & other) :
    rows(other.rows),
    columns(other.columns)
{
    data = new double*[rows];
    for (int i = 0; i < rows; i++)
    {
        data[i] = new double[columns];
        for (int j = 0; j < columns; j++)
        {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::Matrix(Matrix && other) :
    rows(other.rows),
    columns(other.columns),
    data(nullptr)
{
    std::swap(data, other.data);
}

Matrix Matrix::operator=(Matrix & other)
{
    Matrix result(other.rows, other.columns);
    result.data = other.data;
    return result;
}

Matrix Matrix::operator-()
{
    Matrix result(rows, columns);
    for (uint i = 0; i < rows; i++)
    {
        for (uint j = 0; j < columns; j++)
        {
            result.data[i][j] = -data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator+(Matrix other)
{
    if (rows != other.rows || columns != other.columns)
    {
#ifndef Q_DECL_NOEXCEPT
        throw QException();
#else
        return Matrix(0, 0);
#endif
    }

    Matrix result(rows, columns);
    for (uint i = 0; i < rows; i++)
    {
        for (uint j = 0; j < columns; j++)
        {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(Matrix other)
{
    return (*this) + (-other);
}

Matrix Matrix::operator*(Matrix other)
{
    if (columns != other.rows)
    {
#ifndef Q_DECL_NOEXCEPT
        throw QException();
#else
        return Matrix(0, 0);
#endif
    }

    Matrix result(rows, other.columns);
    for (uint i = 0; i < rows; i++)
    {
        for (uint j = 0; j < other.columns; j++)
        {
            double cur = 0;
            for (uint k = 0; k < columns; k++)
            {
                cur += data[i][k] * other.data[k][j];
            }
            result.data[i][j] = cur;
        }
    }
    return result;
}

bool Matrix::operator<(Matrix &other)
{
    if (rows != other.rows || columns != other.columns)
    {
#ifndef Q_DECL_NOEXCEPT
        throw QException();
#else
        return false;
#endif
    }

    for (uint i = 0; i < rows; i++)
    {
        for (uint j = 0; j < columns; j++)
        {
            if (getAt(i, j) >= other.getAt(i, j))
            {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::operator>(Matrix &other)
{
    if (rows != other.rows || columns != other.columns)
    {
#ifndef Q_DECL_NOEXCEPT
        throw QException();
#else
        return false;
#endif
    }

    for (uint i = 0; i < rows; i++)
    {
        for (uint j = 0; j < columns; j++)
        {
            if (getAt(i, j) <= other.getAt(i, j))
            {
                return false;
            }
        }
    }

    return true;
}

int Matrix::getRows() const
{
    return rows;
}

int Matrix::getColumns() const
{
    return columns;
}

double Matrix::getAt(int i, int j) const
{
    return data[i][j];
}

void Matrix::setAt(int i, int j, double value)
{
    data[i][j] = value;
}

Matrix Matrix::transpose()
{
    Matrix result(columns, rows);
    for (uint i = 0; i < rows; i++)
    {
        for (uint j = 0; j < columns; j++)
        {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

#ifdef Q_DECL_NOEXCEPT
bool Matrix::hasError() const
{
    return !(rows || columns);
}
#endif

Matrix Matrix::solveLinEq(Matrix& A, Matrix& B)
{
    if (A.rows != A.columns || A.rows != B.rows || B.columns != 1)
    {

#ifndef Q_DECL_NOEXCEPT
        throw QException();
#else
        return Matrix(0, 0);
#endif
    }

    Matrix a(A), b(B);

    for (int var = 0; var < a.rows; var++)
        {
            if (a.data[var][var] == 0)
            {
                bool good = false;
                for (int row = 0; row < a.rows; row++)
                {
                    if (a.data[row][var] != 0)
                    {
                        std::swap(a.data[var], a.data[row]);
                        std::swap(b.data[var], b.data[row]);
                        good = true;
                        break;
                    }
                }
                if (!good)
                {
#ifndef Q_DECL_NOEXCEPT
                    throw QException();
#else
                    return Matrix(0, 0);
#endif
                }
            }

            double coef = a.data[var][var];
            for (int j = 0; j < a.rows; j++)
            {
                a.data[var][j] /= coef;
            }
            b.data[var][0] /= coef;

            for (int i = 0; i < a.rows; i++)
            {
                if (i == var) continue;

                coef = a.data[i][var];
                for (int j = 0; j < a.rows; j++)
                {
                    a.data[i][j] -= a.data[var][j] * coef;
                }
                b.data[i][0] -= b.data[var][0] * coef;
            }
        }

    return b;
}

Matrix Matrix::diagonal(uint size, double value)
{
    Matrix result(size, size);
    for (uint i = 0; i < size; i++)
    {
        result.data[i][i] = value;
    }
    return result;
}

QString Matrix::toString()
{
    QString str = "";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            str += QString::number(data[i][j]) + " ";
        }
        str += "\n";
    }
    return str;
}
