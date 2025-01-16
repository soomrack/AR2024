#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <math.h>


struct Matrix
{
    size_t cols;
    size_t rows;
    double* data;
};
typedef struct Matrix Matrix;


enum MatrixException { ERROR };
typedef enum MatrixException MatrixException;


// 打印矩阵异常信息
void matrix_exception(const MatrixException code, char* msg)
{
    if (code == ERROR) {
        printf("ERROR: %s\n", msg);
    }
}


// 分配矩阵内存
Matrix matrix_allocate(size_t cols, size_t rows)
{
    Matrix A = { cols, rows, NULL };

    if (cols == 0 || rows == 0) {
        matrix_exception(ERROR, "Matrix dimensions must be greater than 0");
        return (Matrix) { cols, rows, NULL };
    }

    if (cols > SIZE_MAX / rows || (cols * rows) > SIZE_MAX / sizeof(double)) {
        matrix_exception(ERROR, "Matrix size exceeds allowable memory limit");
        return (Matrix) { 0, 0, NULL };
    }

    A.data = (double*)malloc(cols * rows * sizeof(double));

    if (A.data == NULL) {
        matrix_exception(ERROR, "Unable to allocate memory");
        return(Matrix) { 0, 0, NULL };
    }

    return A;
}


// 释放矩阵内存
void matrix_free(Matrix* A)
{
    if (A == NULL) return;
    free(A->data);
    *A = (Matrix){ 0, 0, NULL };
}


// 获取矩阵元素
double matrix_get(const Matrix A, size_t row, size_t col)
{
    return A.data[A.cols * row + col];
}


// 设置矩阵元素
void matrix_set_element(const Matrix A, size_t row, size_t col, double value) {
    if (row >= A.rows || col >= A.cols) {
        matrix_exception(ERROR, "Invalid index for setting element");
        return;
    }
    A.data[A.cols * row + col] = value;
}


// 填充矩阵元素
void matrix_set(const Matrix A, const double* values)
{
    memcpy(A.data, values, A.rows * A.cols * sizeof(double));
}


// 矩阵相加 A + B
Matrix matrix_add(const Matrix A, const Matrix B)
{
    if (A.rows != B.rows || A.cols != B.cols) {
        matrix_exception(ERROR, "The dimensions of the matrices do not match for addition");
        return (Matrix) { 0, 0, NULL };
    }

    Matrix result = matrix_allocate(A.cols, A.rows);

    for (size_t idx = 0; idx < result.rows * result.cols; ++idx) {
        result.data[idx] = A.data[idx] + B.data[idx];
    }
    return result;
}


// 矩阵相减 A - B
Matrix matrix_subtract(const Matrix A, const Matrix B)
{
    if (A.rows != B.rows || A.cols != B.cols) {
        matrix_exception(ERROR, "The sizes of the matrices do not match for subtraction");
        return (Matrix) { 0, 0, NULL };
    }

    Matrix result = matrix_allocate(A.cols, A.rows);

    for (size_t idx = 0; idx < result.rows * result.cols; ++idx) {
        result.data[idx] = A.data[idx] - B.data[idx];
    }
    return result;
}


// 矩阵数乘 A * scalar
Matrix matrix_scalar_multiply(const Matrix A, double scalar)
{
    Matrix result = matrix_allocate(A.cols, A.rows);

    for (size_t idx = 0; idx < result.rows * result.cols; ++idx) {
        result.data[idx] = A.data[idx] * scalar;
    }
    return result;
}


// 矩阵相乘 A * B
Matrix matrix_multiply(const Matrix A, const Matrix B)
{
    if (A.cols != B.rows) {
        matrix_exception(ERROR, "The number of columns of the first matrix is not equal to the number of rows of the second matrix");
        return (Matrix) { 0, 0, NULL };
    }

    Matrix result = matrix_allocate(B.cols, A.rows);

    for (size_t row = 0; row < result.rows; row++) {
        for (size_t col = 0; col < result.cols; col++) {
            result.data[row * result.cols + col] = 0.0;
            for (size_t idx = 0; idx < A.cols; idx++) {
                result.data[row * result.cols + col] += A.data[row * A.cols + idx] * B.data[idx * B.cols + col];
            }
        }
    }
    return result;
}


// 计算阶乘
size_t factorial(size_t n)
{
    size_t result = 1;
    for (size_t i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}


// 生成单位矩阵
Matrix matrix_E(size_t size)
{
    Matrix I = matrix_allocate(size, size);
    for (size_t idx = 0; idx < size * size; idx += size + 1) {
        I.data[idx] = 1.0;
    }
    return I;
}


// 矩阵指数运算
Matrix matrix_exp(const Matrix A)
{
    if (A.cols != A.rows) {
        matrix_exception(ERROR, "Matrix must be square for exponentiation");
        return (Matrix) { 0, 0, NULL };
    }

    Matrix result = matrix_E(A.cols); // E
    Matrix term = matrix_E(A.cols);   // A^0 / 0!

    for (size_t n = 1; n <= 20; ++n) {
        Matrix old_term = term;
        term = matrix_multiply(term, A);
        matrix_free(&old_term);

        Matrix scaled_term = matrix_scalar_multiply(term, 1.0 / factorial(n));
        Matrix old_result = result;
        result = matrix_add(result, scaled_term);
        matrix_free(&old_result);
        matrix_free(&scaled_term);
    }
    matrix_free(&term);

    return result;
}


// 计算矩阵的余子矩阵
Matrix matrix_minor(const Matrix A, size_t row, size_t col)
{
    Matrix minor = matrix_allocate(A.cols - 1, A.rows - 1);
    if (minor.data == NULL) {
        matrix_exception(ERROR, "Memory allocation failed for minor");
        return (Matrix) { 0, 0, NULL };
    }
    size_t idx = 0;
    for (size_t rows = 0; rows < A.rows; ++rows) {
        if (rows == row) continue;
        for (size_t cols = 0; cols < A.cols; ++cols) {
            if (cols == col) continue;
            minor.data[idx++] = A.data[rows * A.cols + cols];
        }
    }
    return minor;
}


// 计算矩阵的行列式
double matrix_determinant(const Matrix A)
{
    if (A.cols != A.rows) {
        matrix_exception(ERROR, "Matrix must be square for determinant calculation");
        return NAN;
    }

    if (A.rows == 2 && A.cols == 2) {
        return A.data[0] * A.data[3] - A.data[1] * A.data[2];
    }

    double det = 0.0;
    for (size_t col = 0; col < A.cols; ++col) {
        Matrix subMatrix = matrix_minor(A, 0, col);
        double znak = (col % 2 == 0 ? 1 : -1) * A.data[col];
        det += znak * matrix_determinant(subMatrix);
        matrix_free(&subMatrix);
    }
    return det;
}


// 矩阵转置
Matrix matrix_T(const Matrix A)
{
    Matrix T = matrix_allocate(A.cols, A.rows);

    for (size_t row = 0; row < A.rows; ++row) {
        for (size_t col = 0; col < A.cols; ++col) {
            T.data[col * T.rows + row] = A.data[row * A.cols + col];
        }
    }
    return T;
}


// 计算矩阵元素的代数余子式
double matrix_cofactor(const Matrix m, size_t row, size_t col)
{
    Matrix minor = matrix_allocate(m.rows - 1, m.cols - 1);
    if (minor.data == NULL) {
        matrix_exception(ERROR, "Memory allocation failed for minor");
        return NAN;
    }
    size_t idx = 0;
    for (size_t r = 0; r < m.rows; ++r) {
        for (size_t c = 0; c < m.cols; ++c) {
            if (r == row || c == col) continue;
            minor.data[idx++] = m.data[r * m.cols + c];
        }
    }
    double cofactor = pow(-1, row + col) * matrix_determinant(minor);
    matrix_free(&minor);
    return cofactor;
}


// 计算矩阵的余子式矩阵
Matrix matrix_get_cofactor_(Matrix m)
{
    Matrix cofactor_matrix = matrix_allocate(m.rows, m.cols);
    if (cofactor_matrix.data == NULL) {
        matrix_exception(ERROR, "Memory allocation failed for cofactor matrix");
        return (Matrix) { 0, 0, NULL };
    }
    for (size_t row = 0; row < m.rows; row++) {
        for (size_t col = 0; col < m.cols; col++) {
            matrix_set_element(cofactor_matrix, row, col, matrix_cofactor(m, row, col));
        }
    }
    return cofactor_matrix;
}


// 矩阵求逆
Matrix matrix_inverse_a(const Matrix m)
{
    if (matrix_determinant(m) == 0) {
        matrix_exception(ERROR, "Matrix is not invertible");
        return (Matrix) { 0, 0, NULL };
    }
    Matrix inv_m = matrix_get_cofactor_(m);
    Matrix transpose_inv_m = matrix_T(inv_m);
    Matrix scalar_inverse = matrix_scalar_multiply(transpose_inv_m, 1 / matrix_determinant(m));
    matrix_free(&inv_m);
    matrix_free(&transpose_inv_m);
    return scalar_inverse;
}


// 打印矩阵元素
void matrix_print(const Matrix A)
{
    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            printf("%2.1f ", matrix_get(A, row, col));
        }
        printf("\n");
    }
}


int main()
{
    Matrix A, B;
    A = matrix_allocate(2, 2);
    B = matrix_allocate(2, 2);

    matrix_set(A, (double[]) {
        17., 39.,
            98., 75.
    });
    matrix_set(B, (double[]) {
        93., 5.,
            8., 89.
    });

    printf("Matrix A:\n");
    matrix_print(A);

    printf("Matrix B:\n");
    matrix_print(B);

    Matrix C = matrix_add(A, B);
    printf("A + B:\n");
    matrix_print(C);

    Matrix D = matrix_subtract(A, B);
    printf("A - B:\n");
    matrix_print(D);

    Matrix E = matrix_scalar_multiply(A, 2.0);
    printf("A * scalar:\n");
    matrix_print(E);

    Matrix F = matrix_multiply(A, B);
    printf("A * B:\n");
    matrix_print(F);

    Matrix expA = matrix_exp(A);
    printf("e^A:\n");
    matrix_print(expA);

    double detA = matrix_determinant(A);
    printf("Determinant of A: %f\n", detA);

    Matrix invA = matrix_inverse_a(A);
    printf("Inverse of A: \n");
    matrix_print(invA);

    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);
    matrix_free(&D);
    matrix_free(&E);
    matrix_free(&F);
    matrix_free(&expA);
    matrix_free(&invA);

    return 0;
}