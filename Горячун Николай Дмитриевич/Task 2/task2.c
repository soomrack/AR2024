#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


struct Matrix {
    size_t cols;
    size_t rows;
    double* data;
};

enum MatrixException {ERROR};

double epselon = 0.000000000000000000001;


void matrix_exception(const enum MatrixException exeption, char *msg)
{
    if(exeption == ERROR) {
        printf("ERROR: %s\n", msg);
    };
}


struct Matrix Matrix_allocate(const size_t cols, const size_t rows) {
    struct Matrix A = {cols, rows, NULL};

    if (cols * rows * sizeof(double) / SIZE_MAX > 1) {
        matrix_exception(ERROR, "Ошибка выделения памяти. Объём данных больше чем может вместить в себя тип данных.");
        return (struct Matrix){0, 0, NULL};
    };

    A.data = (double*)malloc(cols * rows * sizeof(double));
    if (A.data == NULL) {
        matrix_exception(ERROR, "Ошибка выделения памяти.");
        return (struct Matrix){0, 0, NULL};
    };
    return A;
};


void matrix_free(struct Matrix *Free)
{
    free(Free->data);
    *Free = (struct Matrix){0, 0, NULL};
}


void matrix_print(const struct Matrix Print)
{
    for (size_t row = 0; row < Print.rows; row++){
        for (size_t col = 0; col < Print.cols; col++) {
            printf("%lf ", Print.data [Print.cols * row + col]);
        };
        printf("\n"); 
    };
    printf("\n");
};


struct Matrix matrixs_multiply(const struct Matrix A, const struct Matrix B) {
    if (A.cols != B.rows) {
        matrix_exception(ERROR, "Количество столбцов первой матрицы не равно количестыу строк второй матрицы.");
        return (struct Matrix) {0, 0, NULL};
    };

    struct Matrix Result = Matrix_allocate(B.cols, A.rows);
    for (size_t row = 0; row < Result.rows; row++) {
        for (size_t col = 0; col < Result.cols; col++) {
            for (size_t idx = 0; idx < Result.cols; idx++) {
                Result.data [Result.cols * row + col] += A.data [A.cols * row + idx] * B.data [B.cols * idx + col];
            };
        };
    };
    return Result;
};


struct Matrix matrixs_sum(const struct Matrix A, const struct Matrix B) {
    if (A.cols != B.cols && A.rows != B.rows) {
        matrix_exception(ERROR, "Порядки матриц не равны.");
        return (struct Matrix){0, 0, NULL};
    };

    struct Matrix Result = Matrix_allocate(A.cols, A.rows);
    for (size_t idx = 0; idx < Result.rows * Result.cols; idx++) {
        Result.data [idx] = A.data [idx] + B.data [idx];
    };
    return Result;
};


struct Matrix matrixs_subtraction(const struct Matrix A, const struct Matrix B) {
    if (A.cols != B.cols && A.rows != B.rows) {
        matrix_exception(ERROR, "Порядки матриц не равны.");
        return (struct Matrix){0, 0, NULL};
    };

    struct Matrix Result = Matrix_allocate(A.cols, A.rows);
    for (size_t idx = 0; idx < Result.rows * Result.cols; idx++) {
        Result.data [idx] = A.data [idx] - B.data [idx];
    };
    return Result;
};


struct Matrix matrix_multiply_on_constant(const struct Matrix A, const double constant) {
    struct Matrix Result = Matrix_allocate(A.cols, A.rows);
    for (size_t idx = 0; idx < Result.rows * Result.cols; idx++) {
        Result.data [idx] = A.data [idx] * constant;
    }
    return Result;
};


void matrix_fill(const struct Matrix Fill, const double *values)
{
    memcpy(Fill.data, values, Fill.rows * Fill.cols * sizeof(double));
};


struct Matrix matrix_E(const size_t rows_and_cols) {
    struct Matrix E = Matrix_allocate(rows_and_cols, rows_and_cols);

    size_t counter = rows_and_cols;
    for (size_t idx = 0; idx < rows_and_cols * rows_and_cols; idx++) {
        counter += (size_t)1;
        if (counter ==  rows_and_cols + 1) {
            E.data[idx] = (double)1;
            counter = 0;
        };
    };
	return E;
};


struct Matrix matrix_exponentiation(const struct Matrix A, const size_t n) {
    if (A.rows != A.cols) {
        matrix_exception(ERROR, "Матрица не квадратная.");
        return (struct Matrix){0, 0, NULL};
    };

    if (n <= 0 && n % 1 >= epselon) {
        matrix_exception(ERROR, "Степень должна быть натуральной");
        return (struct Matrix){0, 0, NULL};
    };

    struct Matrix Result = matrix_E(A.cols);

    for (double idx = 1; idx <= n; idx++) {
        Result = matrixs_multiply(Result, A);
    };
	return Result;
};

size_t factorial(const size_t n) 
{
    if (n <= 0 && n % 1 >= epselon) {
        matrix_exception(ERROR, "Нельзя взять факториал не натурального числа.");
        return (size_t)1;
    };

    double result = (double)1;
    for (double idx = 2; idx <= n; idx++) {
        result *= idx;
    };
    return result;
};


struct Matrix matrix_exponent(const struct Matrix A) {
    if (A.rows != A.cols) {
        matrix_exception(ERROR, "Матрица не квадратная.");
        return (struct Matrix){0, 0, NULL};
    };

    struct Matrix Result = matrix_E(A.cols);

    if (Result.data == NULL) {
        matrix_exception(ERROR, "Ошибка выделения памяти.");
        return (struct Matrix){0, 0, NULL};
    };

    for (double n = 1; n <= (double)20; n++) {
        Result = matrixs_sum(Result, matrix_multiply_on_constant(matrix_exponentiation(A, n), (double)1 / factorial(n)));
    };
	return Result;
};


double degree(const double num, const int n)
{
    double result = 1;
    for (int idx = 0; idx < n; idx++) {
        result *= num;
    };
  return result;
};


double matrix_minor(const struct Matrix A, const size_t el_col, const size_t el_row)
{
    if (A.cols != A.rows) {
        matrix_exception(ERROR, "Матрица должна быть квадратной.");
        return (size_t)1;
    };

    struct Matrix Minor = Matrix_allocate(A.cols - 1, A.rows -1);
    size_t idx = 0;

    for (size_t row = 0; row < A.rows; row++) {
        if (row != el_row) {
            for (size_t col = 0; col < A.cols; col++) {
                if (col != el_col) {
                    Minor.data [idx] = A.data [A.cols * row + col];
                    idx++;
                };
            };
        };
    };

    if (Minor.cols == Minor.rows && Minor.cols == (size_t)2) {
        return(Minor.data [0] * Minor.data [3] - Minor.data[1] * Minor.data [2]);
    };

    double result = 0;
    for (size_t col = 0; col < Minor.cols; col++) {
        result += Minor.data [col] * degree(-1, col) * matrix_minor(Minor, col, 0);
    };

    return result;
};


double matrix_dat(const struct Matrix A)
{
    if (A.cols != A.rows) {
        matrix_exception(ERROR, "Матрица должна быть квадратной.");
        return (size_t)1;
    };

    double result = 0;
    for (size_t col = 0; col < A.cols; col++) {
        result += A.data [col] * degree(-1, col) * matrix_minor(A, col, 0);
    };

    return result;
};


struct Matrix matrix_invertible(const struct Matrix A)
{
    if (A.cols != A.rows) {
        matrix_exception(ERROR, "Матрица должна быть квадратной.");
        return (struct Matrix){0, 0, NULL};
    };

    double dat_result = matrix_dat(A);
    if (dat_result == 0) {
        matrix_exception(ERROR, "Определитель матрицы равен нудю. Найти обратную матрицу невозможно.");
        return (struct Matrix){0, 0, NULL};
    };

    struct Matrix Result = Matrix_allocate(A.cols, A.rows);
    for (size_t row = 0; row < Result.rows; row++) {
        for (size_t col = 0; col < Result.cols; col++) {
            Result.data [Result.cols * col + row] = degree(-1, col + row) * matrix_minor(A, col, row) / dat_result;
        };
    };
    return Result;
};


int main()
{
    struct Matrix A = Matrix_allocate(3, 3);
    struct Matrix B = Matrix_allocate(3, 3);

    matrix_fill(A, (double[]){
            1., 7., 2.,
            6., 4., 1.,
            3., 5., 8.
        });
    matrix_fill(B, (double[]){
            8., 5., 6.,
            4., 1., 3.,
            9., 7., 2.
        });

    struct Matrix C = matrixs_multiply(A, B);
    struct Matrix D = matrixs_sum(A, B);
    struct Matrix F = matrixs_subtraction(A, B);
    struct Matrix G = matrix_multiply_on_constant(A, 5);
    struct Matrix H = matrix_exponent(A);
    double dat_A = matrix_dat(A);
    struct Matrix I = matrix_invertible(A);
/*
    matrix_print(C);
    matrix_print(D);
    matrix_print(F);
    matrix_print(G);
    matrix_print(H);
    printf("%lf\n", dat_A);
*/
    matrix_print(I);

    matrix_free(&A);
    matrix_free(&B);
    matrix_free(&C);
    matrix_free(&D);
    matrix_free(&F);
    matrix_free(&G);
    matrix_free(&H);
    matrix_free(&I);
    return 0;
}
