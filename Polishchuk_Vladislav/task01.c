#include <stdio.h>


typedef long long int Money;


struct Bank {
    Money vklad;
    Money invest;
};


struct Mortgage {
    double inter_rate;
    Money credit;
    Money month_pay;
};


struct Person {
    Money salary;
    Money expenses;
    Money flat;
    Money remains;
    struct Mortgage mortgage;
    struct Bank bank;
};


struct Person Alice;
struct Person Bob;  


void Alice_expenses()
{
    Alice.expenses = 50 * 1000;
}


void Alice_money()
{
    Alice.bank.vklad = 0;
    Alice.salary = 200 * 1000;
    
    Alice.remains = 0;

    Alice.mortgage.inter_rate = 0.20;
    Alice.mortgage.credit = 8000 * 1000;
    Alice.mortgage.month_pay = 150 * 1000;
}


void Alice_mortgage()
{
    Alice.bank.vklad -= Alice.mortgage.month_pay;
}


void Alice_salary(const int month)
{
    if(month == 12) {
        Alice.bank.vklad += Alice.salary;
    }

    if(month == 1) {
        Alice.salary *= 1.08;
    }

    Alice.bank.vklad += Alice.salary;
}


void Alice_print()
{
    if (Alice.bank.vklad > Bob.bank.vklad) {
        printf ("Alice has more money than Bob on %lld\n", Alice.bank.vklad - Bob.bank.vklad);
    }

    if (Alice.bank.vklad < Bob.bank.vklad) {
        printf ("Bob has more money than Alice on %lld\n", Bob.bank.vklad - Alice.bank.vklad);
    }
    printf ("Alice capital = %lld \n", Alice.bank.vklad);
}


void Bob_expenses()
{
    Bob.expenses = 50 * 1000;
}


void Bob_money()
{
    Bob.bank.vklad = 0;
    Bob.salary = 200 * 1000;
    Bob.flat = 30 * 1000; 
    Bob.remains = 0;
    Bob.bank.invest = 120 * 1000;
}


void Bob_salary(const int month)
{
    if (month == 12) {
        Bob.bank.vklad += Bob.salary;
    }
    if (month == 1) {
        Bob.salary *= 1.08;
    }

    Bob.bank.vklad += Bob.salary;
}


void Bob_bank(const int rate)
{
    Bob.bank.vklad += (Bob.bank.vklad * rate / 100);
}


void Bob_print()
{
    printf ("Bob capital = %lld\n", Bob.bank.vklad);
}


void Bob_car(int month)
{   
    static int has_car = 0;

    if (Bob.bank.vklad >= 3 * 1000 * 1000 && has_car == 0){
        Bob.bank.vklad -= 3 * 1000 * 1000;
        has_car = 1;
    } 
    if(has_car == 1){
        if (month == 9){
            Bob.bank.vklad -= 15 * 1000;
        }
        else{
            Bob.bank.vklad -= 40 * 1000;
        }
    }
}




void simulation()
{
    int month = 1;
    int year = 2024;

    while( !((month == 1) && (year == 2055)) ) {
        
        Alice_salary(month);
        Alice_mortgage();
        Alice_expenses();
        
        Bob_salary(month);
        Bob_bank(20);
        Bob_car(month);
        Bob_expenses();

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
