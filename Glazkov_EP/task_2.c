
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <math.h>


struct Matrix {
    size_t columns;
    size_t rows;
    double *data;
};
typedef struct Matrix Matrix;


enum MatrixError {MATRIX_ERROR};
typedef enum MatrixError MatrixError;

int factorial(double n)
{
    for (int i = 1; i<=n; i++)
    {
        n = n * i;
    }
    return n;
}


void handle_matrix_error(const MatrixError code, char* message) {
    if (code == MATRIX_ERROR) {
        printf("ERROR: %s\n", message);
    }
}


Matrix create_matrix(size_t columns, size_t rows) {
    Matrix mat = {columns, rows, NULL};

    if (columns == 0 || rows == 0) {
        handle_matrix_error(MATRIX_ERROR, "Matrix dimensions must be greater than 0");
        return (Matrix){columns, rows, NULL};
    }

    if (columns > SIZE_MAX / rows || (columns * rows) > SIZE_MAX / sizeof(double)) {
        handle_matrix_error(MATRIX_ERROR, "Matrix size exceeds allowable memory limit");
        return (Matrix){0, 0, NULL};
    }

    mat.data = (double*)malloc(columns * rows * sizeof(double));

    if (mat.data == NULL) {
        handle_matrix_error(MATRIX_ERROR, "Unable to allocate memory");
        return (Matrix){0, 0, NULL};
    }

    return mat;
}


void release_matrix(Matrix* mat) {
    if (mat == NULL) return;
    free(mat->data);
    *mat = (Matrix){0, 0, NULL};
}


void set_matrix_values(const Matrix mat, const double* values) {
    memcpy(mat.data, values, mat.rows * mat.columns * sizeof(double));
}


double get_matrix_value(const Matrix mat, size_t row, size_t column) {
    return mat.data[mat.columns * row + column];
}


void set_matrix_data (const Matrix mat, size_t row, size_t column, double value) {
    if (row >= mat.rows || column >= mat.columns) {
        handle_matrix_error(MATRIX_ERROR, "Invalid index for setting data");
        return;
    }
    mat.data[mat.columns * row + column] = value;
}


Matrix add_matrices(const Matrix matA, const Matrix matB) {
    if (matA.rows != matB.rows || matA.columns != matB.columns) {
        handle_matrix_error(MATRIX_ERROR, "The dimensions of the matrices do not match for addition");
        return (Matrix){0, 0, NULL};
    }

    Matrix result = create_matrix(matA.columns, matA.rows);

    for (size_t idx = 0; idx < result.rows * result.columns; ++idx) {
        result.data[idx] = matA.data[idx] + matB.data[idx];
    }
    return result;
}


Matrix subtract_matrices(const Matrix matA, const Matrix matB) {
    if (matA.rows != matB.rows || matA.columns != matB.columns) {
        handle_matrix_error(MATRIX_ERROR, "The sizes of the matrices do not match for subtraction");
        return (Matrix){0, 0, NULL};
    }

    Matrix result = create_matrix(matA.columns, matA.rows);

    for (size_t idx = 0; idx < result.rows * result.columns; ++idx) {
        result.data[idx] = matA.data[idx] - matB.data[idx];
    }
    return result;
}


Matrix multiply_matrix_by_scalar(const Matrix mat, double scalar) {
    Matrix result = create_matrix(mat.columns, mat.rows);

    for (size_t idx = 0; idx < result.rows * result.columns; ++idx) {
        result.data[idx] = mat.data[idx] * scalar;
    }
    return result;
}


Matrix multiply_matrices(const Matrix matA, const Matrix matB) {
    if (matA.columns != matB.rows) {
        handle_matrix_error(MATRIX_ERROR, "The number of columns of the first matrix is not equal to the number of rows of the second matrix");
        return (Matrix){0, 0, NULL};
    }

    Matrix result = create_matrix(matB.columns, matA.rows);

    for (size_t row = 0; row < result.rows; row++) {
        for (size_t column = 0; column < result.columns; column++) {
            result.data[row * result.columns + column] = 0.0;
            for (size_t idx = 0; idx < matA.columns; idx++) {
                result.data[row * result.columns + column] += matA.data[row * matA.columns + idx] * matB.data[idx * matB.columns + column];
            }
        }
    }
    return result;
}


Matrix create_identity_matrix(size_t size) {
    Matrix identity = create_matrix(size, size);

    for (size_t idx = 0; idx < size * size; idx += size + 1) {
        identity.data[idx] = 1.0;
    }

    return identity;
}


Matrix calculate_matrix_exponential(const Matrix mat) {
    if (mat.columns != mat.rows) {
        handle_matrix_error(MATRIX_ERROR, "Matrix must be square for exponentiation");
        return (Matrix){0, 0, NULL};
    }

    Matrix result = create_identity_matrix(mat.columns);
    Matrix term = create_identity_matrix(mat.columns);

    for (size_t n = 1; n <= 20; ++n) {
        Matrix old_term = term;
        term = multiply_matrices(term, mat);
        release_matrix(&old_term);

        Matrix scaled_term = multiply_matrix_by_scalar(term, 1.0 / factorial(n));

        Matrix old_result = result;
        result = add_matrices(result, scaled_term);
        release_matrix(&old_result);

        release_matrix(&scaled_term);
    }

    release_matrix(&term);

    return result;
}


void print_matrix(const Matrix mat) {
    for (size_t row = 0; row < mat.rows; row++) {
        for (size_t column = 0; column < mat.columns; column++) {
            printf("%2.1f ", get_matrix_value(mat, row, column));
        }
        printf("\n");
    }
}


int main() {
    Matrix matA, matB;
    matA = create_matrix(2, 2);
    matB = create_matrix(2, 2);

    set_matrix_values(matA, (double[]){
        34., 65.,
        13., 9.
    });
    set_matrix_values(matB, (double[]){
        7., 86.,
        35., 26.
    });

    printf("Matrix A:\n");
    print_matrix(matA);

    printf("Matrix B:\n");
    print_matrix(matB);

    Matrix matC = add_matrices(matA, matB);
    printf("A + B:\n");
    print_matrix(matC);

    Matrix matD = subtract_matrices(matA, matB);
    printf("A - B:\n");
    print_matrix(matD);

    Matrix matE = multiply_matrix_by_scalar(matA, 2.0);
    printf("A * scalar:\n");
    print_matrix(matE);

    Matrix matF = multiply_matrices(matA, matB);
    printf("A * B:\n");
    print_matrix(matF);

    Matrix expA = calculate_matrix_exponential(matA);
    printf("e^A:\n");
    print_matrix(expA);

    release_matrix(&matA);
    release_matrix(&matB);
    release_matrix(&matC);
    release_matrix(&matD);
    release_matrix(&matE);
    release_matrix(&matF);
    release_matrix(&expA);

    return 0;
}
