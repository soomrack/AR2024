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


enum MatrixException {ERROR};
typedef enum MatrixException MatrixException;


void matrix_exception(const MatrixException code, char* msg)
{
    if(code == ERROR) {
        printf("ERROR: %s\n", msg);   
    }
} 


Matrix matrix_allocate(size_t cols, size_t rows) 
{
    Matrix A = {cols, rows, NULL};   
    
    if (cols == 0 || rows == 0) {
        matrix_exception(ERROR, "Matrix dimensions must be greater than 0");    
        return (Matrix){cols, rows, NULL};
    }

    if (cols > SIZE_MAX / rows || (cols * rows) > SIZE_MAX / sizeof(double)) {
        matrix_exception(ERROR, "Matrix size exceeds allowable memory limit");  
        return (Matrix){0, 0, NULL};
    }

    A.data = (double*)malloc(cols * rows * sizeof(double));

    if (A.data == NULL) {
        matrix_exception(ERROR, "Unable to allocate memory");  
        return(Matrix){0, 0, NULL};
    }
    
    return A;
}


void matrix_free(Matrix *A) 
{
    if (A == NULL) return;
    free (A->data);
    *A = (Matrix){0, 0, NULL};
}


double matrix_get(const Matrix A, size_t row, size_t col) 
{
    return A.data[A.cols * row + col];
}


void matrix_set(const Matrix A, const double *values)
{
    memcpy(A.data, values, A.rows * A.cols * sizeof(double));
}


// return A += B
Matrix matrix_add(const Matrix A, const Matrix B) 
{
    if(A.rows != B.rows || A.cols != B.cols) {
        matrix_exception (ERROR, "The dimensions of the matrices do not match for addition");   
        return (Matrix){0, 0, NULL};
    }

    Matrix result = matrix_allocate (A.cols, A.rows); 
    
    for (size_t idx = 0; idx < result.rows * result.cols; ++idx) {
        result.data[idx] = A.data[idx] + B.data[idx];
    }
    return result;
}


// return A -= B
Matrix matrix_subtract(const Matrix A, const Matrix B) 
{
    if (A.rows != B.rows || A.cols != B.cols) {
        matrix_exception (ERROR, "The sizes of the matrices do not match for subtraction");   
        return (Matrix){0, 0, NULL};
    }

    Matrix result = matrix_allocate (A.cols, A.rows);

    for (size_t idx = 0; idx < result.rows * result.cols; ++idx) {
        result.data[idx] = A.data[idx] - B.data[idx];
    }
    return result;
}


// A * scalar
Matrix matrix_scalar_multiply(const Matrix A, double scalar) 
{
    Matrix result = matrix_allocate (A.cols, A.rows);
    
    for (size_t idx = 0; idx < result.rows * result.cols; ++idx) {
        result.data[idx] = A.data[idx] * scalar;
    }
    return result;
}


// A *= B
Matrix matrix_multiply(const Matrix A, const Matrix B) 
{
    if (A.cols != B.rows) {
        matrix_exception (ERROR, "The number of columns of the first matrix is not equal to the number of rows of the second matrix"); 
        return (Matrix){0, 0, NULL};
    }

    Matrix result = matrix_allocate (B.cols, A.rows);
    
    for (size_t row = 0; row < result.rows; row++) {
        for (size_t col = 0; col < result.cols; col++) {
            result.data[row * result.cols + col] = 0.0; 
            for (size_t idx = 0; idx < A.cols; idx++) {
                result.data[row * result.cols + col] += A.data[row * A.cols + idx] * B.data[idx * B.cols  + col]; 
            }
        }
    }
    return result;
}


size_t factorial(size_t n) 
{
    size_t result = 1;
    for (size_t i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}


Matrix matrix_E(size_t size) 
{
    Matrix I = matrix_allocate(size, size);
    for (size_t idx = 0; idx < size * size; idx += size + 1) {
        I.data[idx] = 1.0;
    }
    return I;
}


Matrix matrix_exp(const Matrix A) 
{
    if (A.cols != A.rows) {
        matrix_exception(ERROR, "Matrix must be square for exponentiation");
        return (Matrix){0, 0, NULL};
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


Matrix matrix_minor(const Matrix A, size_t row, size_t col) 
{
    Matrix minor = matrix_allocate(A.cols - 1, A.rows - 1);
    
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


Matrix matrix_T(const Matrix A) 
{
    Matrix T = matrix_allocate(A.cols, A.rows);
    
    for (size_t row = 0; row < A.rows; ++row) {
        for (size_t col = 0; col < A.cols; ++col) {
            Matrix minor = matrix_minor(A, row, col); 
            matrix_free(&minor);
        }
    }
    
    return T;
}


Matrix matrix_inverse(const Matrix A) 
{
    double det = matrix_determinant(A);
    if (det == 0.00001 || det == NAN) {
        matrix_exception(ERROR, "Matrix is singular and cannot be inverted");
        return (Matrix){0, 0, NULL};
    }
    
    Matrix T = matrix_T(A);
    Matrix inverse = matrix_scalar_multiply(T, 1.0 / det);
    matrix_free(&T);
    
    return inverse;
} 


void matrix_print(const Matrix A) 
{
    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            printf ("%2.1f ", matrix_get(A, row, col));
        }
        printf ("\n");
    }
} 


int main() 
{
    Matrix A, B;
    A = matrix_allocate(2, 2);
    B = matrix_allocate(2, 2);
    
    matrix_set(A, (double[]) {
        1., 2.,
        3., 4.
    });
    matrix_set(B, (double[]) {
        5., 6.,
        7., 8.
    });

    printf("Matrix A:\n");
    matrix_print(A);

    printf("Matrix B:\n");
    matrix_print(B);

    Matrix C = matrix_add (A, B);
    printf("The amount A and B:\n");
    matrix_print(C);

    Matrix D = matrix_subtract (A, B);
    printf("Difference A and B:\n");
    matrix_print(D);

    Matrix E = matrix_scalar_multiply (A, 2.0);
    printf("Multiplication A on 2.0:\n");
    matrix_print(E);

    Matrix F = matrix_multiply (A, B);
    printf("Multiplication A on B:\n");
    matrix_print(F);

    Matrix expA = matrix_exp(A);
    printf("Exponential of A (e^A):\n");
    matrix_print(expA);

    double detA = matrix_determinant(A);
    printf("Determinant of A: %f\n", detA);

    Matrix invA = matrix_inverse(A);
    printf("Inverse of A: \n");

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