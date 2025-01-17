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

void Alice_init(){
    Alice.saving = 1300 * 1000;
    Alice.salary = 300 * 1000;
    Alice.expense = 50 * 1000;

    Alice.mortgage.rate = 17 * 0.01;
    
    Alice.mortgage.month_pay = 150 * 1000;
}
void Alice_credit()
{
    Alice.mortgage.credit -= Alice.saving;
    Alice.saving = 0;
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

void Alice_expense()
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
}
void Bob_cat(year)
{
    Bob.expense += 5000;
    if(year == 2036){
        Bob.expense -= 5000;
    }
}
void Bob_d_cat(year)
{
    if(year == 2036){
        Bob.saving -= 5000;
    }
}
void Bob_saving()
{
    Bob.saving += Bob.salary;
    Bob.saving -= Bob.apartment;
    Bob.saving -= Bob.expense;
}

void Bob_apartment(const int month)
{
    if(month == 12){
    Bob.apartment *= infliation;
    }
}

void Bob_salary(const int month)
{
    if(month == 12){
        Bob.salary *= infliation;
    }
}

void simulation()
{
    int years_simulation = 30;
    int start_year = 2024;
    int month = 9;
    int year = start_year;
    int end_year = start_year + years_simulation;

    while(!((month == 9) && (year == end_year))) {

        Alice_credit();
        Alice_salary(month);
        Alice_mortgage();
        Alice_expense();
        
        Bob_saving();
        Bob_Bank();
        Bob_salary(month);
        Bob_apartment(month);
        Bob_cat(year);
        Bob_d_cat(year);
        
        month++;
        if(month == 13) {
            month = 1;
            year ++;
        }
    }
}
void Bob_print()
{
    if (Alice.saving < Bob.Bank.deposit) {
        printf ("\n Bob has more money than Alice on %i", Bob.Bank.deposit - Alice.saving);
    }
    
    printf ("\n Bob capital = %i", Bob.Bank.deposit);
}

void Alice_print()
{
    if (Alice.saving > Bob.Bank.deposit) {
        printf ("\n Alice has more money than Bob on %i", Alice.saving - Bob.Bank.deposit);
    }

    printf (" \n Alice capital = %i", Alice.saving);
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
