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
    Money count;
    struct Mortgage mortgage;
    struct Bank bank;
};


struct Person Alice;
struct Person Bob;  


void Alice_money()
{
    Alice.count = 0;
    Alice.salary = 200 * 1000;
    Alice.expenses = 50 * 1000;
    Alice.remains = 0;

    Alice.mortgage.inter_rate = 0.20;
    Alice.mortgage.credit = 8000 * 1000;
    Alice.mortgage.month_pay = 150 * 1000;
}


void Alice_mortgage()
{
    Alice.count -= Alice.mortgage.month_pay;
}


void Alice_salary(const int month)
{
    if(month == 12) {
        Alice.count += Alice.salary;
    }

    if(month == 1) {
        Alice.salary *= 1.08;
    }

    Alice.count += Alice.salary;
}


void Alice_print()
{
    if (Alice.count > Bob.count) {
        printf ("Alice has more money than Bob on %lld\n", Alice.count - Bob.count);
    }

    if (Alice.count < Bob.count) {
        printf ("Bob has more money than Alice on %lld\n", Bob.count - Alice.count);
    }
    printf ("Alice capital = %lld \n", Alice.count);
}


void Bob_money()
{
    Bob.count = 0;
    Bob.salary = 200 * 1000;
    Bob.expenses = 50 * 1000;
    Bob.flat = 30 * 1000; 
    Bob.remains = 0;
    Bob.bank.invest = 120 * 1000;
}


void Bob_salary(const int month)
{
    if (month == 12) {
        Bob.count += Bob.salary;
    }
    if (month == 1) {
        Bob.salary *= 1.08;
    }

    Bob.count += Bob.salary;
}


void Bob_bank(int deposit)
{
    Bob.bank.vklad += (Bob.count * deposit / 100);
    Bob.bank.vklad += (Bob.bank.vklad * 0.01 / 12);
}


void Bob_print()
{
    printf ("Bob capital = %lld\n", Bob.count);
}


void Bob_car(int month, int flag)
{   
    if (Bob.bank.vklad >= 3 * 1000 * 1000 && flag == 1){
        Bob.count -= 3 * 1000 * 1000;
        Bob.bank.vklad -= 3 * 1000 * 1000;
        flag = 0;
    } else if(flag == 0 && month != 9){
        Bob.count -= 15 * 1000;
    } else if(flag == 0 && month == 9){
        Bob.count -= 40 * 1000;
    }
}




void simulation()
{
    int month = 1;
    int year = 2024;

    while( !((month == 1) && (year == 2055)) ) {
        
        Alice_salary(month);
        Alice_mortgage();
        
        Bob_salary(month);
        Bob_bank(20);

        Bob_car(month, 1);

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
