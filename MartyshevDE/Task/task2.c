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


void matrix_exception(const int code, char* msg)
{
    if(code == 1)
    {
        printf("ERROR: %s\n", msg);   // Ошибка
    }

    if(code == 2)
    {
        printf("Matrix %s\n", msg);   // Матрица
    }
}


struct Matrix matrix_allocate (size_t cols, size_t rows) 
{
    struct Matrix A = {cols, rows, NULL};  
    A.data = (double*)malloc(cols * rows * sizeof(double)); 
    
    if (cols == 0 || rows == 0) 
    {
        matrix_exception(1, "Matrix dimensions must be greater than 0");    //Размер матрицы должен быть больше 0
        return (struct Matrix){0, 0, NULL};
    }

    if (cols > SIZE_MAX / rows || (cols * rows) > SIZE_MAX / sizeof(double)) 
    {
        matrix_exception(1, "Matrix size exceeds allowable memory limit");  //Размер матрицы превышает допустимый предел памяти
        return (struct Matrix){0, 0, NULL};
    }


    if (A.data == NULL) 
    {
        matrix_exception(1, "Unable to allocate memory");   //Не удается выделить память
        return(struct Matrix) {0, 0, NULL};
    }
    
    return A;
} 


void matrix_free (struct Matrix* A) 
{
    free (A->data);
    *A = (struct Matrix){0, 0, NULL};

}

// Функция для доступа к элементу матрицы
double matrix_get (struct Matrix A, size_t row, size_t col) 
{
    return A.data [A.cols * row + col];
}

// Функция для установки значения в элемент матрицы
void matrix_set (struct Matrix A, size_t row, size_t col, double value) 
{
    A.data [A.cols * row + col] = value;
}

// Сложение двух матриц
struct Matrix matrix_add (struct Matrix A, struct Matrix B) 
{
    if(A.rows != B.rows || A.cols != B.cols) 
    {
        matrix_exception (1, "The dimensions of the matrices do not match for addition");   //Размеры матриц не совпадают при сложении
        return (struct Matrix) {0, 0, NULL};
    }

    struct Matrix result = matrix_allocate (A.cols, A.rows); 
    
    for (size_t idx = 0; idx < A.rows * A.cols; ++idx)
    {
        result.data[idx] = A.data[idx] + B.data[idx];
    }
    return result;
}

// Вычитание двух матриц
struct Matrix matrix_subtract (struct Matrix A, struct Matrix B) 
{
    if (A.rows != B.rows || A.cols != B.cols) 
    {
        matrix_exception (1, "The sizes of the matrices do not match for subtraction");   //Размеры матриц не совпадают при вычитании
        return (struct Matrix){0, 0, NULL};
    }

    struct Matrix result = matrix_allocate (A.cols, A.rows);

    for (size_t idx = 0; idx < A.rows * A.cols; ++idx)
    {
        result.data[idx] = A.data[idx] - B.data[idx];
    }
    return result;
}

// Умножение матрицы на число
struct Matrix matrix_scalar_multiply (struct Matrix A, double scalar) 
{
    struct Matrix result = matrix_allocate (A.cols, A.rows);
    
    for (size_t idx = 0; idx < A.rows * A.cols; ++idx)
    {
        result.data[idx] = A.data[idx] * scalar;
    }
    return result;
}

// Умножение матрицы на матрицу
struct Matrix matrix_multiply (struct Matrix A, struct Matrix B) 
{
    if (A.cols != B.rows) 
    {
        // Неравное кол-во строк и столбцов в обоих матриц
        martix_exception (1, "The number of columns of the first matrix is not equal to the number of rows of the second matrix");   //Количество столбцов первой матрицы не равно количеству строк второй матрицы
        return (struct Matrix) {0, 0, NULL};
    }

    struct Matrix result = matrix_allocate (B.cols, A.rows);
    
    for (size_t row = 0; row < A.rows; row++) 
    {
        for (size_t col = 0; col < B.cols; col++) 
        {
            result.data[row * result.cols + col] = 0.0; // Сумма для кождого элемента

            for (size_t idx = 0; idx < A.cols; idx++)
            {
                result.data[row * result.cols + col] += A.data[row * A.cols + idx] * B.data[idx * B.cols  + col]; // Умножение матрицы на матрицу
            }
        }
    }
    return result;
}


void matrix_print (struct Matrix A) 
{
    for (size_t row = 0; row < A.rows; row++) 
    {
        for (size_t col = 0; col < A.cols; col++) 
        {
            printf ("%2.1f ", matrix_get(A, row, col));
        }
        printf ("\n");
    }
}


int main() 
{
    
    struct Matrix A = matrix_allocate(2, 2);
    struct Matrix B = matrix_allocate(2, 2);
    
    matrix_set(A, 0, 0, 1);
    matrix_set(A, 0, 1, 2);
    matrix_set(A, 1, 0, 3);
    matrix_set(A, 1, 1, 4);

    matrix_set(B, 0, 0, 5);
    matrix_set(B, 0, 1, 6);
    matrix_set(B, 1, 0, 7);
    matrix_set(B, 1, 1, 8);

    printf("Matrix A:\n");
    matrix_print(A);

    printf("Matrix B:\n");
    matrix_print(B);

    struct Matrix C = matrix_add (A, B);
    printf("The amount A and B:\n");
    matrix_print(C);

    struct Matrix D = matrix_subtract (A, B);
    printf("Difference A and B:\n");
    matrix_print(D);

    struct Matrix E = matrix_scalar_multiply (A, 2.0);
    printf("Multiplication A on 2.0:\n");
    matrix_print(E);

    struct Matrix F = matrix_multiply (A, B);
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