#include <stdio.h>
#include <stdlib.h>



struct Matrix {
    size_t cols;
    size_t rows;
    double* data;
};


struct Matrix Matrix_allocate(size_t cols,size_t rows) {
    struct Matrix A = {cols, rows, NULL};
    A.data = (double*) malloc (cols * rows * sizeof(double));
    if (A.data == NULL) {
        printf("Ошибка выделения памяти.\n");
        return (struct Matrix) {0, 0, NULL};
    };
    return A;
};


void matrix_free(struct Matrix Free)
{
    if (Free.data != NULL) {
        free(Free.data);
        Free.data = NULL;
    };
}


void print_matrix(struct Matrix Print)
{
    for (int row = 0; row < Print.rows; row++){
        for (int col = 0; col < Print.cols; col++) {
            printf("%lf ", Print.data [Print.cols * row + col]);
        };
        printf("\n"); 
    };
};


struct Matrix multiply_of_matrixs(struct Matrix A, struct Matrix B) {
    if (A.cols == B.rows) {
        struct Matrix Result = Matrix_allocate(B.cols, A.rows);
        for (int row = 0; row < A.rows; row++) {
            for (int col = 0; col < B.cols; col++) {
                double element_result = 0;
                for (int idx = 0; idx < A.cols; idx++) {
                    element_result += A.data [A.cols * row + idx] * B.data [B.cols * idx + col];
                };
                Result.data [Result.cols * row + col] = element_result;
            };
        };
        return Result;
    } else {
        printf("Количество столбцов первой матрицы не равно количестыу строк второй матрицы.\n");
        return (struct Matrix) {0, 0, NULL};
    };
};


struct Matrix sum_of_matrixs(struct Matrix A, struct Matrix B) {
    if (A.cols == B.cols && A.rows == A.rows) {
        struct Matrix Result = Matrix_allocate(A.cols, A.rows);
        for (int idx = 0; idx < A.rows * A.cols; idx++) {
            Result.data [idx] = A.data [idx] + B.data [idx];
        }
        return Result;
    } else {
        printf("Порядки матриц не равны.\n");
        return (struct Matrix) {0, 0, NULL};
    };
};


struct Matrix subtraction_of_matrixs(struct Matrix A, struct Matrix B) {
    if (A.cols == B.cols && A.rows == A.rows) {
        struct Matrix Result = Matrix_allocate(A.cols, A.rows);
        for (int idx = 0; idx < A.rows * A.cols; idx++) {
            Result.data [idx] = A.data [idx] - B.data [idx];
        }
        return Result;
    } else {
        printf("Порядки матриц не равны.\n");
        return (struct Matrix) {0, 0, NULL};
    };
};


struct Matrix multiply_of_constant_and_matrix(struct Matrix A, double constant) {
    struct Matrix Result = Matrix_allocate(A.cols, A.rows);
    for (int idx = 0; idx < A.rows * A.cols; idx++) {
        Result.data [idx] = A.data [idx] * constant;
    }
    return Result;
};


int main()
{
    struct Matrix A = Matrix_allocate(3, 3);
    struct Matrix B = Matrix_allocate(3, 3);

    A.data [0] = 1;
    A.data [1] = 7;
    A.data [2] = 2;
    A.data [3] = 6;
    A.data [4] = 4;
    A.data [5] = 1;
    A.data [6] = 3;
    A.data [7] = 5;
    A.data [8] = 8;

    B.data [0] = 8;
    B.data [1] = 5;
    B.data [2] = 6;
    B.data [3] = 4;
    B.data [4] = 1;
    B.data [5] = 3;
    B.data [6] = 9;
    B.data [7] = 7;
    B.data [8] = 2;

    struct Matrix C = multiply_of_matrixs(A, B);
    struct Matrix D = sum_of_matrixs(A, B);
    struct Matrix E = subtraction_of_matrixs(A, B);
    struct Matrix F = multiply_of_constant_and_matrix(A, 5);
    print_matrix(F);

    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
    matrix_free(D);
    matrix_free(E);
    matrix_free(F);
    return 0;
}
