#include <stdio.h>

typedef long long int Money;


struct Cat {
    Money catfood;
    int life_cat;
};


struct Mortgage {
    Money mortgage;
    Money month_mortgage;
};


struct Person {
    Money salary;
    Money expenses;
    Money flat;
    Money rent_flat;
    Money account;
    struct Cat person_cat;
    struct Mortgage person_mortgage;
};


struct Person Bob;
struct Person Alice;


void Bob_init()
{
    Bob.account = 1200000;
    Bob.salary = 300000;
    Bob.expenses = 40000;
    Bob.rent_flat = 35000;
};


void Alice_init()
{
    Alice.account = 1200000;
    Alice.salary = 300000;
    Alice.expenses = 40000;
    Alice.flat = 13000000;
    
    Alice.person_cat.catfood = 7000;
    Alice.person_cat.life_cat = 15;

    Alice.person_mortgage.mortgage = Alice.flat;
    Alice.person_mortgage.mortgage -= Alice.account;
    Alice.person_mortgage.mortgage *= 1.2;
    Alice.account = 0;

    Alice.person_mortgage.month_mortgage = Alice.person_mortgage.mortgage / (30 * 12);
};


void Bob_salary(const int month, const int year)
{
    Bob.account += Bob.salary;

      if (month == 12) {
            Bob.account += Bob.salary;
        }

    if (month == 1) {
        Bob.salary *= 1.06;
    }
};


void Bob_expenses(const int month, const int year)
{
    Bob.account -= Bob.expenses;

    if (month == 1) {
        Bob.expenses *= 1.06;
    }
};


void Bob_rent_flat(const int month, const int year)
{
    Bob.account -= Bob.rent_flat;

    if (month == 1) {
    Bob.rent_flat *= 1.06;
   }
};


void Bob_deposit(const int month, const int year)
{

    Bob.account *= 1 + (0.2 / 12);
};


void Alice_salary(const int month, const int year)
{
    Alice.account += Alice.salary;
    
    if (month == 1) {
        Alice.salary *= 1.06;
    }
};


void Alice_expenses(const int month, const int year)
{
    Alice.account -= Alice.expenses;

    if (month == 1) {
        Alice.expenses *= 1.06;
    }
};


void Alice_flat(const int month, const int year)
{
    if (month == 1) {
        Alice.flat *= 1.06;
    }
};


void Alice_mortgage()
{
    Alice.account -= Alice.person_mortgage.month_mortgage;
};


void Alice_deposit(const int month, const int year)
{
    Alice.account *= 1 + (0.2 / 12);
};


void Alice_cat(const int month, const int year) {

    if (month == 1) {
        Alice.person_cat.catfood *= 1.06;
    }

    if ((year >= 2027) && (year <= (2027 + Alice.person_cat.life_cat))) {

        Alice.account -= Alice.person_cat.catfood;
    }
};


void simulation()
{
    int month = 1;
    int year = 2024;

    while( !((month == 1) && (year == 2054)) ) {
        Bob_salary(month, year);
        Bob_expenses(month, year);
        Bob_rent_flat(month, year);
        Bob_deposit(month, year);

        Alice_salary(month, year);
        Alice_expenses(month, year);
        Alice_flat(month, year);
        Alice_mortgage();
        Alice_deposit(month, year);
        Alice_cat(month, year);

        month++;
        if (month == 13) {
            month = 1;
            year++;
        }
    }
};

void print()
{
    if (Alice.account + Alice.flat < Bob.account) {
        printf("Bob will save up for a flat faster");
    }
    else {
        printf("Alice will pay off the mortgage faster");
    }
};


int main()
{
    Alice_init();
    Bob_init();

    simulation();
    
    print();
}
