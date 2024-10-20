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
};

struct Deposit
{
    Money deposit;
    double rate;
};


struct Person Alice = { 300 * 1000, 100 * 1000, 0, 14000 * 1000, 0, 0, 150 * 1000 };
struct Person Bob = { 300 * 1000, 100 * 1000, 0, 14000 * 1000, 40 * 1000, 0, 0, };


void alice_house(const int month, const int year)
{
    if (month == 12) {
        Alice.house *= 1.08;
    }
    if (month == 9 && year == 2024 + 30) {
        Alice.account += Alice.house;
    }
}


void alice_salary(const int month, const int year)
{
    if (month == 12) {
        Alice.salary *= 1.06;
    }

    Alice.account += Alice.salary;
}


void alice_expenses(const int month, const int year)
{
    if (month == 12) {
        Alice.for_living *= 1.08;
    }

    Alice.expenses = Alice.for_living + Alice.mortgage;
    Alice.account -= Alice.expenses;
}



void bob_salary(const int month, const int year)
{
    if (month == 12) {
        Bob.salary *= 1.06;
    }

    Bob.account += Bob.salary;
}


void bob_expenses(const int month, const int year)
{
    if (month == 12) {
        Bob.for_living *= 1.08;
        Bob.house_rent *= 1.08;
    }

    Bob.expenses = Bob.for_living + Bob.house_rent;
    Bob.account -= Bob.expenses;
}


void simulation()
{
    while (!(year == 2024 + 30 && month == 10)) {
        alice_house(month, year);
        alice_salary(month, year);
        alice_expenses(month, year);
        void alice_deposit(const int month, const int year);
        {
            if (month == 12) {
                Alice.account * 1.1;
            }
        }

        bob_salary(month, year);
        bob_expenses(month, year);
        void bob_deposit(const int month, const int year);
        {
            if (month == 12) {
                Bob.account * 1.1;
            }
        }


        month++;

        if (month == 13) {
            year++;
            month = 1;
        }
    }
}



void result()
{
    if (Alice.account > Bob.account) {
        printf("Alice is richer on %lld\n", Alice.account - Bob.account);
    }
    else {
        printf("Bob is richer on %lld\n", Bob.account - Alice.account);
    }
}


int main()
{
    simulation();
    result();
    return 0;
}
