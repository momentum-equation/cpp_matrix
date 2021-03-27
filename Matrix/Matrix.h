#pragma once
#include <iostream>
#include <cassert>

#include "IPrint.h"

// requirements for type T to work with this class
// should have copy assignment, multiplication operator *, addition operator + and +=

enum class MatrixType
{
    Square,
    Diagonal,
    Unit
};

struct MatrixSize
{
    size_t rows;
    size_t columns;
};

template<typename T> class Matrix;
//template<typename T> Matrix<T> operator+ (const Matrix<T>& matrix1, const Matrix<T>& matrix2);
//template<typename T> Matrix<T> operator* (const Matrix<T>& matrix1, const Matrix<T>& matrix2);

template<typename T>
class Matrix : public IPrint
{
public:
    Matrix();

    Matrix(size_t rows, size_t columns, const T& value);

    Matrix(size_t rows, size_t columns);

    Matrix(size_t rows);

    Matrix(size_t rows, const MatrixType& matrixType, const T& value);

    Matrix(const Matrix& matrix);

    virtual ~Matrix();

    Matrix& operator= (const Matrix& matrix);

    MatrixSize size() const;

    void setValueAt(size_t row, size_t col, const T& value);

    virtual void Print(std::ostream& out) const override;

    // fillMatrix with value
    void fillMatrix(const T& value);

    // create diagonal matrix
    void createDiagonal(const T& value);

    // Fortran style array access
    T operator() (size_t row, size_t col) const;


private:
    void allocateMemory();

    void clearMemory();

    void setSize(size_t rows, size_t columns);

    void copyFromMatrix(T* const matrixPtr);

    bool indexBetweenBounds(size_t row, size_t col) const;

private:
    T* m_ptr = nullptr;
    size_t m_rows, m_columns;

    // matrix addition
    Matrix<T> operator+ (const Matrix<T>& otherMatrix)
    {
        Matrix<T> thisMatrix = *this;
        assert(areOfSameSize(thisMatrix, otherMatrix));
        auto rows = thisMatrix.m_rows;
        auto columns = otherMatrix.m_columns;
        Matrix<T> result(rows, columns);

        for (size_t i = 0; i != rows; i++)
        {
            for (size_t j = 0; j != columns; j++)
            {
                result.m_ptr[rows * i + j] = thisMatrix.m_ptr[rows * i + j] + otherMatrix.m_ptr[rows * i + j];
            }
        }
        return result;
    }

    // matrix inner product
    Matrix<T> operator* (const Matrix<T>& otherMatrix)
    {
        
        Matrix<T> thisMatrix = *this;
        assert(thisMatrix.size().columns == otherMatrix.size().rows);

        auto rows = thisMatrix.size().rows;
        auto columns = otherMatrix.size().columns;
        auto sumIterations = thisMatrix.size().columns;

        Matrix<T> result(rows, columns);

        for (size_t i = 0; i != rows; i++)
        {
            for (size_t k = 0; k != columns; k++)
            {
                T sumWhileCalculatingProduct = 0;
                for (size_t j = 0; j != sumIterations; j++)
                {
                    sumWhileCalculatingProduct += thisMatrix(i, j) * otherMatrix(j, k);
                }
                result.m_ptr[rows * i + k] = sumWhileCalculatingProduct;
            }
        }
        return result;
    }
};

namespace
{
    template<typename T>
    void copyArrays(T* destination, const T* source, size_t size);

    template<typename T>
    bool areOfSameSize(const Matrix<T>& m1, const Matrix<T>& m2);
}
