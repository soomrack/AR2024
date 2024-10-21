#include<stdio.h>

typedef long long int Money;


struct Mortgage {
    double rate;
    Money credit;
    Money platez;
    Money month_pay;
};


struct Person {
    Money salary;
    Money account;
    Money food;
    Money expences;
    Money flat;
    struct Mortgage mortgage;
};


struct Bank {
    double deposit_rate; // monthly!
    Money bob_account;
    Money alice_account;
    int deposit_rate_elevation;
};


struct Bank bank;
struct Person alice;
struct Person bob;


void alice_mortgage()
{
    alice.account -= alice.mortgage.month_pay;

}


void bob_flat(const int month)
{
    bob.account -= bob.flat;
    if (month == 1) {
        bob.flat *= 1.07;
    }
}


void bob_deposit()
{
    bank.bob_account += bob.account;
    bob.account = 0;
    bank.bob_account *= bank.deposit_rate;
    if (bank.bob_account >= 10000 * 1000 && bank.deposit_rate_elevation < 1) {
        bank.deposit_rate += 0.01;
        bank.deposit_rate_elevation++;
    };
    bob.account += bank.bob_account;
    bank.bob_account = 0;
}


void alice_food(const int month)
{
    if (month == 1) {
        alice.food *= 1.1;
    }
    alice.account -= alice.food;
}


void bob_food(const int month)
{
    if (month == 1) {
        bob.food *= 1.2;
    }
    bob.account -= bob.food;
}


void alice_expences(const int month) {
    if (month == 1) {
        alice.expences *= 1.15;
    }
    alice.account -= alice.expences;
}


void bob_expences(const int month) {
    if (month == 1) {
        bob.expences *= 1.1;
    }
    bob.account -= bob.expences;
}


void alice_init()
{
    alice.account = 1000 * 1000;
    alice.salary = 200 * 1000;
    alice.food = 10 * 1000;
    alice.expences = 70 * 1000;

    alice.mortgage.platez = 1000 * 1000;
    alice.mortgage.credit = 14000 * 1000;
    alice.mortgage.rate = 0.17;
    alice.mortgage.month_pay = 100 * 1000;
    alice.account -= alice.mortgage.platez;
}


void bank_init()
{
    bank.bob_account = 0;
    bank.deposit_rate = 1.2;
    bank.deposit_rate_elevation = 0;
}


void bob_init()
{
    bob.salary = 200 * 1000;
    bob.food = 10 * 1000;
    bob.expences = 70 * 1000;

    bob.flat = 40 * 1000;
}


void alice_print()
{
    printf("Alice account = %lld \n", alice.account);
}


void bob_print()
{
    printf("Bob account = %lld \n", bob.account);
}


void alice_salary(const int month, const int year)
{
    if (month == 1) {
        alice.salary *= 1.07;
    }
    alice.account += alice.salary;
}


void bob_salary(const int month, const int year)
{
    if (month == 1) {
        bob.salary *= 1.07;
    }
    bob.account += bob.salary;
}


void simulation_alice()
{
    int month = 9;
    int year = 2024;

    while (!((month == 9) && (year == 2024 + 30))) {

        alice_salary(month, year);
        alice_mortgage();
        alice_food(month);
        alice_expences(month);

        month++;
        if (month == 13) {
            month = 1;
            year++;
        }
    }
}


void simulation_bob()
{
    int month = 9;
    int year = 2024;

    while (!((month == 9) && (year == 2024 + 30))) {
        bob_salary(month, year);
        bob_flat(month);
        bob_food(month);
        bob_expences(month);
        bob_deposit();

        month++;
        if (month == 13) {
            month = 1;
            year++;
        }
    }
}


int main()
{
    alice_init();
    bob_init();

    simulation_alice();
    simulation_bob();

    bob_print();
    alice_print();
    return 1;
}