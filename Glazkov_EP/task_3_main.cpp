#include <iostream>
#include <windows.h>

#include "matrix.hpp"

int main(int argc, char* argv[]) {
    // Задаем кодировку, чтобы кириллица выводилась корректно
    SetConsoleOutputCP(CP_UTF8);

    double a[] = {1, 2,
                  3, 4};
    double b[] = {5, 6,
                  7, 8};

    Matrix a_ = Matrix(a, 2, 2);
    Matrix b_ = Matrix(b, 2, 2);

    Matrix sumMatrix = a_.sum(b_);
    Matrix subMatrix = a_.sub(b_);
    Matrix mulMatrix = a_.mul(b_);
    
    std::cout << "Матрица A\n";
    a_.print();

    std::cout << "Матрица B\n";
    b_.print();

    std::cout << "Сумма матриц\n";
    sumMatrix.print();

    std::cout << "Вычитание матриц\n";
    subMatrix.print();

    std::cout << "Умножение матриц\n";
    mulMatrix.print();

    return 0;
}
