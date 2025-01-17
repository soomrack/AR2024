#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义向量结构体
struct Vector {
    size_t size;
    double* data;
};
typedef struct Vector Vector;

// 定义异常级别枚举类型
enum VectorExceptionLevel { ERROR, WARNING, INFO, DEBUG };

// 向量异常处理函数
void vector_exception(const enum VectorExceptionLevel level, const char* msg)
{
    if (level == ERROR) {
        printf("ERROR: %s", msg);
    }
    if (level == WARNING) {
        printf("WARNING: %s", msg);
    }
}

// 分配指定大小的向量内存空间
Vector vector_allocate(const size_t size)
{
    Vector v = { 0, NULL };
    if (size == 0) {
        return v;
    }
    v.data = (double*)malloc(size * sizeof(double));
    if (v.data == NULL) {
        vector_exception(ERROR, "Memory allocation failed for vector.");
        return v;
    }
    v.size = size;
    return v;
}

// 释放向量内存空间
void vector_free(Vector* v)
{
    free(v->data);
    v->size = 0;
    v->data = NULL;
}

// 设置向量元素值，添加合法性检查
void vector_set(Vector v, const double* values)
{
    if (v.size > 0 && values!= NULL) {
        memcpy(v.data, values, v.size * sizeof(double));
    }
}

// 打印向量元素
void vector_print(const Vector v)
{
    for (size_t i = 0; i < v.size; ++i) {
        printf("%2.3f ", v.data[i]);
    }
    printf("\n");
}

// 向量相加，v1 += v2
int vector_add(Vector v1, Vector v2)
{
    if (v1.size!= v2.size) {
        vector_exception(ERROR, "vector_add: Incompatible sizes.");
        return 0;
    }
    for (size_t i = 0; i < v1.size; ++i) {
        v1.data[i] += v2.data[i];
    }
    return 1;
}

// 计算向量点积的函数
double vector_dot_product(Vector v1, Vector v2) {
    if (v1.size!= v2.size ) {
        vector_exception(ERROR, "vector_dot_product: Incompatible sizes.");
        return NAN;
    }
    double result = 0.0;
    for (size_t i = 0; i < v1.size; ++i) {
        result += v1.data[i] * v2.data[i];
    }
    return result;
}

int main()
{
    Vector v1, v2;
    double arr1[] = { 1., 2., 3., 4. };
    double arr2[] = { 5., 6., 7., 8. };
    v1 = vector_allocate(4);
    v2 = vector_allocate(4);
    vector_set(v1, arr1);
    vector_set(v2, arr2);
    vector_print(v1);
    vector_print(v2);

    vector_add(v1, v2);
    vector_print(v1);

    double dotProductResult = vector_dot_product(v1, v2);
    printf("The dot product of the two vectors is: %2.3f\n", dotProductResult);

    vector_free(&v1);
    return 1;
}
