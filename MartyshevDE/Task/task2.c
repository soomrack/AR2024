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


enum MatrixException {ERROR};
typedef enum MatrixException MatrixException;


void matrix_exception(const MatrixException code, char* msg)
{
    if(code == ERROR) {
        printf("ERROR: %s\n", msg);   // Ошибка
    }
} 


Matrix matrix_allocate (size_t cols, size_t rows) 
{
    Matrix A = {cols, rows, NULL};  
    A.data = (double*)malloc(cols * rows * sizeof(double)); 
    
    if (cols == 0 || rows == 0) {
        matrix_exception(ERROR, "Matrix dimensions must be greater than 0");    
        return (Matrix){cols, rows, NULL};
    }

    if (cols > SIZE_MAX / rows || (cols * rows) > SIZE_MAX / sizeof(double)) {
        matrix_exception(ERROR, "Matrix size exceeds allowable memory limit");  
        return (Matrix){0, 0, NULL};
    }

    if (A.data == NULL) {
        matrix_exception(ERROR, "Unable to allocate memory");  
        return(Matrix){0, 0, NULL};
    }
    
    return A;
}


void matrix_free (Matrix* A) 
{
    free (A->data);
    *A = (Matrix){0, 0, NULL};

}

// Функция для доступа к элементу матрицы
double matrix_get (Matrix A, size_t row, size_t col) 
{
    return A.data [A.cols * row + col];
}

// Функция для установки значения в элемент матрицы
void matrix_set(const Matrix A, const double *values)
{
    memcpy(A.data, values, A.rows * A.cols * sizeof(double));
}

// return A += B
Matrix matrix_add (const Matrix A, const Matrix B) 
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
Matrix matrix_subtract (Matrix A, Matrix B) 
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
Matrix matrix_scalar_multiply (Matrix A, double scalar) 
{
    Matrix result = matrix_allocate (A.cols, A.rows);
    
    for (size_t idx = 0; idx < result.rows * result.cols; ++idx) {
        result.data[idx] = A.data[idx] * scalar;
    }
    return result;
}

// A *= B
Matrix matrix_multiply (Matrix A, Matrix B) 
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


void matrix_print (Matrix A) 
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

    
    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);
    matrix_free(&D);
    matrix_free(&E);
    matrix_free(&F);

    return 0;
}