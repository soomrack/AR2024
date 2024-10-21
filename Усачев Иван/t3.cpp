#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

struct Matrix {
    size_t rows;
    size_t cols;
    double* data;
};

typedef struct Matrix Matrix;


enum MatrixExceptionLevel { ERROR, WARNING, INFO, DEBUG };


void matrix_exception(const enum MatrixExceptionLevel level, const char *msg)
{
    if (level == ERROR) {
        printf("ERROR: %s", msg);
    }

    if (level == WARNING) {
        printf("WARNING: %s", msg);
    }
}


Matrix matrix_allocate(const size_t rows, const size_t cols)
{
    Matrix A = { 0, 0, NULL };

    if (rows == 0 || cols == 0) {
        return { rows, cols, NULL };
    }

    A.data = (double*) malloc(rows * cols * sizeof(double));  // TODO: check for overflow
    if (A.data == NULL) {
        matrix_exception(ERROR, "Allocation memory fail.");
        return A;
    }

    A.rows = rows;
    A.cols = cols;
    return A;
}


void matrix_free(Matrix* A)
{
    free(A->data);  // free( (*A).data  )
    *A = { 0, 0, NULL };
}



// no checks at all
void matrix_set(const Matrix A, const double* values)
{
    memcpy(A.data, values, A.rows * A.cols * sizeof(double));
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


// A += B
int matrix_add(const Matrix A, const Matrix B)
{
    if (!((A.cols == B.cols) && (A.rows == B.rows))) {
        matrix_exception(ERROR, "matrix_add: incompatible sizes.");
        return 0;
    }
    for (size_t idx = 0; idx < A.rows * A.cols; ++idx) {
        A.data[idx] += B.data[idx];
    }
    return 1;
}


int main()
{
    Matrix A, B;
    A = matrix_allocate(3, 3);  // TODO: check for allocated
    B = matrix_allocate(3, 3);  // TODO: check for allocated
    double valuesA[] = { 
        1., 2., 3.,
        3., 4., 5.,
        6., 7., 8.
    };
    double valuesB[] = {
        1., 0., 0.,
        0., 1., 0.,
        0., 0., 1.
    };
    matrix_set(A, valuesA);
    matrix_set(B, valuesB);
    matrix_print(A);
    matrix_print(B);

    matrix_add(A, B);
    matrix_print(A);

    matrix_free(&A);
    matrix_free(&B);
    return 1;
}
