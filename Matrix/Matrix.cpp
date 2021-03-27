#include "Matrix.h"

namespace
{
    template<typename T>
    void copyArrays(T* destination, const T* source, size_t size)
    {
        assert(sizeof(destination) == sizeof(source));
        for (size_t i = 0; i != size; i++)
        {
            destination[i] = source[i];
        }
    }

    template<typename T>
    bool areOfSameSize(const Matrix<T>& m1, const Matrix<T>& m2)
    {
        return (m1.size().rows == m2.size().rows && m1.size().columns == m2.size().columns);
    }
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, const T& value) :
    m_rows(rows),
    m_columns(columns)
{
    allocateMemory();

    for (size_t i = 0; i != m_rows; i++)
    {
        for (size_t j = 0; j != m_columns; j++)
        {
            m_ptr[m_rows*i + j] = value;
        }
    }
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) :
    Matrix<T>(rows, columns, 0)
{}

template<typename T>
Matrix<T>::Matrix(size_t rows) :
    Matrix<T>(rows, rows)
{}

// Create Square matrix filled with the value. Defaults to null.
template<typename T>
Matrix<T>::Matrix(size_t rows, const MatrixType& matrixType, const T& value) :
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
    //case MatrixType::Unit:
    //    fillMatrix(0);
    //    createDiagonal(1);
    default:
        break;
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& matrix)
{
    setSize(matrix.m_rows, matrix.m_columns);
    if (m_ptr == nullptr)
    {
        allocateMemory();
    }

    copyFromMatrix(matrix.m_ptr);
}

template<typename T>
Matrix<T>::Matrix() :
    m_rows(0),
    m_columns(0),
    m_ptr(nullptr)
{}

template<typename T>
Matrix<T>::~Matrix()
{
    clearMemory();
}

template<typename T>
MatrixSize Matrix<T>::size() const
{
    MatrixSize matrixSize;
    matrixSize.rows = m_rows;
    matrixSize.columns = m_columns;

    return matrixSize;
}

template<typename T>
void Matrix<T>::setValueAt(size_t row, size_t col, const T& value)
{
    assert(indexBetweenBounds(row, col));

    m_ptr[m_rows * (row - 1) + (col - 1)] = value;
}

template<typename T>
T Matrix<T>::operator() (size_t row, size_t col) const
{
    return m_ptr[m_rows*row + col];
}

template<typename T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& matrix)
{
    setSize(matrix.m_rows, matrix.m_columns);
    if (m_ptr == nullptr)
    {
        allocateMemory();
    }

    copyFromMatrix(matrix.m_ptr);

    return *this;
}

template<typename T>
void Matrix<T>::Print(std::ostream& out) const
{
    assert(m_ptr != nullptr);
    for (size_t i = 0; i != m_rows* m_columns; i++)
    {
        out << m_ptr[i] << ' ';
        if ((i + 1) % m_rows == 0)
        {
            out << std::endl;
        }
    }
}

template<typename T>
void Matrix<T>::fillMatrix(const T& value)
{
    for (size_t i = 0; i != m_rows*m_columns; i++)
    {
        m_ptr[i] = value;
    }
}

template<typename T>
void Matrix<T>::createDiagonal(const T& value)
{
    assert(m_rows == m_columns);

    size_t size = m_rows;

    for (size_t i = 0; i != size*size; i++)
    {
        if (i % (size + 1) == 0)
        {
            m_ptr[i] = value;
        }
    }
}

template<typename T>
void Matrix<T>::allocateMemory()
{
    m_ptr = new T [m_rows*m_columns];
}

template<typename T>
void Matrix<T>::clearMemory()
{
    delete[] m_ptr;
}

template<typename T>
void Matrix<T>::setSize(size_t rows, size_t columns)
{
    m_rows = rows;
    m_columns = columns;
}

template<typename T>
void Matrix<T>::copyFromMatrix(T* const matrixPtr)
{
    assert(matrixPtr != nullptr);

    for (size_t i = 0; i != m_rows*m_columns; i++)
    {
        m_ptr[i] = matrixPtr[i];
    }
}

template<typename T>
bool Matrix<T>::indexBetweenBounds(size_t row, size_t col) const
{
    return ((row > 0 && row < m_rows + 1) && (col > 0 && col < m_columns + 1));
}

template <>
class Matrix<double>;

template<>
class Matrix<int>;