#include <stdio.h>
#include <stdint.h>

struct Matrix {
    size_t cols; //кол-во столбцов
    size_t rows; // кол-во строк
    double* data;
};

struct Matrix Matrix_allocate(size_t cols, size_t rows)
{
    struct Matrix A = {cols, rows, NULL};
    A.data = (double*)malloc(cols * rows * sizeof(double));

    if(A.data == NULL){
        //ERROR
        return (struct Matrix){0,0,NULL};
    }
};

if(cols * rows * sizeof(double) <= SIZE_MAX)

data [A.cols * roo + col];

memcpy (data_A, data_R, );
memset (data_A, size, 0);

int main() {
    return 0;
} 

//free (date);