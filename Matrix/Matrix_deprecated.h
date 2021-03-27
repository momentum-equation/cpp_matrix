#pragma once
#include <iostream>
#include <cassert>

enum class MatrixType
{
    Square,
    Diagonal,
    Unit
};

class Matrix_deprecated
{
public:
    Matrix_deprecated();

    Matrix_deprecated(size_t rows, size_t columns, double value);

    Matrix_deprecated(size_t rows, size_t columns);

    Matrix_deprecated(size_t rows);

    Matrix_deprecated(size_t rows, const MatrixType& matrixType, double value = 0);

    Matrix_deprecated(const Matrix_deprecated& matrix);

    ~Matrix_deprecated();

    Matrix_deprecated& operator= (const Matrix_deprecated& matrix);

    struct MatrixSize
    {
        size_t rows;
        size_t columns;
    };

    MatrixSize size() const;

    void setValueAt(size_t row, size_t col, double value);

    void print();

    // fillMatrix with value
    void fillMatrix(double value);

    // create diagonal matrix
    void createDiagonal(double value);

    // Fortran style array access
    double operator() (size_t row, size_t col) const;

    // matrix addition
    friend Matrix_deprecated operator+ (const Matrix_deprecated& matrix1, const Matrix_deprecated& matrix2);

    // matrix inner product
    friend Matrix_deprecated operator& (const Matrix_deprecated& matrix1, const Matrix_deprecated& matrix2);

private:
    void allocateMemory();

    void clearMemory();

    void setSize(size_t rows, size_t columns);

    void copyFromMatrix(double** const matrixPtr);

    bool indexBetweenBounds(size_t row, size_t col) const;

private:
    double** m_ptr = nullptr;
    size_t m_rows, m_columns;
};

namespace
{
    void copyArrays(double* destination, const double* source, size_t size);
    bool areOfSameSize(const Matrix_deprecated& m1, const Matrix_deprecated& m2);
}