#include <stdio.h>
#include <locale.h>
int main() {
    setlocale(LC_ALL, "Russian");

    long long int Count_Bob, Count_Alice, month, year, expenses_Alice, expenses_Bob, salary, payment, inflation, deposit, allowance, rate, mlnA, tysA, mlnB, tysB, A, B, C, D;
    Count_Bob = 0;
    Count_Alice = 0;
    payment = 185337; // платеж по ипотеке 185 337
    salary = 300000;
    month = 9;
    year = 2024;
    inflation = 9;
    expenses_Alice = 65000; // итого65/мес для эл
    expenses_Bob = 90000; // итого90/мес для бб
    deposit = 1000000;
    allowance = 9;
    rate = 20;
    printf("Alice:                Bob:\n");
    for (month=9; year <= 2054; month++) {
        Count_Alice = Count_Alice + salary - expenses_Alice - payment;
        Count_Bob = Count_Bob + salary - expenses_Bob;
        B = Count_Bob;
        A = Count_Alice;
        if(month == 9 && year == 2054){

    C = Count_Bob - Count_Alice;
    D = Count_Alice - Count_Bob;
    while (C / 1000 > 1) {
        mlnB = C / 1000000;
        C = C % 1000000;
        tysB = C / 1000;
        C = C % 1000;
    }
    while (D / 1000 > 1) {
        mlnA = D / 1000000;
        D = D % 1000000;
        tysA = D / 1000;
        D = D % 1000;
    }

    if (D > C) {
        printf("Alice, с разницей =  %lldмлн %lldтыс %lldруб\n", mlnA, tysA, D);
    } else {
        printf("Bob, с разницей = %lldмлн %lldтыс %lldруб\n", mlnB, tysB, C);
    }

return 0;
        }
        while (B / 1000 > 1) {
            mlnB = B / 1000000;
            B = B % 1000000;
            tysB = B / 1000;
            B = B % 1000;
        }
        while (A / 1000 > 1) {
            mlnA = A / 1000000;
            A = A % 1000000;
            tysA = A / 1000;
            A = A % 1000;
        }

        if (month % 12 == 0) {
            printf("%lldмлн %lldтыс %lldруб    %lldмлн %lldтыс %lldруб    %lld-й год\n", mlnA, tysA, A, mlnB, tysB, B, year);
            month = 1;
            year++;
            salary = salary + (salary / 100) * allowance;
            expenses_Alice = expenses_Alice + ((expenses_Alice / 100) * inflation);
            expenses_Bob = expenses_Bob + ((expenses_Bob / 100) * inflation);
            deposit = deposit + ((deposit / 100) * (rate - inflation));
        }

    }
    Count_Alice = Count_Alice + 13000000;
    Count_Bob = Count_Bob + deposit;
    C = Count_Bob - Count_Alice;
    D = Count_Alice - Count_Bob;
    while (C / 1000 > 1) {
        mlnB = C / 1000000;
        C = C % 1000000;
        tysB = C / 1000;
        C = C % 1000;
    }
    while (D / 1000 > 1) {
        mlnA = D / 1000000;
        D = D % 1000000;
        tysA = D / 1000;
        D = D % 1000;
    }

    if (D > C) {
        printf("Alice, с разницей =  %lldмлн %lldтыс %lldруб\n", mlnA, tysA, D);
    } else {
        printf("Bob, с разницей = %lldмлн %lldтыс %lldруб\n", mlnB, tysB, C);
    }

    return 0;
}
