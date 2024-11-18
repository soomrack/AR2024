#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
setlocale(LC_ALL, "RUS");


struct Matrix
{
    size_t cols;
    size_t rows;
    double* data;
};


void matrix_error(int error_code, const char* message) {
    fprintf(stderr, "Error %d: %s\n", error_code, message);
}

Matrix matrix_allocate(size_t cols, size_t rows)
{
    if (cols == 0 || rows == 0) {
        matrix_error(ERROR, "Размеры матрицы должны быть больше 0");
        return (Matrix) { 0, 0, NULL };
    }


    if (cols > SIZE_MAX / rows || cols * rows > SIZE_MAX / sizeof(double)) {
        matrix_error(ERROR, "Размер матрицы превышает допустимый лимит памяти");
        return (Matrix) { 0, 0, NULL };
    }


    Matrix A = { cols, rows, malloc(cols * rows * sizeof(double)) };


    if (A.data == NULL) {
        matrix_error(ERROR, "Невозможно выделить память");
        return (Matrix) { 0, 0, NULL };
    }

    return A;
}


void matrix_free(Matrix* A)
{
    free(A->data);
    *A = (Matrix){ 0, 0, NULL };

}


Matrix matrix_add(const Matrix A, const Matrix B)
{
    if (A.rows != B.rows || A.cols != B.cols) {
        matrix_error(ERROR, "Размеры матрицы не совпадают для сложения");
        return (Matrix) { 0, 0, NULL };
    }

    Matrix C = matrix_allocate(A.cols, A.rows);

    for (size_t elm = 0; elm < C.rows * C.cols; ++elm) {
        C.data[elm] = A.data[elm] + B.data[elm];
    }
    return C;
}


Matrix matrix_sub(const Matrix A, const Matrix B)
{
    if (A.rows != B.rows || A.cols != B.cols) {
        matrix_error(ERROR, "Размеры матрицы не совпадают для сложения");
        return (Matrix) { 0, 0, NULL };
    }

    Matrix C = matrix_allocate(A.cols, A.rows);

    for (size_t elm = 0; elm < C.rows * C.cols; ++elm) {
        C.data[elm] = A.data[elm] - B.data[elm];
    }
    return C;
}


Matrix matrix_scr_mul(Matrix A, double scr)
{
    Matrix D = matrix_allocate(A.cols, A.rows);

    for (size_t elm = 0; elm < result.rows * result.cols; ++elm) {
        D.data[idx] = A.data[idx] * scr;
    }
    return D;
}


Matrix matrix_mul(Matrix A, Matrix B) {
    if (A.cols != B.rows) {
        matrix_error("ERROR", "Количество столбцов первой матрицы не равно количеству строк второй матрицы");
        return (Matrix) { 0, 0, NULL };
    }

    Matrix F = matrix_allocate(A.rows, B.cols);

    for (size_t i = 0; i < A.rows; i++) {
        for (size_t j = 0; j < B.cols; j++) {
            F.data[i * B.cols + j] = 0.0;

            for (size_t k = 0; k < A.cols; k++) {
                F.data[i * B.cols + j] += A.data[i * A.cols + k] * B.data[k * B.cols + j];
            }
        }
    }

    return F;
}


void matrix_print(const Matrix A)
{
    for (size_t row = 0; row < A.rows; ++row) {
        for (size_t col = 0; col < A.cols; ++col) {
            cout << A.data[row * A.cols + col];
        }
        printf("\n");
    }
    printf("\n");
}


int main() {
    Matrix A, B;
    A = matrix_allocate(3, 3);
    B = matrix_allocate(3, 3);

    matrix_set(A, (double[]) {
        1., 2., 5.,
            3., 4., 6.,
            7., 8., 9.
    });
    matrix_set(B, (double[]) {
        5., 6., 1.,
            7., 8., 2.,
            3., 4., 9.
    });

    printf("Matrix A:\n");
    matrix_print(A);

    printf("Matrix B:\n");
    matrix_print(B);

    Matrix C = matrix_add(A, B);
    printf("The amount A and B:\n");
    matrix_print(C);

    Matrix D = matrix_sub(A, B);
    printf("Difference A and B:\n");
    matrix_print(D);

    Matrix E = matrix_scr_mul(A, 7.0);
    printf("Multiplication A on 7.0:\n");
    matrix_print(E);

    Matrix F = matrix_mul(A, B);
    printf("Multiplication A on B:\n");
    matrix_print(F);

    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);
    matrix_free(&D);
    matrix_free(&E);
    matrix_free(&F);

    return 1;
}