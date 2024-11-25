#include <stdio.h>
#include <stdbool.h>
int rowsA, colsA, rowsB, colsB, matrixA[100][100], matrixB[100][100], matrixAB[100][100], cons, E[100][100],expa[100][100], obr[100][100], n;double A[100][100] ;float det;
int mat_E(){
    for (int i=0;i<rowsA;++i){
        for (int j=0;j<colsA;++j){
            if (i==j){
                E[i][j]=1;
            }
            if (i!=j){
                E[i][j]=0;
            }
        }
    }
}
int vvod(){
    printf("Введите размер квадратной матрицы: ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    printf("Введите элемент [%d][%d]: ",i+1,j+1);
                    scanf("%lf", &A[i][j]);
            }
            }
}
int mat_vvodA(){
    printf("Введите количество строк и столбцов матрицы A через пробел: ");
        scanf("%d%d", &rowsA,&colsA);
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsA; ++j) {
                printf("Введите элемент [%d][%d]: ", i + 1, j + 1);
                scanf("%d", &matrixA[i][j]);
            }
        }
        printf("\nМатрица A:\n");
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsA; ++j) {
                printf("%d ", matrixA[i][j]);
            }
            printf("\n");
        }
}
int mat_vvodB(){
    printf("Введите количество строк и столбцов матрицы B через пробел: ");
        scanf("%d%d", &rowsB,&colsB);
        for (int i = 0; i < rowsB; ++i) {
            for (int j = 0; j < colsB; ++j) {
                printf("Введите элемент [%d][%d]: ", i + 1, j + 1);
                scanf("%d", &matrixB[i][j]);
            }
        }
        printf("\nМатрица B:\n");
        for (int i = 0; i < rowsB; ++i) {
            for (int j = 0; j < colsB; ++j) {
                printf("%d ", matrixB[i][j]);
            }
            printf("\n");
        }
}
int mat_umn() {
        if (rowsA!=colsB) { 
            printf("Данные матрицы нельзя перемножить\n");
            return(0);
        }
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsB; ++j) {
                matrixAB[i][j]=0;
                for (int k=0;k<colsA;++k) {
                    matrixAB[i][j]+=matrixA[i][k]*matrixB[k][j];
                }
            }
        }
        printf("\nМатрица A*B:\n");
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsB; ++j) {
                printf("%d ", matrixAB[i][j]);
            }
            printf("\n");
        }
        
}
int mat_umn_const() {
        printf("Введите константу: ");
        scanf("%d", &cons);
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsA; ++j) {
               matrixA[i][j]*=cons;
            }
        }
        printf("\nМатрица A*const:\n");
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsA; ++j) {
                printf("%d ", matrixA[i][j]);
            }
            printf("\n");
        }
}
int mat_slozh(){
        if (rowsA!=rowsB || colsA!=colsB){
            printf("Данные матрицы нельзя сложить\n");
            return(0);
        }
       
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsB; ++j) {
                matrixAB[i][j]= matrixA[i][j]+matrixB[i][j];
                }
            }
        
        printf("\nМатрица A+B:\n");
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsB; ++j) {
                printf("%d ", matrixAB[i][j]);
            }
            printf("\n");
        }
}
int mat_min(){
        if (rowsA!=rowsB || colsA!=colsB){
            printf("Из матрицы А нельзя вычесть матрицу B\n");
            return(0);
        }
       
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsB; ++j) {
                matrixAB[i][j]= matrixA[i][j]-matrixB[i][j];
                }
            }
        
        printf("\nМатрица A-B:\n");
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsB; ++j) {
                printf("%d ", matrixAB[i][j]);
            }
            printf("\n");
        }
}   
int mat_exp(){
    mat_E();
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            expa[i][j]=E[i][j]+matrixA[i][j];
    return(0);
        }
        }
}   
double mat_det(double A[][100], int n) {
    float det = 0;
    if (n == 1){
        return A[0][0];}
    if (n == 2)
        return A[0][0]*A[1][1] - A[0][1]*A[1][0];
    double minor[100][100];
    int zn = 1;
    for (int i = 0; i < n; i++) {
        for (int p = 1; p < n; p++) {
            int h = 0;
            for (int j = 0; j < n; j++) {
                if (j == i)
                    continue;
                minor[p-1][h++] = A[p][j];
            }
        }
        det += zn * A[0][i] * mat_det(minor, n-1);
        zn *= -1;
    }
    return det;
}
double mat_obr(double A[][100],int n){
    if (n == 1){
        printf("%.3f\n",n/mat_det(A,n));
        return(0);
    }
    double alg_dop[n][n];
    double minor[n-1][n-1];
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
             for (int k=0;k<n;k++){
                 for (int l=0;l<n;l++){
                     if (k!=i && l!=j){
                         minor[i][j]=A[k][l];
                         printf("%.0f %.0f\n",A[i][j], minor[i][j]);
                     }
                     
                 }
             }     
        }
    }
    
    
    }
int main() {
    printf("Добро пожаловать\n");
    int ans;
    while (1) {
        printf("\nВыберите действие(введите цифру):\n1) Перемножить матрицы A и B\n2) Умножить матрицу А на константу\n3) Сложить матрицы А и В\n4) Вычесть из матрицы А матрицу B\n5) Найти матричный экспанентум\n6) Вычислить определитель матрицы A\n7) Вычислить обратную матрицу\n8) Выйти из программы\n\n");
        scanf("%d", &ans);
        printf("\n");
        if (ans==8){
            break;
        }
        switch (ans) {
            case 1:mat_vvodA(),mat_vvodB(),mat_umn();break;
            case 2:mat_vvodA(),mat_umn_const();break;
            case 3:mat_vvodA(),mat_vvodB(),mat_slozh();break;
            case 4:mat_vvodA(),mat_vvodB(),mat_min();break;
            case 5:mat_vvodA(),mat_exp();break;
            case 6:vvod(),
            det = mat_det(A, n);
            printf("Определитель матрицы: %.2f\n", det);
            break;
            case 7:
            mat_obr(A,n);
            break;
        }
    }
    return 0;
}