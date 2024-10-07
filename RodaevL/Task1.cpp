// Task1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

// ставки для подсчетов
const float RealInflateRate = 1 + 9 / 100;
const float RealSalaryIncrease = 1 + 9 / 100;

struct Bob
{
    float Deposit;
    float DepositRate; 
    float RentAMonth; 
    float SalaryAMonth; 
    int MonthCount;
};

struct Alice
{
    float FirstPay;
    float Credit;
    float CreditRate;
    float SalaryAMonth;
    int MonthCount;
};

float Calculation_Bob(Bob Data)      // сумма вклада
{
    float Result = 0;
    // ставка деозита для подсчета
    float RealDepositRate = 1 + Data.DepositRate / 100;
    // сумма депозита после нескольких лет
    Data.Deposit *= pow(RealDepositRate, Data.MonthCount);


    for (int Month = 1; Month <= Data.MonthCount; Month++)
    {
        Result += (Data.SalaryAMonth - Data.RentAMonth);  // зарплата - аренда

        Data.SalaryAMonth *= RealSalaryIncrease; // повышение зарплаты
        Data.RentAMonth *= RealInflateRate; // повышение стоимости аренды
    }

    return Result + Data.Deposit;
}

float Calculation_Alice(Alice Data)
{
    float Result = 0;

    // ежемесячная ставка
    float RealCreditRate = Data.CreditRate / 100; // теперь НЕ в процентах
    // формула расчета "общей ставки"
    float GeneralCreditRate = pow(1 + Data.CreditRate, Data.MonthCount);
    // платеж в месяц
    float PaymentAMonth = Data.Credit * RealCreditRate * GeneralCreditRate / (GeneralCreditRate - 1);

    for (int Month = 1; Month <= Data.MonthCount; Month++)
    {
        Result += (Data.SalaryAMonth - PaymentAMonth) * 12;  // зарплата - ежемесячный платеж

        Data.SalaryAMonth *= RealSalaryIncrease; // повышение зарплаты
    }

    return Result - Data.FirstPay;
}


int main()
{
    printf("Bob:%.2f\n", Calculation_Bob({ 1000000, 12,30000,200000, 30 }));
    printf("Alice:%.2f\n", Calculation_Alice({ 1000, 13000000, 17, 200000, 30 }));
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
