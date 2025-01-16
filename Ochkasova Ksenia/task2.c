#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_SIZE 100

void fillMatrix(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100 + 1;
        }
    }
}

void addMatrices(int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE], int result[MAX_SIZE][MAX_SIZE], int cols, int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

void subMatrices(int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE],
                 int result[MAX_SIZE][MAX_SIZE], int cols, int rows){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
}

void multiplyMatrixByScalar(int matrix1[MAX_SIZE][MAX_SIZE],  int result[MAX_SIZE][MAX_SIZE],  int scalar, int rows1, int cols1){
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            result[i][j] = matrix1[i][j] * scalar;
        }
    }
}

void multiplyMatrixByMatrix(int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE],
                            int result[MAX_SIZE][MAX_SIZE], int rows1, int cols1, int cols2) {
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

double determinant(int n, int matrix[n][n]) {
    if (n == 1) return matrix[0][0];
    if (n == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    double det = 0.0;
    for (int p = 0; p < n; p++) {
        int subMatrix[n - 1][n - 1];
        for (int i = 1; i < n; i++) {
            int colIndex = 0;
            for (int j = 0; j < n; j++) {
                if (j == p) continue;
                subMatrix[i - 1][colIndex] = matrix[i][j];
                colIndex++;
            }
        }
        det += matrix[0][p] * determinant(n - 1, subMatrix) * ((p % 2 == 0) ? 1 : -1);
    }
    return det;
}

int invertMatrix(int n, int matrix[n][n], double inverse[n][n]) {
    double det = determinant(n, matrix);
    if (det == 0) return 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int subMatrix[n - 1][n - 1];
            int rowIndex = 0;
            for (int row = 0; row < n; row++) {
                if (row == i) continue;
                int colIndex = 0;
                for (int col = 0; col < n; col++) {
                    if (col == j) continue;
                    subMatrix[rowIndex][colIndex] = matrix[row][col];
                    colIndex++;
                }
                rowIndex++;
            }
            inverse[j][i] = determinant(n - 1, subMatrix) * ((i + j) % 2 == 0 ? 1 : -1) / det;
        }
    }
    return 1;
}

void printMatrix(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}


int main() {
    srand(time(NULL));

    int rows1, cols1, rows2, cols2;

    do {
        printf("Введите количество строк и столбцов первой матрицы: ");
        scanf("%d %d", &rows1, &cols1);
        if ((rows1 < 1 || rows1 > 100) && (cols1 < 1 || cols1 > 100)) {
            printf("Строки и столбцы должны быть в диапазоне: (1; 100).\n");
        }
    } while ((rows1 < 1 || rows1 > 100) && (cols1 < 1 || cols1 > 100));

    do {
        printf("Введите количество строк и столбцов второй матрицы: ");
        scanf("%d %d", &rows2, &cols2);
        if ((rows2 < 1 || rows2 > 100) && (cols2 < 1 || cols2 > 100)) {
            printf("Строки и столбцы должны быть в диапазоне: (1; 100).\n");
        }
    } while ((rows2 < 1 || rows2 > 100) && (cols2 < 1 || cols2 > 100));

    int matrix1[100][100];
    int matrix2[100][100];

    fillMatrix(matrix1, rows1, cols1);
    fillMatrix(matrix2, rows2, cols2);

    printf("Первая матрица:\n");
    printMatrix(matrix1, rows1, cols1);
    printf("\n");
    
    printf("Вторая матрица:\n");
    printMatrix(matrix2, rows2, cols2);
    printf("\n");

    int result[100][100];
    
    int scalar;

    if (rows1 == rows2 || cols1 == cols2) {
        addMatrices(matrix1, matrix2, result, rows1, cols1);
        printf("Результат сложения матриц:\n");
        printMatrix(result, rows1, cols1);
        printf("\n");
    } else {
        printf("ОШИБКА СЛОЖЕНИЯ, РАЗМЕРЫ НЕ РАВНЫ\n");
        printf("\n");
    }

    if (rows1 == rows2 || cols1 == cols2) {
        subMatrices(matrix1, matrix2, result, rows1, cols1);
        printf("Результат вычитания матриц:\n");
        printMatrix(result, rows1, cols1);
        printf("\n");
    }
    else {
        printf("ОШИБКА ВЫЧИТАНИЯ, РАЗМЕРЫ НЕ РАВНЫ\n");
        printf("\n");
    }

    
    if (cols1 == rows2) {
        result[10][10];
        multiplyMatrixByMatrix(matrix1, matrix2, result, rows1, cols1, cols2);
        printf("Результат умножения матриц:\n");
        printMatrix(result, rows1, cols2);
        printf("\n");
    } else {
        printf("УМНОЖЕНИЕ НЕВОЗМОЖНО: cols1 != rows2\n");
        printf("\n");
    }
    
    {printf("Введите число для умножения на первую матрицу: ");
     scanf("%d", &scalar);
     multiplyMatrixByScalar(matrix1, result, scalar, rows1, cols1);
     printf("Результат умножения первой матрицы на число:\n");
     printMatrix(result, rows1, cols1);
     printf("\n");
    }
     
    {  
     printf("Введите число для умножения на вторую матрицу: ");
     scanf("%d", &scalar);
     multiplyMatrixByScalar(matrix2, result, scalar, rows2, cols2);
     printf("Результат умножения второй матрицы на число:\n");
     printMatrix(result, rows2, cols2);
     printf("\n");
     }
    
    double det1 = 0.0;
    if (rows1 == cols1) {
        det1 = determinant(rows1, matrix1);
        printf("\nОпределитель (Matrix 1): %.2f\n", det1);
    } else {
        printf("Нельзя найти определитель первой матрицы, т.к. она не квадратная\n");
    }
    
    if (rows1 == cols1 || det1 == 0) {
        double inverse1[rows1][cols1];
     if (invertMatrix(rows1, matrix1, inverse1)) {
            printf("\nОбратная матрица (Matrix 1):\n");
            for (int i = 0; i < rows1; i++) {
                for (int j = 0; j < cols1; j++) {
                    printf("%8.2f", inverse1[i][j]);
                }
                printf("\n");
            }
        printf("\n");
        } else {
            printf("\nMatrix 1 нельзя найти обратную матрицу.\n");
        }
    }
    
    double det2 = 0.0;
    if (rows2 == cols2) {
        double det2 = determinant(rows2, matrix2);
        printf("\nОпределитель (Matrix 2): %.2f\n", det2);
    } else {
        printf("Нельзя найти определитель второй матрицы, т.к. она не квадратная\n");
    }
    
    if (rows2 == cols2 || det2 == 0) {
        double inverse2[rows2][cols2];
        if (invertMatrix(rows2, matrix2, inverse2)) {
            printf("\nОбратная матрица (Matrix 2):\n");
            for (int i = 0; i < rows2; i++) {
                for (int j = 0; j < cols2; j++) {
                    printf("%8.2f", inverse2[i][j]);
                }
                printf("\n");
            }
        printf("\n");
        } else {
            printf("\nMatrix 2 нельзя найти обратную матрицу.\n");
        }
    }
    
    return 1;
}
