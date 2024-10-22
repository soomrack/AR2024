#include <stdio.h> 


typedef long long int Money;


struct Person {
    Money salary;
    Money account;
    Money charges;
    Money rent;
    Money flat;
    Money loan;
    Money unexpected_situations;
    Money deposit;
    double deposit_percent;
};


struct Person Alice;
struct Person Bob;


void Bob_init()
{
    Bob.salary = 200 * 1000;
    Bob.account = 1000 * 1000;
    Bob.charges = 25 * 1000;
    Bob.rent = 40 * 1000;
    Bob.flat = 0;
    Bob.loan = 100 * 1000;
    Bob.unexpected_situations = 10 * 1000;
    Bob.deposit = 0;
    Bob.deposit_percent = 1.001;    // процент по депозиту //
}


void Alice_init()
{
    Alice.salary = 200 * 1000;
    Alice.account = 1000 * 1000;
    Alice.charges = 30 * 1000;
    Alice.rent = 0;
    Alice.flat = 14000 * 1000;
    Alice.loan = 100 * 1000;
    Alice.unexpected_situations = 10 * 1000;
    Alice.deposit = 0;
    Alice.deposit_percent = 1.001;           // процент по депозиту //  
}


void Bob_salary(const int month, const int year)
{
    if (month == 12) {
        Bob.salary *= 1.08;                            // 8% инфляция ежегодно //
    }
    Bob.account += Bob.salary;
}


void Bob_charges(const int month, const int year)
{
    if (month == 12) {
        Bob.rent *= 1.08;
        Bob.unexpected_situations *= 1.08;
    }
    Bob.account -= Bob.unexpected_situations - Bob.rent;
}


void Bob_deposit()
{
    Bob.deposit *= Bob.deposit_percent;
}


void Alice_salary(const int month, const int year)
{
    if (month == 12) {
        Alice.salary *= 1.08;
        Alice.flat *= 1.08;
    }
    Alice.account += Alice.salary;
}


void Alice_charges(const int month, const int year)
{
    if (month == 12) {
        Alice.unexpected_situations *= 1.08;
        Alice.loan *= 1.08;
    }
    Alice.charges = Alice.unexpected_situations + Alice.loan;
    Alice.account -= Alice.charges;
}


void Alice_deposit()
{
    Alice.deposit *= Alice.deposit_percent;
}


void simulation()
{
    int month = 9;
    int year = 2024;
    while (!(year == 2054 && month == 10)) {
        Alice_salary(month, year);
        Alice_charges(month, year);
        Alice_deposit();
        Bob_salary(month, year);
        Bob_charges(month, year);
        Bob_deposit();
        month++;
        if (month == 13) {
            year = year + 1;
            month = 1;
        }
    }
}


void Alice_printf()
{
    printf("Alice account = %lld \n", Alice.account);
}


void Bob_printf()
{
    printf("Bob account = %lld \n", Bob.account);
};


int main() {
    Alice_init();
    Bob_init();
    simulation();
    Alice_printf();
    Bob_printf();
    return 0;
}
