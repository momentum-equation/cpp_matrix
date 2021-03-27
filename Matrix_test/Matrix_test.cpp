#include "pch.h"
#include "Matrix.cpp"

template<typename testType>
class TestMatrix : public Matrix<testType>
{
	TestMatrix(testType* array)
	{

	}

private:
	size_t m_rows;
	size_t m_columns;
};

TEST(MatrixTests, UnitMatrix) {
	Matrix<size_t> I = Matrix<size_t>(3, MatrixType::Unit, 1);
	EXPECT_EQ(1, 2);
	EXPECT_TRUE(true);
}