#include <stdio.h>

struct Matrix {
    size_t cols;
    size_t rows;
    double* date;
}

struct Matrix Matrix_allocate (size_t cols, size_t rows) {
    data = malloc (cols*rows*sizeof(double))
    if (data == NULL) {
        return (struct {0,0,null})
    }
}

void Matrix_free () {
    if (data != NULL) {
        free(data);
        data = NULL;
    }
}
