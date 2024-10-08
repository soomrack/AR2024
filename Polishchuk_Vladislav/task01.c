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
    Money remains;
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
    Alice.remains = 0;

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
    if(month == 12) {
        Alice.status += Alice.salary;
    }

    if(month == 1) {
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
    Bob.remains = 0;
    Bob.bank.month_pay = 120 * 1000;
}


void Bob_salary(const int month, const int year)
{
    if (month == 12) {
        Bob.status += Bob.salary;
    }
    if (month == 1) {
        Bob.salary *= 1.08;
    }

    Bob.status += Bob.salary;
}


void Bob_bank(int deposit)
{
    Bob.bank.vklad += (Bob.status * deposit / 100);
    Bob.bank.vklad += (Bob.bank.vklad * 0.01 / 12);
}



void Bob_flat(int year)
{
    year = 2024;
    if (year == 2034 || year == 2044 || year == 2054) {
        Bob.flat += 10000;
    }
}


void Bob_print()
{
    printf ("Bob capital = %lld\n", Bob.status);
}


void Bob_car(int year, int month)
{   
    if (year == 2031 && month == 3 && Bob.status == 15 * 1000 * 1000){
        Bob.status -= 15 * 1000 * 1000;
    }
    else if(year >= 2031 && month > 3){
        Bob.status -= 15 * 1000;
    }
    else if(month == 9){
        Bob.status -= 50 * 1000;
    }
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
        Bob_bank(20);

        Bob_car(year, month);

        month++;
        if (month == 13) {
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
