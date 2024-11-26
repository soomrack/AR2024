#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
struct Matrix {
    size_t rows;
    size_t cols;
    double* data;
};

typedef struct Matrix Matrix;


enum MatrixExceptionLevel { ERROR, WARNING, INFO, DEBUG };


void matrix_exception(const enum MatrixExceptionLevel level, const char* msg)
{
    if (level == 0) {
        printf("ERROR: %s", msg);
    }

    if (level == 1) {
        printf("WARNING: %s", msg);
    }
}


Matrix matrix_allocate(const size_t rows, const size_t cols)
{
    Matrix A = { 0, 0, NULL };

    if (rows == 0 || cols == 0) {
        return { rows, cols, NULL };
    }

    A.data = (double*)malloc(rows * cols * sizeof(double));

    if (A.data == NULL) {
        matrix_exception(ERROR, "Allocation memory fail.");
        return A;
    }

    if (rows > SIZE_MAX / cols || rows * cols > SIZE_MAX / sizeof(double)) {
        matrix_exception(ERROR, "Memory fail: owerflow");
        return A;
    }

    A.rows = rows;
    A.cols = cols;
    return A;
}


void matrix_free(Matrix* A)
{
    free((*A).data);
    *A = { 0, 0, NULL };
}


void matrix_set(const Matrix A, const double* values)
{
    memcpy(A.data, values, A.rows * A.cols * sizeof(double));
}


void matrix_print(const Matrix A)
{
    for (size_t row = 0; row < A.rows; ++row) {
        for (size_t col = 0; col < A.cols; ++col) {
            printf(" % 2.3f", A.data[row * A.cols + col]);
        }
        printf("\n");
    }
    printf("\n");
}




int matrix_add(const Matrix A, const Matrix B, const Matrix C)
{
    if (!((A.cols == B.cols) && (A.rows == B.rows))) {
        matrix_exception(ERROR, "matrix_add: incompatible sizes.\n \n");
        return (0);
    }

    for (size_t idx = 0; idx < A.rows * A.cols; ++idx) {
        C.data[idx] = A.data[idx] + B.data[idx];
    }
    printf("A + B =\n");
    matrix_print(C);
    return 1;
}


int matrix_subtraction(const Matrix A, const Matrix B, const Matrix C)
{
    if (!((A.cols == B.cols) && (A.rows == B.rows))) {
        matrix_exception(ERROR, "matrix_subtraction: incompatible sizes.\n \n");
        return (0);
    }


    for (size_t idx = 0; idx < A.rows * A.cols; ++idx) {
        C.data[idx] = A.data[idx] - B.data[idx];
    }
    printf("A - B =\n");
    matrix_print(C);
    return 1;
}
int main()
{
    Matrix A, B, C;
    A = matrix_allocate(4, 4);
    B = matrix_allocate(4, 4);
    double valuesA[] = {
      5., 2., 3., 7.,
      2., -2., 5., 7.,
       3., 4., 2., 7.,
       7., 7., 7., 7.
    };
    double valuesB[] = {
        2., 3., 3., 1.,
        -3., 2., 1., 2.,
        -2., 5., 1., 3.,
        4., 5., 6., 7.
    };
    matrix_set(A, valuesA);
    matrix_set(B, valuesB);
    matrix_print(A);
    matrix_print(B);

    C = matrix_allocate(A.rows, A.cols);
    matrix_add(A, B, C);
    matrix_free(&C);

    C = matrix_allocate(A.rows, A.cols);
    matrix_subtraction(A, B, C);
    matrix_free(&C);

    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);
    return 0;
}