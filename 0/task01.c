#include<stdio.h>

typedef long long int Money;  // RUR


struct Cat{
    Money food;
    int is_alive;
};


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
    struct Mortgage mortgage;
    struct Cat cat;
};


struct Person alice;  // mortgage
struct Person bob;

void alice_mortgage()
{
    alice.account -= alice.mortgage.month_pay;
    
}

void alice_food(const int month)
{
    if (month == 1) {
        alice.food *= 1.1;
    }
    alice.account -= alice.food;
}

void alice_expences(const int month ){
    if (month == 1) {
        alice.account -= 5000;
    }
    alice.account -= alice.expences;
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
    alice.mortgage.month_pay = 100 * 1000;  //
    alice.account -= alice.mortgage.platez;

    alice.cat.food = 5000;
    alice.cat.is_alive = 0;
}


void alice_cat(const int month, const int year)
{
    if ((month == 12) && (year==2026)) {
        alice.account -= 30000;
        alice.cat.is_alive = 1;
    }
    if ((year == 2043) && (month == 3)) {
        alice.cat.is_alive = 0;
        alice.account -= 3000;
    }
    if (month == 1){
        alice.cat.food *= 1.1;
    }
    if (alice.cat.is_alive == 1){
        alice.account -= alice.cat.food ;
    }
}


void alice_print()
{
    printf("Alice account = %lld \n", alice.account);
}


void alice_salary(const int month, const int year)
{
    if(month == 12) {
        alice.account += alice.salary;
    }
    if(month == 1) {
        alice.salary *= 1.07;
    }
    alice.account += alice.salary;    
}




void simulation()
{
    int month = 9;
    int year = 2024;

    while( !((month == 9) && (year == 2024 + 30)) ) {

        alice_salary(month, year);
        alice_mortgage();
        alice_food(month);
        alice_expences(month );  // одежда, личные вещи
        alice_cat(month, year);
        // alice_car();
        // alice_vacation();

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

    simulation();

    alice_print();
    return 1;
}
