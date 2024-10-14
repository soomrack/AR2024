#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


struct Matrix {
    size_t cols; 
    size_t rows; 
    double* data; 
}; 


struct Matrix Matrix_allocate (size_t cols, size_t rows) {
    struct Matrix A = {cols, rows, NULL};
    A.data = (double*) malloc (cols * rows * sizeof(double));
    
    if (A.data == NULL) {
        printf ("Error: Unable to allocate memory\n"); // Ошибка выделения памяти
        return (struct Matrix) {0, 0, NULL};
    }
    
    memset (A.data, 0, cols * rows * sizeof(double)); // Заполнение матрицы нулями
    return A;
} 


void Matrix_free (struct Matrix A) {
    if (A.data != NULL) {
        free (A.data);
        A.data = NULL;
    }
}

// Функция для доступа к элементу матрицы
double Matrix_get (struct Matrix A, size_t row, size_t col) {
    return A.data [A.cols * row + col];
}

// Функция для установки значения в элемент матрицы
void Matrix_set (struct Matrix A, size_t row, size_t col, double value) {
    A.data [A.cols * row + col] = value;
}

// Сложение двух матриц
struct Matrix Matrix_add (struct Matrix A, struct Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        printf ("Error: the dimensions of the matrices do not match for addition\n"); 
        return (struct Matrix) {0, 0, NULL};
    }

    struct Matrix result = Matrix_allocate (A.cols, A.rows); 
    
    for (size_t i = 0; i < A.rows; i++) {
        for (size_t j = 0; j < A.cols; j++) {
            Matrix_set (result, i, j, Matrix_get(A, i, j) + Matrix_get(B, i, j)); 
        }
    }
    return result;
}

// Вычитание двух матриц
struct Matrix Matrix_subtract (struct Matrix A, struct Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        printf ("Error: the sizes of the matrices do not match for subtraction\n");
        return (struct Matrix){0, 0, NULL};
    }

    struct Matrix result = Matrix_allocate (A.cols, A.rows);
    
    for (size_t i = 0; i < A.rows; i++) {
        for (size_t j = 0; j < A.cols; j++) {
            Matrix_set (result, i, j, Matrix_get(A, i, j) - Matrix_get(B, i, j));
        }
    }
    return result;
}

// Умножение матрицы на число
struct Matrix Matrix_scalar_multiply (struct Matrix A, double scalar) {
    struct Matrix result = Matrix_allocate (A.cols, A.rows);
    
    for (size_t i = 0; i < A.rows; i++) {
        for (size_t j = 0; j < A.cols; j++) {
            Matrix_set (result, i, j, Matrix_get(A, i, j) * scalar);
        }
    }
    return result;
}

// Умножение матрицы на матрицу
struct Matrix Matrix_multiply (struct Matrix A, struct Matrix B) {
    if (A.cols != B.rows) {
        // Неравное кол-во строк и столбцов в обоих матриц
        printf ("Error: the number of columns of the first matrix is not equal to the number of rows of the second matrix\n");
        return (struct Matrix) {0, 0, NULL};
    }

    struct Matrix result = Matrix_allocate (B.cols, A.rows);
    
    for (size_t i = 0; i < A.rows; i++) {
        for (size_t j = 0; j < B.cols; j++) {
            double sum = 0.0; // Сумма для кождого элемента
            for (size_t k = 0; k < A.cols; k++) {
                sum += Matrix_get(A, i, k) * Matrix_get(B, k, j); // Умножение матрицы на матрицу
            }
            Matrix_set (result, i, j, sum); // Сохранение результата
        }
    }
    return result;
}


void Matrix_print (struct Matrix A) {
    for (size_t i = 0; i < A.rows; i++) {
        for (size_t j = 0; j < A.cols; j++) {
            printf ("%d ", Matrix_get(A, i, j));
        }
        printf ("\n");
    }
}


int main() {
    
    struct Matrix A = Matrix_allocate(2, 2);
    struct Matrix B = Matrix_allocate(2, 2);
    
    Matrix_set(A, 0, 0, 1);
    Matrix_set(A, 0, 1, 2);
    Matrix_set(A, 1, 0, 3);
    Matrix_set(A, 1, 1, 4);

    Matrix_set(B, 0, 0, 5);
    Matrix_set(B, 0, 1, 6);
    Matrix_set(B, 1, 0, 7);
    Matrix_set(B, 1, 1, 8);

    printf ("Matrix A:\n");
    Matrix_print(A);

    printf ("Matrix B:\n");
    Matrix_print(B);

    struct Matrix C = Matrix_add (A, B);
    printf ("The amount A and B:\n");
    Matrix_print(C);

    struct Matrix D = Matrix_subtract (A, B);
    printf ("Difference A and B:\n");
    Matrix_print(D);

    struct Matrix E = Matrix_scalar_multiply (A, 2.0);
    printf ("Multiplication A on 2.0:\n");
    Matrix_print(E);

    struct Matrix F = Matrix_multiply (A, B);
    printf ("Multiplication A on B:\n");
    Matrix_print(F);

    // Освобождение памяти
    Matrix_free(A);
    Matrix_free(B);
    Matrix_free(C);
    Matrix_free(D);
    Matrix_free(E);
    Matrix_free(F);

    return 0;
}