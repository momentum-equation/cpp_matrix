#include "Matrix.h"
#include <iostream>

int main(int argc, char** argv)
{
    Matrix<double> matrix(3, MatrixType::Square, 3.5);
    Matrix<double> matrx1(3, MatrixType::Square, -3.5);
    auto size = matrix.size();
    //Matrix<double> mPlus = matrix + matrx1;
    //std::cout << mPlus;
    //Matrix otherMatrix(3, 1, 1);
    //otherMatrix.print();
    //Matrix result = matrix & otherMatrix;
    //result.print();
    return 0;
}