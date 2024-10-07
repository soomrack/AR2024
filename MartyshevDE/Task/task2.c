#include <stdio.h>
#include <stdint.h>

struct Matrix {
    size_t cols; //кол-во столбцов
    size_t rows; // кол-во строк
    double* data;
};

struct Matrix Matrix_allocate (size_t cols, size_t rows)
{
    
};
