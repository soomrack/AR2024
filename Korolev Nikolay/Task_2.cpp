#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Matrix {
	int cols;
	int rows;
	double* data;
};


const Matrix empty = { 0, 0, NULL };


Matrix initialize_matrix(const int cols, const int rows) // создание новой матрицы с выделением памяти
{
    Matrix matrix;
	matrix.cols = cols;
	matrix.rows = rows;
    int n_data = matrix.cols * matrix.rows;
	matrix.data = (double*) malloc(n_data * sizeof(double));
	return matrix;
}


void set_matrix_data(Matrix* matrix) {  // заполнение матрицы рандомными числами
    for (int index = 0; index < matrix -> cols * matrix -> rows; ++index) {
        matrix -> data[index] = (double)rand();
    }
}


void error_size(char* operation_name, char* error) // ошибки
{  
	printf("%s is impossible. %s\n", operation_name, error);
}


int null_matrix (const Matrix matrix) // нулевая ли матрица
{ 
	return matrix.cols == 0 && matrix.rows == 0 ?  1 : 0;
}


void print_matrix(const Matrix matrix) { // вывести матрицу в консоль
	if (null_matrix(matrix)) {
		printf("The matrix doesn't exist\n");
		return;
	}
	for ( int row = 0; row < matrix.rows; ++row) {
		for ( int col = 0; col < matrix.cols; ++col) {
			printf("%.2f ", matrix.data[row * matrix.cols + col]);
		}
		printf("\n");
	}
	printf("\n");
}


void free_matrix(Matrix* matrix) // отчистить память
{ 
	free(matrix->data);
}


Matrix summ(const Matrix matrix1, const Matrix matrix2) // сумма матриц
{ 
	if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols) {
		error_size("Summation", "Matrixes should have equal sizes");
		return empty;
	}
	Matrix result = initialize_matrix(matrix1.cols, matrix1.rows);
	 int n_data = result.cols * result.rows;
	for ( int index = 0; index < n_data; ++index) {
		result.data[index] = matrix1.data[index] + matrix2.data[index];
	}
	return result;
}


Matrix difference(const Matrix matrix1, const Matrix matrix2) // разность матриц 
{ 
	if (matrix1.rows != matrix2.rows && matrix1.cols != matrix2.cols) {
		error_size("Differenceion", "Matrixes should have equal sizes");
		return empty;
	}
	Matrix result = initialize_matrix(matrix1.cols, matrix1.rows);
	 int n_data = result.cols * result.rows;
	for ( int index = 0; index < n_data; ++index) {
		result.data[index] = matrix1.data[index] - matrix2.data[index];
	}
	return result;
}


Matrix multiply_by_number(const Matrix matrix, double number) // умножение матрицы на число
{ 
	Matrix result = initialize_matrix(matrix.cols, matrix.rows);
	 int n_data = result.cols * result.rows;
	for ( int index = 0; index < n_data; ++index) {
		result.data[index] = matrix.data[index] * number;
	}
	return result;
}


Matrix multiply(const Matrix matrix1, const Matrix matrix2) // умножение матрицы на матрицу
{ 
	if (matrix1.cols != matrix2.rows) {
		error_size("Multiplication", "Matrixes should have certain sizes");
		return empty;
	}
	 int n_cols = matrix2.cols;
	 int n_rows = matrix1.rows;
	Matrix result = initialize_matrix(n_cols, n_rows);
	for ( int row = 0; row < n_rows; ++row) {
		for ( int col = 0; col < n_cols; ++col) {
			double summa = 0.0;
			for ( int k = 0; k < matrix1.cols; ++k) {
				summa +=
					matrix1.data[row * matrix1.cols + k] * 
					matrix2.data[k * matrix2.cols + col];
			}
			result.data[row * n_cols + col] = summa;
		}
	}
	return result;
}


double det(const Matrix matrix) // определитель матрицы
{ 
	if (matrix.cols != matrix.rows) {
		error_size("Getting determinant", "Matrix should be square");
		return 0.;
	}
	double result = 0;
	 int n = matrix.cols;
	if (n == 1) {
		result = matrix.data[0];
		return result;
	}
	for ( int row = 0; row < n; ++row) {
		 int col = 0;
		Matrix submatrix = initialize_matrix(n - 1, n - 1);
		 int row_offset = 0;
		 int col_offset = 0;
		for ( int sub_row = 0; sub_row < n - 1; ++sub_row) {
			for ( int sub_col = 0; sub_col < n - 1; ++sub_col) {
				if (sub_row == row) { row_offset = 1; }
				if (sub_col == col) { col_offset = 1; }
				submatrix.data[sub_row * (n - 1) + sub_col] = 
					matrix.data[(sub_row + row_offset) * n + (sub_col + col_offset)];
			}
		}
		result += pow(-1, row + col) * matrix.data[row * n + col] * det(submatrix);
		free_matrix(&submatrix);
		}
	return result;
}


Matrix transpose_matrix(const Matrix matrix) // транспонированная матрица
{ 
	Matrix result = initialize_matrix(matrix.rows, matrix.cols);
	for ( int row = 0; row < result.rows; ++row) {
		for ( int col = 0; col < result.cols; ++col) {
			result.data[row * result.cols + col] = matrix.data[col * result.rows + row];
		}
	}
	return result;
}


Matrix identity( int dimention) 
{ 
	Matrix result = initialize_matrix(dimention, dimention);
	for ( int row = 0; row < result.rows; ++row) {
		for ( int col = 0; col < result.cols; ++col) {
			result.data[row * result.cols + col] = (row == col) ? 1. : 0.;
		}
	}
	return result;
}


Matrix copy(const Matrix matrix) // копирование матрицы
{ 
	Matrix result = initialize_matrix(matrix.cols, matrix.rows);
	for ( int index = 0; index < matrix.cols * matrix.rows; ++index) {
		result.data[index] = matrix.data[index];
	}
	return result;
}


Matrix expo(const Matrix matrix, int accuracy) // экспонента
{ 
	if (matrix.cols != matrix.rows) {
		error_size("Exp", "Matrix should be square");
		return empty;
	}
	Matrix new_result, new_powered, multiplied;
	Matrix result = identity(matrix.rows);
	Matrix powered = matrix;
	int factorial = 1;
	for (int acc = 1; acc <= accuracy; ++acc) {
		factorial *= acc;

		new_powered = multiply(powered, matrix);
		powered = copy(new_powered);
		free_matrix(&new_powered);

		multiplied = multiply_by_number(powered, 1 / factorial);

		new_result = summ(result, multiplied);
		result = copy(new_result);
		free_matrix(&new_result);

		free_matrix(&multiplied);
	}
	free_matrix(&powered);
	return result;
}


int main() 
{
	Matrix m1, m2;

	m1 = initialize_matrix(3, 3);
	set_matrix_data(&m1);
	print_matrix(m1);

	m2 = initialize_matrix(3, 3);
	set_matrix_data(&m2);
	print_matrix(m2);

	Matrix summition;
	summition = summ(m1, m2);
	print_matrix(summition);
	free_matrix(&summition);

	Matrix differenceion;
	differenceion = difference(m1, m2);
	print_matrix(differenceion);
	free_matrix(&differenceion);


	double determinant;
	determinant = det(m1);
	printf("%.2f\n\n", determinant);

	determinant = det(m2);
	printf("%.2f\n\n", determinant);

	Matrix multiplication1;
	multiplication1 = multiply_by_number(m1, 5);
	print_matrix(multiplication1);
	free_matrix(&multiplication1);


	Matrix multiplication2;
	multiplication2 = multiply(m1, m2);
	print_matrix(multiplication2);
	free_matrix(&multiplication2);


	Matrix trans;
	trans = transpose_matrix(m1);
	print_matrix(trans);
	free_matrix(&trans);

	

	Matrix exponenta;
	exponenta = expo(m1, 3);
	print_matrix(exponenta);
	free_matrix(&exponenta);

	free_matrix(&m1);
	free_matrix(&m2);
}