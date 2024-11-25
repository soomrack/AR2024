#include <stdio.h>

typedef long long int Money;
double infliation = 1.09;

struct Mortgage{
    double rate;
    Money credit;
    Money pay;
    Money month_pay;
};


struct Bank{
    double rate;
    Money deposit;
    Money month_pay;
};


struct Person{
    Money salary;
    Money expense;
    Money saving;

    Money apartment;

    struct Mortgage mortgage;
    struct Bank Bank;
}; 


struct Person Alice;
struct Person Bob;  


void Alice_init()
{
    Alice.saving = 1300 * 1000;
    Alice.salary = 300 * 1000;
    Alice.expense = 50 * 1000;

    Alice.mortgage.rate = 17 * 0.01;
    Alice.mortgage.credit = 13 * 1000 * 1000;
    Alice.mortgage.month_pay = 150 * 1000;
}


void Alice_mortgage()
{
    Alice.saving -= Alice.mortgage.month_pay;
}


void Alice_salary(int const month)
{
    if (month == 12) {
        Alice.salary *= infliation;
    }
    Alice.saving += Alice.salary;
}


void Alice_expense(int year, int const month)
{
    Alice.saving -= Alice.expense;
}


void Bob_init()
{
    Bob.saving = 1300 * 1000;
    Bob.salary = 300 * 1000;
    Bob.expense = 50 * 1000;
    Bob.apartment = 75 * 1000;
    Bob.Bank.rate = 0.2;

    Bob.Bank.deposit = 0;
}


void Bob_Bank()
{
    int year = 2024;
    int month = 8;

    Bob.Bank.deposit *= Bob.Bank.rate;
    Bob.Bank.deposit += Bob.saving;
    Bob.saving = 0;

    Bob.Bank.deposit += Bob.salary - Bob.expense - Bob.Bank.month_pay;
}


void Bob_apartment(int start_year, int year, int const month)
{
    Bob.saving -= Bob.Bank.month_pay;
    if (((year - start_year) % 5 == 0) && (month == 8)) {
        Bob.Bank.month_pay += 5000;
    }
}


void Bob_salary(const int month)
{
    if(month == 12) {
        Bob.salary *= infliation;
    }
}


void Bob_cat()
{
    int Cat_cost = 50 * 1000;
    int Cat_expense = 5000;

    Bob.saving -= Cat_expense;
}


void simulation()
{
    int years_simulation = 30;
    int start_year = 2024;
    int month = 9;
    int year = start_year;
    int end_year = start_year + years_simulation;

    while(!((month == 9) && (year == end_year))) {

        Alice_salary(month);
        Alice_mortgage();
        
        Bob_salary(month);
        Bob_apartment(start_year, year, month);
        Bob_cat();
        Bob_Bank();
        
        month++;
        if(month == 13) {
            month = 1;
            year ++;
        }
    }
}


void Bob_print()
{
    printf ("\n Bob capital = %lli", Bob.Bank.deposit);
}


void Alice_print()
{
    if (Alice.saving > Bob.Bank.deposit) {
        printf ("\n Alice has more money than Bob on %lli", Alice.saving - Bob.Bank.deposit);
    }

    if (Alice.saving < Bob.Bank.deposit) {
        printf ("\n Bob has more money than Alice on %lli", Bob.Bank.deposit - Alice.saving);
    }

    printf (" \n Alice capital = %lli", Alice.saving);
}


int main()
{
    Alice_init();

    Bob_init();

    simulation();

    Alice_print();

    Bob_print();

    return 1;
}