#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


struct Matrix {
    size_t cols;
    size_t rows;
    double* data;
};

enum MatrixException {ERROR, WARNING};

double Epselon = 0.000000000000000000001;


void matrix_exception(const enum MatrixException exeption, char *msg)
{
    if (exeption == ERROR) {
        printf("ERROR: %s\n", msg);
    };

    if (exeption == WARNING) {
        printf("WARNING: %s\n", msg);
    };
}


struct Matrix matrix_allocate(const size_t cols, const size_t rows) {
    struct Matrix A = {cols, rows, NULL};

    if (cols == 0 && rows == 0) {
        matrix_exception(WARNING, "Внимание выша матрица состоит из 0 столбцов лили из 0 строк");
        return (struct Matrix){A.cols, A.rows, NULL};
    };

    if (sizeof(double) / SIZE_MAX > 1.0/(cols * rows)) {
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


void matrix_free(struct Matrix *F)
{
    if (F->data != NULL) {
        free(F->data);
        *F = (struct Matrix){0, 0, NULL};
    };
}


void matrix_print(const struct Matrix P)
{
    for (size_t row = 0; row < P.rows; row++){
        for (size_t col = 0; col < P.cols; col++) {
            printf("%lf ", P.data[P.cols * row + col]);
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

    struct Matrix R = matrix_allocate(B.cols, A.rows);

    for (size_t idx_null = 0; idx_null < R.rows * R.cols; idx_null++) {
        R.data[idx_null] = 0.0;
    };

    for (size_t row = 0; row < R.rows; row++) {
        for (size_t col = 0; col < R.cols; col++) {
            for (size_t idx = 0; idx < R.cols; idx++) {
                R.data[R.cols * row + col] += A.data[A.cols * row + idx] * B.data[B.cols * idx + col];
            };
        };
    };
    return R;
};


struct Matrix matrixs_sum(const struct Matrix A, const struct Matrix B) {
    if (A.cols != B.cols && A.rows != B.rows) {
        matrix_exception(ERROR, "Порядки матриц не равны.");
        return (struct Matrix){0, 0, NULL};
    };

    struct Matrix R = matrix_allocate(A.cols, A.rows);
    for (size_t idx = 0; idx < R.rows * R.cols; idx++) {
        R.data[idx] = A.data[idx] + B.data[idx];
    };
    return R;
};


struct Matrix matrixs_subtraction(const struct Matrix A, const struct Matrix B) {
    if (A.cols != B.cols && A.rows != B.rows) {
        matrix_exception(ERROR, "Порядки матриц не равны.");
        return (struct Matrix){0, 0, NULL};
    };

    struct Matrix R = matrix_allocate(A.cols, A.rows);
    for (size_t idx = 0; idx < R.rows * R.cols; idx++) {
        R.data[idx] = A.data[idx] - B.data[idx];
    };
    return R;
};


struct Matrix matrix_multiply_on_constant(const struct Matrix A, const double constant) {
    struct Matrix R = matrix_allocate(A.cols, A.rows);
    for (size_t idx = 0; idx < R.rows * R.cols; idx++) {
        R.data[idx] = A.data[idx] * constant;
    }
    return R;
};


void matrix_fill(const struct Matrix Fill, const double *values)
{
    memcpy(Fill.data, values, Fill.rows * Fill.cols * sizeof(double));
};


struct Matrix matrix_E(const size_t rows_and_cols) {
    struct Matrix E = matrix_allocate(rows_and_cols, rows_and_cols);

    for (size_t col = 0; col < E.cols; col++) {
        E.data[E.cols * col + col] = 1.0;
    };

	return E;
};


struct Matrix matrix_power(const struct Matrix A, const size_t n) {
    if (A.rows != A.cols) {
        matrix_exception(ERROR, "Матрица не квадратная.");
        return (struct Matrix){0, 0, NULL};
    };

    struct Matrix R = matrix_E(A.cols);

    if (R.data == NULL) {
        return (struct Matrix){0, 0, NULL};
    };

    if (n == 0) {
        return R;
    };

    if (n % 1 >= Epselon) {
        matrix_exception(ERROR, "Степень должна быть натуральной");
        return (struct Matrix){0, 0, NULL};
    };

    for (double idx = 1; idx <= n; idx++) {
        struct Matrix temp = matrix_allocate(R.cols, R.rows);
        memcpy(temp.data, R.data, R.rows * R.cols * sizeof(double));
        R = matrixs_multiply(temp, A);
        matrix_free(&temp);
    };
	return R;
};

double factorial(const size_t n) 
{
    if (n <= 0 && n % 1 >= Epselon) {
        matrix_exception(ERROR, "Нельзя взять факториал не натурального числа.");
        return (size_t)1;
    };

    double result = 1.;
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

    struct Matrix R = matrix_E(A.cols);

    if (R.data == NULL) {
        return (struct Matrix){0, 0, NULL};
    };

    for (double n = 1; n <= 20.; n++) {
        struct Matrix temp = matrix_allocate(R.cols, R.rows);
        memcpy(temp.data, R.data, R.rows * R.cols * sizeof(double));
        R = matrixs_sum(temp, matrix_multiply_on_constant(matrix_power(A, n), 1.0 / factorial(n)));
        matrix_free(&temp);
    };
	return R;
};


double matrix_minor(const struct Matrix A, const size_t el_col, const size_t el_row)
{
    if (A.cols != A.rows) {
        matrix_exception(ERROR, "Матрица должна быть квадратной.");
        return (size_t)1;
    };

    struct Matrix M = matrix_allocate(A.cols - 1, A.rows -1);

    if (M.data == NULL) {
        return 0;
    };

    size_t idx = 0;

    for (size_t row = 0; row < A.rows; row++) {
        if (row != el_row) {
            for (size_t col = 0; col < A.cols; col++) {
                if (col != el_col) {
                    M.data[idx] = A.data[A.cols * row + col];
                    idx++;
                };
            };
        };
    };

    if (M.cols == M.rows && M.cols == (size_t)2) {
        return(M.data[0] * M.data[3] - M.data[1] * M.data[2]);
    };

    double result = 0;
    double sign = 1.;
    for (size_t col = 0; col < M.cols; col++) {
        sign = 1.0;
        if (col % 2 != 0) {
            sign = -1.0;
        };
        result += M.data[col] * sign * matrix_minor(M, col, 0);
    };

    return result;
};


double matrix_det(const struct Matrix A)
{
    if (A.cols != A.rows) {
        matrix_exception(ERROR, "Матрица должна быть квадратной.");
        return (size_t)1;
    };

    double result = 0;
    double sign = 1.;
    for (size_t col = 0; col < A.cols; col++) {
        sign = 1.0;
        if (col % 2 != 0) {
            sign = -1.0;
        };
        result += A.data[col] * sign * matrix_minor(A, col, 0);
    };

    return result;
};


struct Matrix matrix_invertible(const struct Matrix A)
{
    if (A.cols != A.rows) {
        matrix_exception(ERROR, "Матрица должна быть квадратной.");
        return (struct Matrix){0, 0, NULL};
    };

    double det_result = matrix_det(A);
    if (det_result == 0) {
        matrix_exception(ERROR, "Определитель матрицы равен нудю. Найти обратную матрицу невозможно.");
        return (struct Matrix){0, 0, NULL};
    };

    struct Matrix R = matrix_allocate(A.cols, A.rows);
    double sign = 1.;
    for (size_t row = 0; row < R.rows; row++) {
        for (size_t col = 0; col < R.cols; col++) {
            sign = 1.0;
            if ((col + row) % 2 != 0) {
                sign = -1.0;
            };
            R.data[R.cols * col + row] = sign * matrix_minor(A, col, row) / det_result;
        };
    };
    return R;
};


int main()
{
    struct Matrix A = matrix_allocate(3, 3);
    struct Matrix B = matrix_allocate(3, 3);

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
    double det_A = matrix_det(A);
    struct Matrix I = matrix_invertible(A);

    matrix_print(C);
    matrix_print(D);
    matrix_print(F);
    matrix_print(G);
    matrix_print(H);
    printf("%lf\n\n", det_A);
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
