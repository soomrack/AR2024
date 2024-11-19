#include<stdio.h>

typedef long long Money;

struct Pet{
    Money food;
    int is_alive;
};

struct Mortgage {
    int rate;
    Money credit;
    Money payment; 
    Money month_pay;
    Money property_cost;
};

struct Person {
    Money account;
    Money salary;
    Money food;
    Money expences;
    struct Mortgage mortgage;
    struct Pet pet;
};

struct Person alice;
struct Person bob;

void alice_init(){
    alice.salary = 200 * 1000;
    alice.account = 1000 * 1000;
    alice.food = 10 * 1000;
    alice.expences = 70 * 1000;

    alice.mortgage.credit = 14000 * 1000;
    alice.mortgage.payment = 1000 * 1000;
    alice.mortgage.property_cost = alice.mortgage.credit;
    alice.mortgage.rate = 0.17;
    alice.mortgage.month_pay = 100 * 1000;

    alice.account -= alice.mortgage.payment;

    alice.pet.food = 5000;
    alice.pet.is_alive = 0;
}

void bob_init()
{
    bob.account = 1000 * 1000;
    bob.salary = 200 * 1000;
    bob.food = 10 * 1000;
    bob.expences = 70 * 1000;

    bob.mortgage.credit = 0;
    bob.mortgage.rate = 0.10;
    bob.mortgage.month_pay = 25 * 1000;

    bob.pet.food = 5000;
    bob.pet.is_alive = 0;
}

void alice_mortgage(const int month)
{
    alice.account -= alice.mortgage.month_pay;
    alice.mortgage.credit *= (1 + alice.mortgage.rate/12);
    if (month == 12) {
        alice.mortgage.property_cost += alice.mortgage.property_cost*0.13;
        alice.mortgage.credit *= (1 + alice.mortgage.rate);
    }

}

void bob_mortgage(const int month)
{
    bob.account -= bob.mortgage.month_pay;
    if (month == 12) {
        bob.mortgage.month_pay *= 1.10;
    }

}

void alice_salary(const int month, const int year){
     if(month == 12) {
        alice.account += alice.salary;
    }
    if(month == 1) {
        alice.salary *= 1.03;
    }
    alice.account += alice.salary;
}

void bob_salary(const int month, const int year)
{
    if(month == 12) {
        bob.account += bob.salary;
    }
    if(month == 1) {
        bob.salary *= 1.03;
        bob.mortgage.month_pay *= 1.01;
    }
    bob.account += bob.salary;   
}

void alice_food(const int month){
    if (month == 1) {
        alice.food *= 1.05;
    }
    alice.account -= alice.food;
}

void bob_food(const int month)
{
    if (month == 1) {
        bob.food *= 1.05;
    }
    bob.account -= bob.food;
}

void alice_expences(const int month ){
    if (month == 1) {
        alice.account -= 10000;
    }
    alice.account -= alice.expences;
}

void bob_expences(const int month ){
    if (month == 1) {
        bob.account -= 10000;
    }
    bob.account -= bob.expences;
}

void alice_cat(const int month, const int year)
{
    if ((month == 7) && (year==2028)) {
        alice.account -= 5000;
        alice.pet.is_alive = 1;
    }
    if ((year == 2041) && (month == 5)) {
        alice.pet.is_alive = 0; 
    }
    if (month == 1){
        alice.pet.food *= 1.05;
    }
    if (alice.pet.is_alive == 1){
        alice.account -= alice.pet.food ;
    }
}

void bob_cat(const int month, const int year)
{
    if ((month == 12) && (year==2025)) {
        bob.account -= 50000;
        bob.pet.is_alive = 1;
    }
    if ((year == 2034) && (month == 12))  {
        bob.pet.is_alive = 0;
    }
    if (month == 1) {
        bob.pet.food *= 1.05;
    }
    if (bob.pet.is_alive == 1){
        bob.account -= bob.pet.food;
    }
}

void calendar(){
    int month = 11;
    int year = 2024;

    while (!((month == 11) && (year == 2054))) {
        alice_salary(month, year);
        alice_food(month);
        alice_expences(month);
        alice_mortgage(month);
        alice_cat(month, year);

        bob_salary(month, year);
        bob_mortgage(month);
        bob_food(month);
        bob_expences(month);
        bob_cat(month, year);
        month++;
        if(month == 13) {
            month = 1;
            year++;
        }
    }
}

void alice_print(){
    printf("Alice account = %lld \n", alice.account);
}

void bob_print()
{
    printf("Bob account = %lld \n", bob.account);
}

int main (){
    alice_init();
    bob_init();
    calendar();
    alice_print();
    bob_print();
    return 1;
}
