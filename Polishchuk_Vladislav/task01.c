#include <stdio.h>


typedef long long int Money;


struct Bank
{
    Money vklad;
    Money month_pay;
};


struct Mortgage
{
    double inter_rate;
    Money credit;
    Money pay;
    Money month_pay;
};


struct Person
{
    Money salary;
    Money expenses;
    Money status;
    Money flat;
    Money rubles; 
    struct Mortgage mortgage;
    struct Bank bank;
};


struct Person Alice;
struct Person Bob;  


void Alice_money()
{
    Alice.status = 0;
    Alice.salary = 200 * 1000;
    Alice.expenses = 50 * 1000;
    Alice.rubles = 0;

    Alice.mortgage.inter_rate = 0.20;
    Alice.mortgage.credit = 8000 * 1000;
    Alice.mortgage.month_pay = 150 * 1000;
}


void Alice_mortgage()
{
    Alice.status -= Alice.mortgage.month_pay;
}


void Alice_salary(const int month, const int year)
{
    if(month == 12) 
    {
        Alice.status += Alice.salary;
    }

    if(month == 1) 
    {
        Alice.salary *= 1.08;
    }

    Alice.status += Alice.salary;
}


void Alice_print()
{
    if (Alice.status > Bob.status) {
        printf ("Alice has more money than Bob on %lld\n", Alice.status - Bob.status);
    }

    if (Alice.status < Bob.status) {
        printf ("Bob has more money than Alice on %lld\n", Bob.status - Alice.status);
    }
    printf ("Alice capital = %lld \n", Alice.status);
}


void Bob_money()
{
    Bob.status = 0;
    Bob.salary = 200 * 1000;
    Bob.expenses = 50 * 1000;
    Bob.flat = 30 * 1000; 
    Bob.rubles = 0;
    Bob.bank.month_pay = 120 * 1000;
}


void Bob_salary(const int month, const int year)
{
    if (month == 12) 
    {
        Bob.status += Bob.salary;
    }
    if (month == 1) 
    {
        Bob.salary *= 1.08;
    }

    Bob.status += Bob.salary;
}


void Bob_bank(int deposit)
{
    int month = 9;
    int year = 2024;

    while( !((month == 9) && (year == 2054)) ) {

    deposit = 20; 
    Bob.status -= Bob.bank.month_pay;
    Bob.bank.vklad = (deposit/12)*0.01+1;
    Bob.rubles += (Bob.salary - Bob.bank.month_pay - Bob.expenses - Bob.flat);
    Bob.status += (Bob.bank.vklad + Bob.rubles);
    }
}


void Bob_flat(int year)
{
    year = 2024;
    if (year == 2034 || year == 2044 || year == 2054) {
        Bob.flat += 5000;
    }
}


void Bob_print()
{
    printf ("Bob capital = %lld\n", Bob.status);
}


void simulation()
{
    int month = 9;
    int year = 2024;

    while( !((month == 9) && (year == 2054)) ) {
        
        Alice_salary(month, year);
        Alice_mortgage();
        
        Bob_salary(month, year);
        Bob_flat(year);

        month++;
        if (month == 13) 
        {
            month = 1;
            year++;
        }
    }
}


int main()
{
    Alice_money();
    Bob_money();

    simulation();

    Alice_print();
    Bob_print();

    return 0;
}
