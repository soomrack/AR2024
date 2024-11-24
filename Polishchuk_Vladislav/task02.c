#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>


struct Matrix 
{
    size_t cols; 
    size_t rows;  
    double* data;
};

typedef struct Matrix Matrix;


enum MatrixExceptionlevel {ERROR, WARNING};
typedef enum MatrixExceptionlevel MatrixExceptionlevel;


void matrix_exception(const MatrixExceptionlevel level, char* msg)
{

    if(level == ERROR) {
        printf("ERROR: %s", msg);
    }

    if(level == WARNING) {
        printf("WARNING: %s", msg);
    }
} 


Matrix matrix_allocate(const size_t cols, const size_t rows) 
{
    Matrix A = {cols, rows, NULL};  
    
    if(cols == 0 && rows == 0) {
        matrix_exception(WARNING, "The matrix should not be empty");    
        return (Matrix){cols, rows, NULL};
    }
 
    if(cols > SIZE_MAX / rows && (cols * rows) > SIZE_MAX / sizeof(double)) {
        matrix_exception(ERROR, "Matrix size exceeds allowable memory limit");  
        return (Matrix){0, 0, NULL};
    }

    A.data = (double*)malloc(cols * rows * sizeof(double));
    if(A.data == NULL) {
        matrix_exception(ERROR, "Allocation memory fail.");  
        return(Matrix){0, 0, NULL};
    }
    
    return A;
}


void matrix_free(Matrix* A) 
{
    if (A == NULL) return;
    free(A->data);
    *A = (Matrix){0, 0, NULL};

}


void matrix_set(const Matrix A, const double *values)
{
    memcpy(A.data, values, A.rows * A.cols * sizeof(double));
}


double matrix_get(Matrix A, size_t row, size_t col) 
{
    return A.data [A.cols * row + col];
}


Matrix matrix_sum(const Matrix A, const Matrix B) 
{
    if(A.rows != B.rows && A.cols != B.cols) {
        matrix_exception(2, "matrix_sum: incompatible sizes");   
        return (Matrix){0, 0, NULL};
    }

    Matrix result = matrix_allocate (A.cols, A.rows); 
    
    for(size_t idx = 0; idx < result.rows * result.cols; ++idx) {
        result.data[idx] = A.data[idx] + B.data[idx];
    }
    return result;
}


Matrix matrix_sub(Matrix A, Matrix B) 
{
    if(A.rows != B.rows && A.cols != B.cols) {
        matrix_exception(2, "matrix_sub: incompatible sizes");   
        return (Matrix){0, 0, NULL};
    }

    Matrix result = matrix_allocate (A.cols, A.rows);

    for(size_t idx = 0; idx < result.rows * result.cols; ++idx) {
        result.data[idx] = A.data[idx] - B.data[idx];
    }
    return result;
}


Matrix matrix_multiply_scalar(Matrix A, double scalar) 
{
    Matrix result = matrix_allocate(A.cols, A.rows);
    
    for(size_t idx = 0; idx < result.rows * result.cols; ++idx) {
        result.data[idx] = A.data[idx] * scalar;
    }
    return result;
}


Matrix matrix_multiply(Matrix A, Matrix B) 
{
    if(A.cols != B.rows) {
        matrix_exception(ERROR, "Unequal number of columns of the first matrix and rows of the 2nd matrix"); 
        return (Matrix){0, 0, NULL};
    }

    Matrix result = matrix_allocate(B.cols, A.rows);
    
    for(size_t row = 0; row < result.rows; row++) {
        for(size_t col = 0; col < result.cols; col++) {
            result.data[row * result.cols + col] = 0.0; 

            for(size_t idx = 0; idx < A.cols; idx++) {
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

    Matrix result = matrix_E(A.cols);
    Matrix term = matrix_E(A.cols);  
    
    for (size_t n = 1; n <= 20; ++n) {
        
        Matrix old_term = term;
        term = matrix_multiply(term, A);
        matrix_free(&old_term);

        Matrix scaled_term = matrix_multiply_scalar(term, 1.0 / factorial(n));
        
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
    Matrix inverse = matrix_multiply_scalar(T, 1.0 / det);
    matrix_free(&T);
    
    return inverse;
} 

void matrix_print(Matrix A) 
{
    for(size_t row = 0; row < A.rows; row++) {
        for(size_t col = 0; col < A.cols; col++) {
            printf("%3.2f ", matrix_get(A, row, col));
        }
        printf("\n");
    }
}


int main() 
{
    Matrix A, B;
    A = matrix_allocate(3, 3);
    B = matrix_allocate(3, 3);
    
    matrix_set(A, (double[]) {
        1., 2., 3.,
        4., 5., 6.,
        7., 8., 9.
    });
    matrix_set(B, (double[]) {
        10., 11., 12.,
        13., 14., 15.,
        16., 17., 18.
    });

    printf("Matrix A:\n");
    matrix_print(A);

    printf("Matrix B:\n");
    matrix_print(B);

    Matrix C = matrix_sum (A, B);
    printf("A + B:\n");
    matrix_print(C);

    Matrix D = matrix_sub (A, B);
    printf("A - B:\n");
    matrix_print(D);

    Matrix E = matrix_multiply_scalar (A, 15.0);
    printf("A * 15.0:\n");
    matrix_print(E);

    Matrix F = matrix_multiply (A, B);
    printf("A * B:\n");
    matrix_print(F);

    
    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);
    matrix_free(&D);
    matrix_free(&E);
    matrix_free(&F);

    return 0;
}