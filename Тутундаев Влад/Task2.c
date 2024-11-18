#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct Matrix {
    size_t rows;
    size_t cols;
    double *data;
};


typedef struct Matrix Matrix;


Matrix matrix_alloc( const size_t rows, const size_t cols)
{
    Matrix A = {0, 0, NULL};

    if ( (double)(rows / SIZE_MAX * cols * 1.) >= (double)(1. / sizeof(double)) || rows * cols == 0)
    {
       printf("the matrix size is not correct.");
       return A;
    } 

    A.data = malloc(sizeof(double) * rows * cols);
    
    if ( A.data == NULL){
        printf("Allocation memory fail.");
        return A;
    }

    A.rows = rows;
    A.cols = cols;

    return A;
   
}


void matrix_fill(const Matrix A, double *arr)
{
    memcpy(A.data, arr, A.cols * A.rows * sizeof(double));
}


void matrix_free(Matrix *A)
{
    free(A->data);
    *A = (Matrix){0, 0, NULL};
}


void matrix_print( const Matrix A)
{
    for (size_t rows = 0; rows < A.rows; ++rows){
        for (size_t cols = 0; cols < A.cols; ++cols){
            printf("%f ", A.data[rows * A.cols + cols]);
        }
        printf("\n");
    }
}


void matrix_sum(const Matrix A, const Matrix B, Matrix * C) // C = A + B
{
    matrix_free(C);

    if (A.rows != B.rows || A.cols != B.cols || A.rows * A.cols == 0){
        printf("Summation error.");
        return;
    }

    *C = matrix_alloc(A.rows, A.cols);
    if(C->data == NULL){
        printf("Allocation memory fail.");
        return;
    }

    for (size_t rows = 0; rows < A.rows; ++rows){            
        for (size_t cols = 0; cols < A.cols; ++cols){
            C->data[rows * A.cols + cols] = A.data[rows * A.cols + cols] + B.data[rows * A.cols + cols];
        }        
    }
    
}


void matrix_sub(const Matrix A, const Matrix B, Matrix * C) // C = A - B
{
    matrix_free(C);

    if (A.rows != B.rows || A.cols != B.cols || A.cols * A.rows == 0){
        printf("Summation error.");
        return;
    }

    *C = matrix_alloc(A.rows, A.cols);
    if(C->data == NULL){
        printf("Allocation memory fail.");
        return;
    }

    for (size_t rows = 0; rows < A.rows; ++rows){            
        for (size_t cols = 0; cols < A.cols; ++cols){
            C->data[rows * A.cols + cols] = A.data[rows * A.cols + cols] - B.data[rows * A.cols + cols];
        }        
    }  
}


void matrix_mul(const double ratio, Matrix* A) // A*= ratio
{
    if (A->data == NULL || A->rows * A->cols == 0){
        printf("multiplication matrix error.");
        return;
    }

    for(size_t ind = 0; ind < A->rows * A->cols; ++ind){
        A->data[ind] *= ratio;
    }
}


double matrix_det(const Matrix *A)
{

    if (A->cols != A->rows || A->cols * A->rows == 0 || A->data == NULL){
        printf("Error of finding determinant");
        return NAN;
    }

    double det = 0;

    if(A->cols == 2){
        det = A->data[0] * A->data[3] - A->data[1] * A->data[2];
        return det;
    }

    Matrix M;
    M.rows = A->rows - 1;
    M.cols = A->cols - 1;
    M = matrix_alloc(M.rows, M.cols);


    for (size_t a_cols = 0; a_cols < A->cols; ++a_cols){
        
        size_t cntr = 0;
        for(size_t m_rows = 0; m_rows < A->rows; ++m_rows){
            for (size_t m_cols = 0; m_cols < A->cols; ++m_cols){
                if (m_cols != a_cols && m_rows != 0){
                    M.data[cntr] = A->data[A->rows * m_rows + m_cols];
                    ++cntr;
                    
                }
            }
        }
        if (a_cols % 2 == 0) det += A->data[a_cols] * matrix_det(&M);
        else det -= A->data[a_cols] * matrix_det(&M);
    }

    matrix_free(&M);
    return det;
  
}


void matrix_trn(const Matrix *A)
{
    if (A->cols != A->rows || A->cols * A->rows == 0 || A->data == NULL){
        printf("Transpotation error.");
        return;
    }

    double t;
    for (size_t rows = 0; rows < A->rows; ++rows){
        for ( size_t cols = 0; cols < rows; ++ cols){
            t = A->data[cols + rows * A->rows];
            A->data[cols + rows * A->rows] = A->data[rows + cols * A->cols];
            A->data[rows + A->cols * cols] = t;
        }
    }
}



Matrix matrix_inv(const Matrix A)
{

    if (A.cols != A.rows || A.cols * A.rows == 0 || A.data == NULL){
        printf("Inversion error");
        return (Matrix){0, 0, NULL};
    }


    if(matrix_det(&A) == 0){
        printf("Inverse matrix does not exist");
        return (Matrix){0, 0, NULL};
    }

    Matrix B; //выходная матрица
    B = matrix_alloc(A.rows, A.cols);

    Matrix T; // матрица для нахождения алгебраического дополнения
    T = matrix_alloc(A.rows - 1, A.cols - 1);
    if (T.data == NULL){
        printf("Inversion error");
        return (Matrix){0, 0, NULL};
    }

    size_t cntr;
    for( size_t a_rows = 0; a_rows < A.rows; a_rows++){
        for (size_t a_cols = 0; a_cols < A.cols; a_cols++){
            cntr = 0;
            for (size_t t_rows = 0; t_rows < A.rows; t_rows++){
                for (size_t t_cols = 0; t_cols < A.cols; t_cols++){
                    if(a_rows != t_rows && a_cols != t_cols){
                        T.data[cntr] = A.data[A.cols * t_rows + t_cols];
                        cntr++;
                    }
                }
            }
            B.data[a_rows * A.cols + a_cols] = matrix_det(&T);
            if( (a_rows + a_cols) % 2 == 1) B.data[a_rows * A.cols + a_cols] *= -1;
        }
    }

    matrix_free(&T);
    double t = 1. / matrix_det(&A);
    matrix_trn(&B);
    matrix_mul(t, &B);

    return B;
    
}

Matrix matrix_mul2(const Matrix A, const Matrix B) // произведение матриц
{
    if (A.cols != B.rows || A.cols * A.rows == 0 || B.rows * B.cols == 0){
        printf("Multiplication matrix2 error");
        return (Matrix){0,0,NULL};
    }

    Matrix C;
    C = matrix_alloc(A.rows, B.cols);
    if (C.data == NULL){
        printf("Multiplication matrix2 error");
        return (Matrix){0,0,NULL};
    }

    for( size_t rows_c = 0; rows_c < C.rows; rows_c++){
        for( size_t cols_c = 0; cols_c < C.cols; cols_c++){
            C.data[C.cols * rows_c + cols_c] = 0;
            for( size_t t = 0; t < A.cols; t++){
                 C.data[C.cols * rows_c + cols_c] += A.data[A.cols * rows_c + t] * B.data[B.cols * t + cols_c];
            }
        }
    }
    return C;
}

double fact(size_t n)
{
    double t = 1;
    for (size_t i = 2; i <= n; ++i) t*=i;
    return t;
}



Matrix matrix_unit(const size_t t) // t = cols = rows
{
    Matrix A;
    A = matrix_alloc(t, t);
    if(A.data == NULL){
        printf("matrix unit error");
        return (Matrix){0, 0, NULL};
    }

    for (size_t rows = 0; rows < t; ++rows){
        for (size_t cols = 0; cols < t; ++cols){
            if(cols == rows) A.data[A.cols * rows + cols] = 1;
            else A.data[A.cols * rows + cols] = 0;
        }
    }
    return A;
}

/*Matrix matrix_drg( const Matrix A, size_t n)
{
    if (n == 1) return A;
    if( n < 0){
        printf("dgr_matrix error");
        return (Matrix){0, 0, NULL};
    }

    Matrix B;
    B = A;
    for ( size_t dgr = 1; dgr <= n; ++dgr){
        B = matrix_mul2(A, B);
    }
    return B;
}*/

void matrix_clear(const Matrix *A)
{
    for (size_t ind = 0; ind < A->cols * A->rows; ++ind){
        A->data[ind] = 0;
    }
}

Matrix matrix_exp(const Matrix A)
{
    if(A.cols != A.rows || A.cols * A.rows == 0 || A.data == NULL){
        printf("exp_matrix error");
        return (Matrix){0, 0, NULL};
    }

    Matrix B, M1, M2; //M1 - for mul1, m2 - for mul2

    B = matrix_alloc(A.rows, A.cols);
    if(B.data == NULL){
        printf("exp_matrix error");
        return (Matrix){0, 0, NULL};
    }

    M1 = matrix_alloc(A.rows, A.cols);
    if(M1.data == NULL){
        printf("exp_matrix error");
        return (Matrix){0, 0, NULL};
    }

    M2 = matrix_alloc(A.rows, A.cols);
    if(M2.data == NULL){
        printf("exp_matrix error");
        return (Matrix){0, 0, NULL};
    }

    B = matrix_unit(A.rows);
    matrix_sum(B, A, &B);

    for (size_t i = 2; i < 10; ++i){
        M2 = matrix_mul2(M2, A);
        M1 = M2;
        matrix_mul((double)(1. / fact(i)), &M1);
        matrix_sum(B, M1, &B);
        matrix_clear(&M1);
    }

    matrix_free(&M1);
    matrix_free(&M2);
    return B;
}


int main(){
    Matrix a1, a2, c;
    a1 = matrix_alloc(3, 3);
    a2 = matrix_alloc(3, 3);
    matrix_fill(a1, (double[]){1, 2, 3, 4, 5, 6, 7, 8, 9});
    matrix_fill(a2, (double[]){1, 2, 3, 4, 5, 6, 7, 8, 9});
   


}
