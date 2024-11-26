#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iosfwd>

class Matrix {
public:
    Matrix(double* data, size_t rowSize, size_t colSize);
    ~Matrix();

    Matrix sum(Matrix& matrix);
    Matrix sub(Matrix& matrix);
    Matrix mul(Matrix& matrix);
    void print();
private:
    size_t colSize;
    size_t rowSize;
    double* data;
};

#endif
