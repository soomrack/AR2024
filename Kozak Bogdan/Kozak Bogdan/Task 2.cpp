##include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>


#define ERROR 1
#define WARNING 2


typedef struct Matrix Matrix;


struct Matrix
{
    size_t cols;
    size_t rows;
    double* data;
};


void matrix_set(Matrix A, const double* values) {
    memcpy(A.data, values, A.rows * A.cols * sizeof(double));
}


void matrix_error(int error_code, const char* message) {
    fprintf(stderr, "Error %d: %s\n", error_code, message);
}

Matrix matrix_allocate(size_t cols, size_t rows) {
    if (cols == 0 || rows == 0) {
        matrix_error(WARNING, "The dimensions of the matrix should be larger than 0");
        return (Matrix) { 0, 0, NULL };
    }

    if (cols > SIZE_MAX / rows || cols * rows > SIZE_MAX / sizeof(double)) {
        matrix_error(ERROR, "The size of the matrix exceeds the allowed memory limit");
        return (Matrix) { 0, 0, NULL };
    }

    Matrix A = { cols, rows, malloc(cols * rows * sizeof(double)) };

    if (A.data == NULL) {
        matrix_error(ERROR, "Memory cannot be allocated");
        return (Matrix) { 0, 0, NULL };
    }

    return A;
}


void matrix_free(Matrix* A) {
    if (A == NULL) {
        return;
    }

    if (A->data != NULL) {
        free(A->data);
        A->data = NULL;
    }

    A->rows = 0;
    A->cols = 0;
}


Matrix matrix_add(const Matrix A, const Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        matrix_error(ERROR, "The dimensions of the matrix do not match for addition");
        return (Matrix) { 0, 0, NULL };
    }

    Matrix C = matrix_allocate(A.cols, A.rows);

    for (size_t elm = 0; elm < C.rows * C.cols; ++elm) {
        C.data[elm] = A.data[elm] + B.data[elm];
    }
    return C;
}


Matrix matrix_sub(const Matrix A, const Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        matrix_error(ERROR, "The dimensions of the matrix do not match for subtraction");
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

    for (size_t elm = 0; elm < D.rows * D.cols; ++elm) {
        D.data[elm] = A.data[elm] * scr;
    }
    return D;
}


Matrix matrix_mul(Matrix A, Matrix B) {
    if (A.cols != B.rows) {
        matrix_error(ERROR, "The number of columns of the first matrix is not equal to the number of rows of the second matrix");
        return (Matrix) { 0, 0, NULL };
    }

    Matrix F = matrix_allocate(A.rows, B.cols);

    for (size_t rows = 0; rows < A.rows; rows++) {
        for (size_t cols = 0; cols < B.cols; cols++) {
            F.data[rows * F.cols + cols] = 0.0;
            for (size_t k = 0; k < A.cols; k++) {
                F.data[rows * F.cols + cols] += A.data[rows * A.cols + k] * B.data[k * B.cols + cols];
            }
        }
    }

    return F;
}


double matrix_minor(const Matrix A, const size_t el_col, const size_t el_row) {
    if (A.cols != A.rows) {
        matrix_error(ERROR, "Matrix must be square to calculate a minor");
        return 0;
    }

    struct Matrix minorMat = matrix_allocate(A.rows - 1, A.cols - 1);
    if (minorMat.data == NULL) {
        matrix_error(ERROR, "Memory cannot be allocated.");
        return 0;
    }

    size_t elm = 0;
    for (size_t rows = 0; rows < A.rows; rows++) {
        if (rows != el_row) {
            for (size_t cols = 0; cols < A.cols; cols++) {
                if (cols != el_col) {
                    minorMat.data[elm++] = A.data[A.cols * rows + cols];
                }
            }
        }
    }

    double det = 0;
    if (minorMat.cols == 2 && minorMat.rows == 2) {
        det = minorMat.data[0] * minorMat.data[3] - minorMat.data[1] * minorMat.data[2];
        free(minorMat.data);
        return det;
    }

    for (size_t col = 0; col < minorMat.cols; col++) {
        double n = ((el_row + col) % 2 == 0) ? 1.0 : -1.0;
        det += minorMat.data[col] * n * matrix_minor(minorMat, col, 0);
    }

    free(minorMat.data);
    return det;
}


double matrix_det(const Matrix A) {
    if (A.cols != A.rows) {
        matrix_error(ERROR, "Matrix must be square to calculate determinant");
        return 0;
    }

    double det = 0.0;

    for (size_t col = 0; col < A.cols; col++) {
        double n = ((0 + col) % 2 == 0) ? 1.0 : -1.0;
        det += A.data[col] * n * matrix_minor(A, col, 0);
    }

    return det;
}


Matrix matrix_E(size_t size) {
    Matrix I = matrix_allocate(size, size);

    for (size_t i = 0; i < size * size; ++i) {
        I.data[i] = 0.0;
    }

    for (size_t i = 0; i < size; ++i) {
        I.data[i * (size + 1)] = 1.0;
    }

    return I;
}


Matrix matrix_exp(Matrix A) {
    if (A.cols != A.rows) {
        matrix_error(ERROR, "Matrix must be square for exponentiation");
        return (Matrix) { 0, 0, NULL };
    }

    Matrix exp = matrix_E(A.cols);
    Matrix fimember = matrix_E(A.cols); // (A^0 / 0!)
    struct Matrix current_power = A;


    size_t n = 1;
    double factorial_value = 1.0;

    while (n <= 20) {
        fimember = matrix_mul(fimember, A);
        factorial_value *= n;
        Matrix scaled_fimember = matrix_scr_mul(fimember, 1.0 / factorial_value); // A^n / n!

        exp = matrix_add(exp, scaled_fimember);

        matrix_free(&scaled_fimember);

        ++n;
    }


    return exp;
}


void matrix_print(const Matrix A) {
    for (size_t rows = 0; rows < A.rows; ++rows) {
        for (size_t cols = 0; cols < A.cols; ++cols) {
            printf("%f ", A.data[rows * A.cols + cols]);
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
    printf("The sum of A and B:\n");
    matrix_print(C);

    Matrix D = matrix_sub(A, B);
    printf("Difference of A and B:\n");
    matrix_print(D);

    Matrix E = matrix_scr_mul(A, 7.0);
    printf("Multiplication of A by 7.0:\n");
    matrix_print(E);

    Matrix F = matrix_mul(A, B);
    printf("Multiplication of A and B:\n");
    matrix_print(F);

    Matrix exp = matrix_exp(A);
    printf("Exponential of A (e^A):\n");
    matrix_print(exp);

    Matrix I = matrix_E(A.cols);
    printf("Identity matrix (I):\n");
    matrix_print(I);

    double det = matrix_det(A);
    printf("Determinant of A: %f\n", det);

    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);
    matrix_free(&D);
    matrix_free(&E);
    matrix_free(&F);
    matrix_free(&I);
    matrix_free(&exp);

    return 1;
}
