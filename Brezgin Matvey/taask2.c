#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Matrix {
    size_t rows;
    size_t cols;
    double *data;
};
typedef struct Matrix Matrix;


enum MatrixExceptionLevel {ERROR, WARNING, INFO, DEBUG};


void matrix_exception(const enum MatrixExceptionLevel level, char *msg)
{
    if(level == ERROR) {
        printf("ERROR: %s", msg);
    }

    if(level == WARNING) {
        printf("WARNING: %s", msg);
    }
}


Matrix matrix_allocate(const size_t rows, const size_t cols)
{
    Matrix A = {0, 0, NULL};

    if(rows == 0 || cols == 0) {
        return (Matrix){rows, cols, NULL};
    }
   
    A.data = malloc(rows * cols * sizeof(double));  // TODO: check for overflow
    if(A.data == NULL) {
        matrix_exception(ERROR, "Allocation memory fail.");
        return A;
    }

    A.rows = rows;
    A.cols = cols;
    return A;
}


void matrix_free(Matrix *A)
{
    free(A->data);  // free( (*A).data  )
    *A = (Matrix){0, 0, NULL};
}


// no checks at all
void matrix_set(const Matrix A, const double *values)
{
    memcpy(A.data, values, A.rows * A.cols * sizeof(double));
}


void matrix_print(const Matrix A)
{
    for(size_t row = 0; row < A.rows; ++row) {
        for(size_t col = 0; col < A.cols; ++col) {
            printf("%2.3f ", A.data[row * A.cols + col]);
        }
        printf("\n");
    }
    printf("\n");
}

int factorial(int i)
{
  if (i==0) return 1;
  else return i*factorial(i-1);
}


// A += B
int matrix_add(const Matrix A, const Matrix B)
{
    if( !((A.cols == B.cols) && (A.rows == B.rows)) ) {
        matrix_exception(2, "matrix_add: incompatible sizes.");
        return 0;
    }
    
    for(size_t idx = 0; idx < A.rows * A.cols; ++idx) {
        A.data[idx] += B.data[idx];
    }
    return 1;
}


// A -= B
int matrix_sub(const Matrix A, const Matrix B)
{
    if( !((A.cols == B.cols) && (A.rows == B.rows)) ) {
        matrix_exception(2, "matrix_sub: incompatible sizes.");
        return 0;
    }
    
    for(size_t idx = 0; idx < A.rows * A.cols; ++idx) {
        A.data[idx] -= B.data[idx];
    }
    return 1;
}


// A *= B
int matrix_mult(const Matrix A, const Matrix B)
{
    if( !((A.cols == B.cols) && (A.rows == B.rows)) ) {
        matrix_exception(2, "matrix_mult: incompatible sizes.");
        return 0;
    }
    
    for(size_t idx = 0; idx < A.rows * A.cols; ++idx) {
        A.data[idx] *= B.data[idx];
    }
    return 1;
}

// exp 
int matrix_expm(const Matrix A)
{
    Matrix E, I, A1, AE;
    E = matrix_allocate(2, 2); 
    I = matrix_allocate(2, 2);
    A1 = matrix_allocate(2, 2);
    AE = matrix_allocate(2, 2);

    matrix_set(E, (double[]){
            0., 0.,
            0., 0. 
        });
    matrix_set(I, (double[]){
            1., 0.,
            0., 1.
        });
    matrix_set(A1, (double[]){
            0., 0.,
            0., 0.     
        });
    matrix_set(AE, (double[]){
            0., 0.,
            0., 0.     
        });
   
    matrix_add(E, I);
    matrix_add(E, A);
    matrix_add(A1, A);
    matrix_add(AE, A);
    
    
    for (int n = 0; n < 4; n++)
    {
        matrix_mult(A, A1);
        matrix_add(AE,A);
        for (size_t idx = 0; idx < A.rows * A.cols; ++idx) {
            A.data[idx] /= factorial(n);
        }
        return 1; 
        
        matrix_add(E, AE);
        
        matrix_free(&AE);
        AE = matrix_allocate(2, 2);
            matrix_set(AE, (double[]){
            0., 0.,
            0., 0.     
        });
    }

    matrix_print(E);
    return 1;
}







int main()
{
    Matrix A, B;
    A = matrix_allocate(2, 2);  // TODO: check for allocated
    B = matrix_allocate(2, 2);  // TODO: check for allocated
     
    matrix_set(A, (double[]){
            1., 2.,
            3., 4. 
            
        });
    matrix_set(B, (double[]){
            1., 2.,
            5., 1.
        });
    matrix_print(A);
    matrix_print(B);

    matrix_add(A, B);
    matrix_print(A);

    matrix_free(&A);

    A = matrix_allocate(2, 2);
    matrix_set(A, (double[]){
            1., 2.,
            3., 4.         
        });

    matrix_sub(A, B);
    matrix_print(A);

    matrix_free(&A);

    A = matrix_allocate(2, 2);
    matrix_set(A, (double[]){
            1., 2.,
            3., 4.         
        });

    matrix_mult(A, B);
    matrix_print(A);

    matrix_free(&A);

    A = matrix_allocate(2, 2);
    matrix_set(A, (double[]){
            1., 2.,
            3., 4.         
        });

    matrix_expm(A);
    return 1;
}