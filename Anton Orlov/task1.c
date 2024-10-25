#include<stdio.h>

typedef long long int Money; //RUB


struct Person {
    Money salary;
    Money account;
    Money food;
    Money expence;
    Money rent;
    Money house;
    Money deposit;
    double deposit_procent;
};

struct Mortgage {
    double procent;
    Money summa_credita;
    Money platez_month;
    Money first_platez;
    int years;
};


struct Person alice;
struct Mortgage alice_mortgage;
struct Person bob;


void alice_init()
{
    alice.salary = 310000;
    alice.account = 1000000;
    alice.food = 30000;
    alice.expence = 25000;
    alice.house = 14000000;
    
    
    alice_mortgage.summa_credita = 14000000;
    alice_mortgage.first_platez = 100000;
    alice_mortgage.procent = 9;
    alice_mortgage.years = 30;
    alice_mortgage.platez_month = 112000;
    
    alice.deposit = 0;
    alice.deposit_procent = 1.005;
    
    alice.account -= alice_mortgage.first_platez;
}

void alice_salary(const int month)
{
    if (month == 1) {
        alice.salary *= 1.07;
    }
    alice.account += alice.salary;
}

void alice_food(const int month)
{
    if (month == 1) {
        alice.food *= 1.07;
    }
    alice.account -= alice.food;
}

void alice_expence(const int month)
{
    if (month == 1) {
        alice.account -= 10000;
    }
    alice.account -= alice.expence;
}

void alice__mortgage()
{
    alice.account -= alice_mortgage.platez_month;
}

void alice_house(const int month)
{
    if (month == 1) {
        alice.house *= 1.07;
    }
}

void alice_deposite()
{
    alice.deposit += alice.account;
    alice.account = 0;
    alice.deposit *= alice.deposit_procent;
}


void bob_init()
{
    bob.salary = 310000;
    bob.account = 1000000;
    bob.food = 30000;
    bob.expence = 25000;
    bob.rent = 30000;

    bob.deposit = bob.account;
    bob.deposit_procent = 1.005;
}

void bob_salary(const int month)
{
    if (month == 1) {
        bob.salary *= 1.07;
    }
    bob.account += bob.salary;
}

void bob_food(const int month)
{
    if (month == 1) {
        bob.food *= 1.07;
    }
    bob.account -= bob.food;
}

void bob_expence(const int month)
{
    if (month == 1) {
        bob.account -= 10000;
    }
    bob.account -= bob.expence;
}

void bob_rent(const int month)
{
    if (month == 1) {
        bob.rent *= 1.07;
    }
    bob.account -= bob.rent;
}

void bob_deposite()
{
    bob.deposit += bob.account;
    bob.account = 0;
    bob.deposit *= bob.deposit_procent;
}


void simulation()
{
    int month = 9;
    int year = 2024;
    while (!((month == 9) && (year == 2024 + 30)))
    {
        alice_salary(month);
        alice_food(month);
        alice_expence(month);
        alice_house(month);
        alice__mortgage();
        alice_deposite();
        
        bob_salary(month);
        bob_food(month);
        bob_expence(month);
        bob_rent(month);
        bob_deposite();

        month += 1;
        if (month == 13) {
            month = 1;
            year += 1;
        }
    }
}


void alice_print()
{
    printf("Alice account = %lld \n", alice.account += (alice.house + alice.deposit));
}

void bob_print()
{
    printf("Bob account = %lld \n", bob.account += bob.deposit);
}


int main()
{
    alice_init();
    bob_init();
    
    simulation();
    
    alice_print();
    bob_print();
    
    return 1;
}
