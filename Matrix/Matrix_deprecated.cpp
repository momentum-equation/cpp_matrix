#include "Matrix_deprecated.h"

namespace
{
    void copyArrays(double* destination, const double* source, size_t size)
    {
        assert(sizeof(destination) == sizeof(source));
        for (size_t i = 0; i != size; i++)
        {
            destination[i] = source[i];
        }
    }

    bool areOfSameSize(const Matrix_deprecated& m1, const Matrix_deprecated& m2)
    {
        return (m1.size().rows == m2.size().rows && m1.size().columns == m2.size().columns);
    }
}

Matrix_deprecated::Matrix_deprecated(size_t rows, size_t columns, double value) :
    m_rows(rows),
    m_columns(columns)
{
    allocateMemory();

    for (size_t i = 0; i != m_rows; i++)
    {
        for (size_t j = 0; j != m_columns; j++)
        {
            m_ptr[i][j] = value;
        }
    }
}

Matrix_deprecated::Matrix_deprecated(size_t rows, size_t columns) :
    Matrix_deprecated(rows, columns, 0)
{}

Matrix_deprecated::Matrix_deprecated(size_t rows) :
    Matrix_deprecated(rows, rows)
{}

// Create Square matrix filled with the value. Defaults to null.
Matrix_deprecated::Matrix_deprecated(size_t rows, const MatrixType& matrixType, double value) :
    m_rows(rows),
    m_columns(rows)
{
    allocateMemory();
    switch (matrixType)
    {
    case MatrixType::Square:
        fillMatrix(value);
        break;
    case MatrixType::Diagonal:
        fillMatrix(0);
        createDiagonal(value);
        break;
    case MatrixType::Unit:
        fillMatrix(0);
        createDiagonal(1);
    default:
        break;
    }
}

Matrix_deprecated::Matrix_deprecated(const Matrix_deprecated& matrix)
{
    setSize(matrix.m_rows, matrix.m_columns);
    if (m_ptr == nullptr)
    {
        allocateMemory();
    }

    copyFromMatrix(matrix.m_ptr);
}

Matrix_deprecated::Matrix_deprecated() :
    m_rows(0),
    m_columns(0),
    m_ptr(nullptr)
{}

Matrix_deprecated::~Matrix_deprecated()
{
    clearMemory();
}


Matrix_deprecated::MatrixSize Matrix_deprecated::size() const
{
    Matrix_deprecated::MatrixSize matrixSize;
    matrixSize.rows = m_rows;
    matrixSize.columns = m_columns;

    return matrixSize;
}

void Matrix_deprecated::setValueAt(size_t row, size_t col, double value)
{
    assert(indexBetweenBounds(row, col));

    m_ptr[row - 1][col - 1] = value;
}

double Matrix_deprecated::operator() (size_t row, size_t col) const
{
    assert(row > 0 && col > 0);

    return m_ptr[row - 1][col - 1];
}

Matrix_deprecated& Matrix_deprecated::operator= (const Matrix_deprecated& matrix)
{
    setSize(matrix.m_rows, matrix.m_columns);
    if (m_ptr == nullptr)
    {
        allocateMemory();
    }

    copyFromMatrix(matrix.m_ptr);

    return *this;
}

void Matrix_deprecated::print()
{
    assert(m_ptr != nullptr);
    for (size_t i = 0; i != m_rows; i++)
    {
        for (size_t j = 0; j != m_columns; j++)
        {
            std::cout << m_ptr[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void Matrix_deprecated::fillMatrix(double value)
{
    for (size_t i = 0; i != m_rows; i++)
    {
        for (size_t j = 0; j != m_columns; j++)
        {
            m_ptr[i][j] = value;
        }
    }
}

void Matrix_deprecated::createDiagonal(double value)
{
    assert(m_rows == m_columns);

    for (size_t i = 0; i != m_rows; i++)
    {
        for (size_t j = 0; j != m_columns; j++)
        {
            if (i == j)
            {
                m_ptr[i][j] = value;
            }
        }
    }
}

void Matrix_deprecated::allocateMemory()
{
    m_ptr = new double* [m_rows];
    for (size_t i = 0; i != m_rows; i++)
    {
        m_ptr[i] = new double[m_columns];
    }
}

void Matrix_deprecated::clearMemory()
{
    for (size_t i = 0; i != m_rows; i++)
    {
        delete[] m_ptr[i];
    }
    delete[] m_ptr;
}

void Matrix_deprecated::setSize(size_t rows, size_t columns)
{
    m_rows = rows;
    m_columns = columns;
}

void Matrix_deprecated::copyFromMatrix(double** const matrixPtr)
{
    assert(matrixPtr != nullptr);
    assert(sizeof(m_ptr) == sizeof(matrixPtr));

    for (size_t i = 0; i != m_rows; i++)
    {
        for (size_t j = 0; j != m_columns; j++)
        {
            m_ptr[i][j] = matrixPtr[i][j];
        }
    }
}

bool Matrix_deprecated::indexBetweenBounds(size_t row, size_t col) const
{
    return ((row > 0 && row < m_rows + 1) && (col > 0 && col < m_columns + 1));
}


Matrix_deprecated operator+ (const Matrix_deprecated& matrix1, const Matrix_deprecated& matrix2)
{
    assert(areOfSameSize(matrix1, matrix2));
    Matrix_deprecated result(matrix1.m_rows, matrix2.m_columns);

    for (size_t i = 0; i != result.m_rows; i++)
    {
        for (size_t j = 0; j != result.m_columns; j++)
        {
            result.m_ptr[i][j] = matrix1.m_ptr[i][j] + matrix2.m_ptr[i][j];
        }
    }
    return result;
}

// iterative matrix multiplication: costs O(n^3)
Matrix_deprecated operator& (const Matrix_deprecated& matrix1, const Matrix_deprecated& matrix2)
{
    assert(matrix1.size().columns == matrix2.size().rows);

    Matrix_deprecated result(matrix1.size().rows, matrix2.size().columns);

    for (size_t i = 0; i != matrix1.size().rows; i++)
    {
        for (size_t k = 0; k != matrix2.size().columns; k++)
        {
            double sumWhileCalculatingProduct = 0;
            for (size_t j = 0; j != matrix1.size().columns; j++)
            {
                sumWhileCalculatingProduct += matrix1.m_ptr[i][j] * matrix2.m_ptr[j][k];
            }
            result.m_ptr[i][k] = sumWhileCalculatingProduct;
        }
    }
    return result;
}