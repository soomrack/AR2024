#include <stdio.h>

typedef long long int Money;  // RUR
Money alice_flat_cost = 10 * 1000 * 1000;

struct Cat{
    Money food;
    int is_alive;
};

struct Mortgage{
    double rate;
    Money credit;
    Money platez;
    Money month_pay;
};


struct Deposit{
    double rate;
    Money account;
    Money month_pay;
};


struct Person{
    Money salary;
    Money account;
    Money food;
    Money expences;
    Money rent;
    
    struct Mortgage mortgage;
    struct Cat cat;
    struct Deposit deposit;
};


struct Person alice;  // mortgage
struct Person bob; // deposit

void alice_mortgage()
{
    alice.account -= alice.mortgage.month_pay;
}

void alice_food(const int month)
{
    if (month == 1){
        alice.food *= 1.1;
    }
    alice.account -= alice.food;
}

void alice_expences(const int month ){
    alice.account -= alice.expences;
    if (month == 1){
       alice.expences *= 1.1;
    }
}
void alice_salary(const int month)
{
    if(month == 1) {
        alice.salary *= 1.1;
    }
    alice.account += alice.salary;    
}


void alice_cat(const int month, const int year)
{
    if ((month == 12) && (year==2026)) {
        alice.account -= 10000;
        alice.cat.is_alive = 1;
    }
    if ((year == 2041) && (month == 10)) {
        alice.cat.is_alive = 0;
        alice.account -= 5000;
    }
    if (month == 1){
        alice.cat.food *= 1.1;
    }
    if (alice.cat.is_alive == 1){
        alice.account -= alice.cat.food ;
    }
}

void alice_flat_cost_height(const int month)
{
    if (month == 1){
       alice_flat_cost *= 1.1;
    }
}


void alice_init()
{
    alice.account = 1000 * 1000;
    alice.salary = 200 * 1000;
    alice.food = 16 * 1000;
    alice.expences = 30 * 1000;

    alice.mortgage.platez = 1000 * 1000;
    alice.mortgage.credit = 10000 * 1000;
    alice.mortgage.rate = 0.19;
    alice.mortgage.month_pay = 143 * 1000;
    alice.account -= alice.mortgage.platez;

    alice.cat.food = 5000;
    alice.cat.is_alive = 0;
}


void alice_print()
{
    printf("Alice account = %lld \n", alice_flat_cost + alice.account);
}


void bob_deposit()
{
    bob.deposit.account += bob.deposit.account * bob.deposit.rate / 12;
    bob.deposit.account += bob.account;
    bob.account = 0;
}

void bob_rent(const int month)
{
    bob.account -= bob.rent;
    if (month == 1){
       bob.rent *= 1.1;
    }
}

void bob_food(const int month)
{
    if (month == 1){
        bob.food *= 1.1;
    }
    bob.account -= bob.food;
}

void bob_expences(const int month)
{
    bob.account -= bob.expences;
    if (month == 1){
       bob.expences *= 1.1;
    }
}

void bob_salary(const int month, const int year)
{
    if(month == 12) {
        bob.account += bob.salary;
    }
    if(month == 1){
        bob.salary *= 1.1;
    }
    bob.account += bob.salary;    
}

void bob_init()
{
    bob.account == 1000 * 1000;
    bob.salary = 200 * 1000;
    bob.food = 17 * 1000;
    bob.expences = 40 * 1000;

    bob.deposit.account += bob.account;
    bob.account = 0;
    bob.deposit.rate = 0.20;

    bob.rent = 30 * 1000;
}

void bob_print()
{
    printf("Bob account = %lld \n", bob.account + bob.deposit.account);
}


void simulation()
{
    int month = 9;
    int year = 2024;

    while( !((month == 9) && (year == 2024 + 30)) ) {
        alice_flat_cost_height(month);
        alice_salary(month);
        alice_mortgage();
        alice_food(month);
        alice_expences(month);
        alice_cat(month, year);
        
        bob_salary(month, year);
        bob_food(month);
        bob_expences(month);
        bob_deposit();
        

        month++;
        if(month == 13) {
            month = 1;
            year++;
        }
    }
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