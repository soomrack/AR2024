#include <stdio.h>

typedef long long int  Money;


struct Mortgage {
    Money mortgage;
    Money month_mortgage;
};


struct Person {
    Money account;
    Money salary;
    Money apartment;
    Money rent;
    Money expenses;
    Mortgage mymortgage;
};


struct Person Alice;
struct Person Bob;


void init_Alice()
{
    Alice.account = 1000000;
    Alice.salary = 200000;
    Alice.expenses = 30000;
    Alice.apartment = 13000000;

    Alice.mymortgage.mortgage = Alice.apartment;
    Alice.mymortgage.mortgage -= Alice.account;
    Alice.mymortgage.mortgage *= 1.2;
    Alice.account = 0;

    Alice.mymortgage.month_mortgage = Alice.mymortgage.mortgage / (30 * 12);
}


void init_Bob()
{
    Bob.account = 1000000;
    Bob.salary = 200000;
    Bob.expenses = 30000;
    Bob.rent = 30000;
}


void alice_salary(int month, int year)
{
    Alice.account += Alice.salary;
    
    if(month == 9) Alice.salary *= 1.08;
}


void alice_expenses(int month, int salary)
{
    Alice.account -= Alice.expenses;

    if(month == 9) Alice.expenses *= 1.08;
}


void alice_apartment(int month, int year)
{
    if (month == 9) Alice.apartment *= 1.08;
}


void alice_mortgage(){
    Alice.account -= Alice.mymortgage.month_mortgage;
}


void alice_deposit(int month, int year)
{
    int percent = 20;

    Alice.account *= float(percent / 12);
}


void bob_salary(int month, int year)
{
    Bob.account += Bob.salary;

    if(month == 9) Bob.salary *= 1.08; 
}


void bob_expenses(int month, int salary)
{
    Bob.account -= Bob.expenses;

    if(month == 9) Bob.expenses *= 1.08;
}


void bob_rent(int month, int salary)
{
    Bob.account -= Bob.rent;

    if(month == 9) Bob.rent *= 1.08;
}


void bob_deposit(int month, int year)
{
    int percent = 20;

    Bob.account *= float(percent / 12);
}


void simulation()
{
    int month = 9;
    int year = 2024;

    while( !((month == 9) && (year == 2024 + 30)) ){
        alice_salary(month, year);
        alice_expenses(month, year);
        alice_apartment(month, year);
        alice_mortgage();
        alice_deposit(month, year);

        bob_salary(month, year);
        bob_rent(month, year);
        bob_expenses(month, year);
        bob_deposit(month, year);

        month++;
        if(month == 13) {
            month = 1;
            year++;
        }
    }
}

void print()
{
    if (Alice.account + Alice.apartment > Bob.account) printf ("Alice");
    else printf("Bob");
}


int main()
{
    init_Alice();
    init_Bob();
    simulation();
    print();
}
