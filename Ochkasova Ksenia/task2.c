#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_SIZE 100
#define get_rundom_num(min, max) rand() % (max - min + 1) + max 

struct Matrix 
{
    size_t cols; 
    size_t rows;  
    double* data;
}; 
typedef struct Matrix Matrix;


void fillMatrix(int matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = get_rundom_num(0, 100);
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

 void multiplyMatrixByScalar(int matrix[MAX_SIZE][MAX_SIZE], int result[MAX_SIZE][MAX_SIZE], int scalar, int cols, int rows) {
     for (int i = 0; i < rows; i++) {
         for (int j = 0; j < cols; j++) {
             result[i][j] = matrix[i][j] * scalar;
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
    int cols, rows;

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
    printf("Вторая матрица:\n");
    printMatrix(matrix2, rows2, cols2);

    int result[100][100];
    
    int scalar;

    if (rows1 == rows2 || cols1 == cols2) {
        addMatrices(matrix1, matrix2, result, rows1, cols1);
        printf("Результат сложения:\n");
        printMatrix(result, rows1, cols1);
        printf("\n");
    } else {
        printf("ОШИБКА СЛОЖЕНИЯ, РАЗМЕРЫ НЕ РАВНЫ\n");
    }

    if (rows1 == rows2 || cols1 == cols2) {
        subMatrices(matrix1, matrix2, result, rows1, cols1);
        printf("Результат вычитания:\n");
        printMatrix(result, rows1, cols1);
        printf("\n");
    }
    else {
        printf("ОШИБКА ВЫЧИТАНИЯ, РАЗМЕРЫ НЕ РАВНЫ\n");
    }

    
    if (cols1 == rows2) {
        result[10][10];
        multiplyMatrixByMatrix(matrix1, matrix2, result, rows1, cols1, cols2);
        printf("Результат умножения:\n");
        printMatrix(result, rows1, cols2);
        printf("\n");
    } else {
        printf("УМНОЖЕНИЕ НЕВОЗМОЖНО: cols1 != rows2\n");
        return 1;
    }
    
    
    {printf("Введите число для умножения: ");
     scanf("%d", &scalar);
     multiplyMatrixByScalar(matrix1, result, scalar, rows1, cols1);
     printMatrix(result, rows1, cols1);
     printf("\n");
     
      
     printf("Введите число для умножения: ");
     scanf("%d", &scalar);
     multiplyMatrixByScalar(matrix2,result, scalar, rows2, cols2);
     printMatrix(result, rows2, cols2);
     printf("\n");
     }
     
     
    return 1;
}
