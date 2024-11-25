#include <stdio.h>

typedef long long Money;
int month = 9;
int year = 2024;


struct Person
{
    Money salary;   
    Money for_living;   
    Money account;  
    Money house; 
    Money house_rent; 
    Money expenses; 
    Money mortgage; 
    double deposit;
};


struct Person Alice =
{
    .salary=200*1000,
    .for_living=50*1000,
    .account=0,
    .house=13000*1000,
    .house_rent=0,
    .expenses=0,
    .mortgage=12*1000,
    .deposit=1.2
};


struct Person Bob =
{
    .salary=200*1000,
    .for_living=50*1000,
    .account=0,
    .house=13000*1000,
    .house_rent=30*1000,
    .expenses=0,
    .mortgage=0,
    .deposit=1.20
};


void alice_house(const int month, const int year)
{
    if (month == 12)
    {
        Alice.house *= 1.09;
    }
    if (month == 9 && year == 2024+30)
    {
        Alice.account += Alice.house;
    }
}


void alice_salary(const int month, const int year)
{
    if (month == 12)
    {
        Alice.salary *= 1.09;
        Alice.account*=Alice.deposit;
    }

    Alice.account += Alice.salary;  
}


void alice_expenses(const int month,const int year)
{
    if (month == 12)
    {
        Alice.for_living *=1.09;    
    }

    Alice.expenses = Alice.for_living + Alice.mortgage;
    Alice.account -= Alice.expenses;
}



void bob_salary(const int month,const int year)
{
    if (month == 12)
    {
        Bob.salary *= 1.09; 
        Bob.account*=Bob.deposit;
    }

    Bob.account += Bob.salary;
}


void bob_expenses(const int month,const int year)
{
    if (month == 12)
    {
        Bob.for_living *= 1.09; 
        Bob.house_rent *= 1.09;
    }

    Bob.expenses = Bob.for_living + Bob.house_rent;
    Bob.account -= Bob.expenses;    
}


void simulation()
{
    while (!(year == 2024+30 && month == 10))
    {
        alice_house(month, year);
        alice_salary(month, year);
        alice_expenses(month, year);
        bob_salary(month,year);
        bob_expenses(month, year);
        month++;

        if (month == 13)
        {
            year++;
            month = 1;
        }
    }
}


void result()
{
    if (Alice.account > Bob.account)
    {
        printf("Алиса богаче на %lld\n", Alice.account - Bob.account);
    }
    else
    {
        printf("Боб богаче на %lld\n", Bob.account - Alice.account);
    }
}


int main ()
{
    simulation();
    result();
    return 0;
}
