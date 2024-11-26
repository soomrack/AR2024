#include "matrix.hpp"

#include <iostream>
#include <stdexcept>

Matrix::Matrix(double* data, size_t rowSize, size_t colSize) {
    this->colSize = colSize;
    this->rowSize = rowSize;
    this->data = new double[colSize * rowSize];

    for (int i = 0; i < colSize * rowSize; i++) {
        this->data[i] = data[i];
    }
}

Matrix Matrix::sum(Matrix& matrix) {
    if ((this->rowSize != matrix.rowSize) || (this->colSize != matrix.colSize)) {
        throw std::runtime_error("Попытка сложения матриц разной размерности");
    }

    double newData[this->rowSize * this->colSize];

    for (int i = 0; i < this->rowSize * this->colSize; i++) {
        newData[i] = this->data[i] + matrix.data[i];
    }

    return Matrix(newData, this->colSize, this->rowSize);
}

Matrix Matrix::sub(Matrix& matrix) {
    if ((this->rowSize != matrix.rowSize) || (this->colSize != matrix.colSize)) {
        throw std::runtime_error("Попытка вычитания матриц разной размерности");
    }

    double newData[this->rowSize * this->colSize];

    for (int i = 0; i < this->rowSize * this->colSize; i++) {
        newData[i] = this->data[i] - matrix.data[i];
    }

    return Matrix(newData, this->colSize, this->rowSize);
}

Matrix Matrix::mul(Matrix& matrix) {
    if (this->colSize != matrix.rowSize) {
        throw std::runtime_error("Для умножения матриц число столбцов первой матрицы должно быть равно числу строк второй");
    }

    size_t newColSize = matrix.colSize;
    size_t newRowSize = this->rowSize;
    double newData[newColSize * newRowSize];

    for (int i = 0; i < newRowSize; i++) {
        for (int j = 0; j < newColSize; j++) {
            newData[i * newColSize + j] = 0;
            
            for (int k = 0; k < this->colSize; k++) {
                newData[i * newColSize + j] += this->data[i * this->colSize + k] * matrix.data[k * matrix.colSize + j];
            }
        }
    }

    return Matrix(newData, newRowSize, newColSize);
}

void Matrix::print() {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            std::cout << data[i * colSize + j] << " ";
        }
        std::cout << "\n";
    }
}

Matrix::~Matrix() {
    delete[] data;
}
