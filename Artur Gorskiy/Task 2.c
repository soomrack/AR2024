#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

// Структура для матрицы
struct Matrix {
    size_t rows;  // Количество строк
    size_t cols;  // Количество столбцов
    double* data; // Данные матрицы
};

typedef struct Matrix Matrix;

// Уровни исключений для работы с матрицами
enum MatrixExceptionLevel { ERROR, WARNING, INFO, DEBUG };

// Функция для обработки исключений и вывода сообщений
void matrix_exception(const enum MatrixExceptionLevel level, const char* msg)
{
    switch (level) {
        case ERROR:   printf("ERROR: %s", msg); break;
        case WARNING: printf("WARNING: %s", msg); break;
        case INFO:    printf("INFO: %s", msg); break;
        case DEBUG:   printf("DEBUG: %s", msg); break;
    }
}

// Функция выделения памяти для матрицы
Matrix matrix_allocate(const size_t rows, const size_t cols)
{
    Matrix A = { 0, 0, NULL };

    if (rows == 0 || cols == 0) {
        return A;  // Если строки или столбцы равны нулю, возвращаем пустую матрицу
    }

    // Выделение памяти для данных матрицы
    A.data = (double*)malloc(rows * cols * sizeof(double)); 

    // Проверка на ошибку выделения памяти
    if (A.data == NULL) {
        matrix_exception(ERROR, "Memory allocation failed.\n");
        return A;
    }

    // Проверка на переполнение при выделении памяти
    if (rows > SIZE_MAX / cols || rows * cols > SIZE_MAX / sizeof(double)) {
        matrix_exception(ERROR, "Memory allocation failed: overflow.\n");
        return A;
    }

    A.rows = rows;
    A.cols = cols;
    return A;
}

// Освобождение памяти, занятой матрицей
void matrix_free(Matrix* A)
{
    free(A->data);  // Освобождение памяти для данных матрицы
    *A = (Matrix){ 0, 0, NULL }; // Обнуление структуры
}

// Заполнение матрицы значениями из массива
void matrix_set(const Matrix A, const double* values)
{
    memcpy(A.data, values, A.rows * A.cols * sizeof(double)); // Копирование данных в матрицу
}

// Печать матрицы
void matrix_print(const Matrix A)
{
    for (size_t row = 0; row < A.rows; ++row) {
        for (size_t col = 0; col < A.cols; ++col) {
            printf(" % 2.3f", A.data[row * A.cols + col]);
        }
        printf("\n");
    }
    printf("\n");
}

// Сложение матриц A + B = C
int matrix_add(const Matrix A, const Matrix B, const Matrix C)
{
    // Проверка на совместимость размеров матриц
    if (A.cols != B.cols || A.rows != B.rows) {
        matrix_exception(ERROR, "matrix_add: Incompatible matrix sizes.\n");
        return 0;
    }

    // Сложение матриц
    for (size_t idx = 0; idx < A.rows * A.cols; ++idx) {
        C.data[idx] = A.data[idx] + B.data[idx];
    }
    printf("A + B =\n");
    matrix_print(C);  // Печать результата
    return 1;
}

// Вычитание матриц A - B = C
int matrix_subtraction(const Matrix A, const Matrix B, const Matrix C)
{
    // Проверка на совместимость размеров матриц
    if (A.cols != B.cols || A.rows != B.rows) {
        matrix_exception(ERROR, "matrix_subtraction: Incompatible matrix sizes.\n");
        return 0;
    }

    // Вычитание матриц
    for (size_t idx = 0; idx < A.rows * A.cols; ++idx) {
        C.data[idx] = A.data[idx] - B.data[idx];
    }
    printf("A - B =\n");
    matrix_print(C);  // Печать результата
    return 1;
}

// Умножение матриц A * B = D
int matrix_multiplication(const Matrix A, const Matrix B, Matrix D) 
{
    // Проверка на совместимость матриц для умножения
    if (A.cols != B.rows) {
        matrix_exception(ERROR, "matrix_multiplication: A.cols must be equal to B.rows.\n");
        return 0;
    }

    // Умножение матриц
    for (size_t row = 0; row < D.rows; ++row) {
        for (size_t col = 0; col < D.cols; ++col) {
            D.data[row * D.cols + col] = 0;
            for (size_t k = 0; k < A.cols; ++k) {
                D.data[row * D.cols + col] += A.data[row * A.cols + k] * B.data[k * B.cols + col];
            }
        }
    }
    return 1;
}

// Транспонирование матрицы
int matrix_transposition(const Matrix A, const Matrix T)
{
    for (int row = 0; row < A.cols; ++row) {
        for (int col = 0; col < A.rows; ++col) {
            T.data[col * T.cols + row] = A.data[row * A.cols + col];
        }
    }
    printf("Transposed matrix A = \n");
    matrix_print(T);  // Печать транспонированной матрицы
    return 1;
}

// Вычисление детерминанта матрицы
double matrix_determinant(const Matrix A) {
    if (A.rows != A.cols) {
        matrix_exception(ERROR, "matrix_determinant: Matrix must be square.\n");
        return 0;
    }

    if (A.rows == 1) {
        return A.data[0];  // Для матрицы 1x1 детерминант - это единственный элемент
    }

    if (A.rows == 2) {
        return A.data[0] * A.data[3] - A.data[1] * A.data[2];
    }

    double det = 0;
    for (size_t col = 0; col < A.cols; ++col) {
        Matrix submatrix = matrix_allocate(A.rows - 1, A.cols - 1);
        size_t sub_row = 0;
        for (size_t row = 1; row < A.rows; ++row) {
            size_t sub_col = 0;
            for (size_t k = 0; k < A.cols; ++k) {
                if (k != col) {
                    submatrix.data[sub_row * submatrix.cols + sub_col] = A.data[row * A.cols + k];
                    sub_col++;
                }
            }
            sub_row++;
        }
        det += (col % 2 == 0 ? 1 : -1) * A.data[0 * A.cols + col] * matrix_determinant(submatrix);
        matrix_free(&submatrix);  // Освобождение памяти для подматрицы
    }
    return det;
}

// Вычисление обратной матрицы
int matrix_inverse(const Matrix A, Matrix inverse) {
    if (A.rows != A.cols) {
        matrix_exception(ERROR, "matrix_inverse: Matrix must be square.\n");
        return 0;
    }

    double det = matrix_determinant(A);
    if (det == 0) {
        matrix_exception(ERROR, "matrix_inverse: Matrix is singular (determinant is 0).\n");
        return 0;
    }

    Matrix adjugate = matrix_allocate(A.rows, A.cols);

    // Вычисление матрицы алгебраических дополнений
    for (size_t row = 0; row < A.rows; ++row) {
        for (size_t col = 0; col < A.cols; ++col) {
            Matrix submatrix = matrix_allocate(A.rows - 1, A.cols - 1);
            size_t sub_row = 0;
            for (size_t i = 0; i < A.rows; ++i) {
                if (i == row) continue;
                size_t sub_col = 0;
                for (size_t j = 0; j < A.cols; ++j) {
                    if (j == col) continue;
                    submatrix.data[sub_row * submatrix.cols + sub_col] = A.data[i * A.cols + j];
                    sub_col++;
                }
                sub_row++;
            }
            adjugate.data[col * adjugate.cols + row] = ((row + col) % 2 == 0 ? 1 : -1) * matrix_determinant(submatrix);
            matrix_free(&submatrix);  // Освобождение памяти для подматрицы
        }
    }

    for (size_t i = 0; i < inverse.rows * inverse.cols; ++i) { // Деление на детерминант для получения обратной матрицы
        inverse.data[i] = adjugate.data[i] / det;
    }

    matrix_free(&adjugate);  // Освобождение памяти для матрицы дополнений
    return 1;
}

int main()
{
    Matrix A, B, C, D, T, inverse, expA;
    A = matrix_allocate(4, 4);  
    B = matrix_allocate(4, 4);  

    double valuesA[] = {
      6., 2., 3., 6.,
      2., -1., 5., 5.,
       4., 4., 2., 7.,
       2., 3., 7., 4.
    };

    double valuesB[] = {
        4., 5., 3., 1.,
        -1., 2., 3., 8.,
        -2., 7., 1., 3.,
        5., 5., 9., 7.
    };

    // Заполнение матриц значениями
    matrix_set(A, valuesA);
    matrix_set(B, valuesB);
    matrix_print(A);
    matrix_print(B);

    C = matrix_allocate(A.rows, A.cols);
    matrix_add(A, B, C);  // Сложение матриц
    matrix_free(&C);

    C = matrix_allocate(A.rows, A.cols);
    matrix_subtraction(A, B, C);  // Вычитание матриц
    matrix_free(&C);

    D = matrix_allocate(A.rows, B.cols);
    matrix_multiplication(A, B, D);  // Умножение матриц
    printf("A * B =\n");
    matrix_print(D);

    T = matrix_allocate(A.cols, A.rows);
    matrix_transposition(A, T);  // Транспонирование матрицы

    printf("Determinant of A: %f\n\n", matrix_determinant(A));  // Детерминант

    inverse = matrix_allocate(A.rows, A.cols);
    if (matrix_inverse(A, inverse)) {
        printf("Inverse of A:\n");
        matrix_print(inverse);  // Обратная матрица
    }

    expA = matrix_allocate(A.rows, A.cols);

    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);
    matrix_free(&D);
    matrix_free(&T);
    matrix_free(&inverse);
    matrix_free(&expA);

    return 0;
}
