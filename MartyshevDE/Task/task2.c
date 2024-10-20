#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


struct Matrix 
{
    size_t cols; 
    size_t rows;  
    double* data;
}; 


void martix_exception(const int code, char* msg)
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
    struct Matrix A = {cols, rows, NULL};  //Не выделять 0 памяти (проверку)
    A.data = (double*)malloc(cols * rows * sizeof(double)); // Что бы влезало в SIZE_MAX
    
    if (A.data == NULL) 
    {
        martix_exception(1, "Unable to allocate memory");
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
        martix_exception (1, "The dimensions of the matrices do not match for addition");
        return (struct Matrix) {0, 0, NULL};
    }

    struct Matrix result = matrix_allocate (A.cols, A.rows); 
    
    for(size_t idx = 0; idx < A.rows * A.cols; ++idx);
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
        martix_exception (1, "The sizes of the matrices do not match for subtraction");
        return (struct Matrix){0, 0, NULL};
    }

    struct Matrix result = matrix_allocate (A.cols, A.rows);
    
    for (size_t i = 0; i < A.rows; i++) 
    {
        for (size_t j = 0; j < A.cols; j++) 
        {
            matrix_set (result, i, j, matrix_get(A, i, j) - matrix_get(B, i, j));
        }
    }
    return result;
}

// Умножение матрицы на число
struct Matrix matrix_scalar_multiply (struct Matrix A, double scalar) 
{
    struct Matrix result = matrix_allocate (A.cols, A.rows);
    
    for (size_t i = 0; i < A.rows; i++) 
    {
        for (size_t j = 0; j < A.cols; j++) 
        {
            matrix_set (result, i, j, matrix_get(A, i, j) * scalar);
        }
    }
    return result;
}

// Умножение матрицы на матрицу
struct Matrix matrix_multiply (struct Matrix A, struct Matrix B) 
{
    if (A.cols != B.rows) 
    {
        // Неравное кол-во строк и столбцов в обоих матриц
        martix_exception (1, "The number of columns of the first matrix is not equal to the number of rows of the second matrix");
        return (struct Matrix) {0, 0, NULL};
    }

    struct Matrix result = matrix_allocate (B.cols, A.rows);
    
    for (size_t i = 0; i < A.rows; i++) 
    {
        for (size_t j = 0; j < B.cols; j++) 
        {
            double sum = 0.0; // Сумма для кождого элемента
            for (size_t k = 0; k < A.cols; k++) 
            {
                sum += matrix_get(A, i, k) * matrix_get(B, k, j); // Умножение матрицы на матрицу
            }
            matrix_set (result, i, j, sum); // Сохранение результата
        }
    }
    return result;
}


void matrix_print (struct Matrix A) 
{
    for (size_t i = 0; i < A.rows; i++) 
    {
        for (size_t j = 0; j < A.cols; j++) 
        {
            printf ("%2.1f ", matrix_get(A, i, j));
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