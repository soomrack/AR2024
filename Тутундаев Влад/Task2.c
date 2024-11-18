#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <iostream>


struct Matrix {
    size_t rows;
    size_t cols;
    double *data;
};

typedef struct Matrix Matrix;



Matrix alloc_matrix( size_t rows, size_t cols)
{
    Matrix A = {0, 0, NULL};

    if ( (double)(rows / SIZE_MAX * cols) >= 1. || rows * cols == 0)
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


void fill_matrix(const Matrix A, double *arr)
{
    memcpy(A.data, arr, A.cols * A.rows * sizeof(double));
}


void free_matrix(Matrix *A)
{
    free(A->data);
    *A = (Matrix){0, 0, NULL};
}


void print_matrix( const Matrix A)
{
    for (size_t rows = 0; rows < A.rows; ++rows){
        for (size_t cols = 0; cols < A.cols; ++cols){
            printf("%f ", A.data[rows * A.cols + cols]);
        }
        printf("\n");
    }
}


void sum_matrix(Matrix A, Matrix B, Matrix * C) // C = A + B
{
    free_matrix(C);

    if (A.rows != B.rows || A.cols != B.cols){
        printf("Summation error.");
        return;
    }
    *C = alloc_matrix(A.rows, A.cols);
    for (size_t rows = 0; rows < A.rows; ++rows){            
        for (size_t cols = 0; cols < A.cols; ++cols){
            C->data[rows * A.cols + cols] = A.data[rows * A.cols + cols] + B.data[rows * A.cols + cols];
        }        
    }
    
}


void sub_matrix(Matrix A, Matrix B, Matrix * C) // C = A - B
{
    free_matrix(C);

    if (A.rows != B.rows || A.cols != B.cols){
        printf("Summation error.");
        return;
    }

    *C = alloc_matrix(A.rows, A.cols);
    for (size_t rows = 0; rows < A.rows; ++rows){            
        for (size_t cols = 0; cols < A.cols; ++cols){
            C->data[rows * A.cols + cols] = A.data[rows * A.cols + cols] - B.data[rows * A.cols + cols];
        }        
    }  
}


void mul_matrix(double ratio, Matrix* A) // A*= ratio
{
    /*if (A->data == NULL){
        printf("multiplication matrix error.");
        return;
    }*/

    for (size_t rows = 0; rows < A->rows; ++rows){            
        for (size_t cols = 0; cols < A->cols; ++cols){
            A->data[rows * A->cols + cols] *= ratio;
        }        
    }
}


double det_matrix(const Matrix *A)
{

    if (A->cols != A->rows){
        printf("Error of finding determinant");
        return -1;
    }

    double det = 0;

    if(A->cols == 2){
        det = A->data[0] * A->data[3] - A->data[1] * A->data[2];
        return det;
    }

    Matrix M;
    M.rows = A->rows - 1;
    M.cols = A->cols - 1;
    M = alloc_matrix(M.rows, M.cols);


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
        if (a_cols % 2 == 0) det += A->data[a_cols] * det_matrix(&M);
        else det -= A->data[a_cols] * det_matrix(&M);
    }

    free_matrix(&M);
    return det;
  
}


void trn_matrix(Matrix *A)
{
    if (A->cols != A->rows){
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



Matrix inv_matrix(Matrix A)
{

    if (A.cols != A.rows){
        printf("Inversion error");
        return (Matrix){0, 0, NULL};
    }


    if(det_matrix(&A) == 0){
        printf("Inverse matrix does not exist");
        return (Matrix){0, 0, NULL};
    }

    Matrix B; //выходная матрица
    B = alloc_matrix(A.rows, A.cols);

    Matrix T; // матрица для нахождения алгебраического дополнения
    T = alloc_matrix(A.rows - 1, A.cols - 1);
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
            B.data[a_rows * A.cols + a_cols] = det_matrix(&T);
            if( (a_rows + a_cols) % 2 == 1) B.data[a_rows * A.cols + a_cols] *= -1;
        }
    }

    free_matrix(&T);
    double t = 1. / det_matrix(&A);
    trn_matrix(&B);
    mul_matrix(t, &B);

    return B;
    
}

Matrix mul_matrix2(Matrix A, Matrix B) // произведение матриц
{
    if (A.cols != B.rows){
        printf("Multiplication matrix2 error");
        return (Matrix){0,0,NULL};
    }
    Matrix C;
    C = alloc_matrix(A.rows, B.cols);

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

double fact (size_t n)
{
    double t = 1;
    for (size_t i = 2; i <= n; ++i) t*=i;
    return t;
}



Matrix unit_matrix(const size_t t) // t = cols = rows
{
    Matrix A;
    A = alloc_matrix(t, t);
    for (size_t rows = 0; rows < t; ++rows){
        for (size_t cols = 0; cols < t; ++cols){
            if(cols == rows) A.data[A.cols * rows + cols] = 1;
            else A.data[A.cols * rows + cols] = 0;
        }
    }
    print_matrix(A);
    return A;
}

Matrix dgr_matrix( Matrix A, size_t n)
{
    if (n == 1) return A;
    if( n < 0){
        printf("dgr_matrix error");
        return (Matrix){0, 0, NULL};
    }

    Matrix B;
    B = A;
    for ( size_t dgr = 1; dgr <= n; ++dgr){
        B = mul_matrix2(A, B);
    }
    return B;
}


Matrix exp_matrix(Matrix A)
{
    if(A.cols != A.rows){
        printf("exp_matrix error");
        return (Matrix){0, 0, NULL};
    }

    Matrix B;
    B = unit_matrix(A.rows);

    for (size_t i = 1; i < 10; ++i){
        
    }

}


int main(){
    Matrix a1, a2, c;
    a1 = alloc_matrix(3, 3);
    a2 = alloc_matrix(3, 3);
    fill_matrix(a1, (double[]){1, 2, 3, 4, 5, 6, 7, 8, 9});
    fill_matrix(a2, (double[]){1, 2, 3, 4, 5, 6, 7, 8, 9});
    c = unit_matrix(4);
    


}
