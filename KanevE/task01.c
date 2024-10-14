#include<stdio.h>

typedef long long int Money;  // RUB


struct Pet{
    Money food;
    int is_alive;
};


struct Mortgage {
    double rate;
    Money credit;
    Money platez;
    Money month_pay;
    Money property_cost; //lets see how much it costs after buying
};



struct Person {
    Money salary;
    Money account;
    Money food;
    Money expences;
    struct Mortgage mortgage;
    struct Pet pet;
};


struct Person alice;  // mortgage
struct Person bob;

void alice_mortgage(const int month)
{
    alice.account -= alice.mortgage.month_pay;
    alice.mortgage.credit *= (1 + alice.mortgage.rate/12); //difficult procent tipa
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
        bob.food *= 1.1;
    }
    bob.account -= bob.food;
}

void alice_expences(const int month ){
    if (month == 1) {
        alice.account -= 5000;
    }
    alice.account -= alice.expences;
}

void bob_expences(const int month ){
    if (month == 1) {
        bob.account -= 5000;
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
    alice.mortgage.property_cost = alice.mortgage.credit;
    alice.mortgage.rate = 0.17;
    alice.mortgage.month_pay = 100 * 1000;  //ohrenetb

    alice.account -= alice.mortgage.platez;

    alice.pet.food = 5000;
    alice.pet.is_alive = 0;
}

void bob_init()
{
    bob.account = 1000 * 1000;
    bob.salary = 200 * 1000;
    bob.food = 10 * 1000;
    bob.expences = 70 * 1000;

    bob.mortgage.platez = 25000;
    bob.mortgage.credit = 0;
    bob.mortgage.rate = 0.10;
    bob.mortgage.month_pay = 25000;  //
    bob.account -= bob.mortgage.platez;

    bob.pet.food = 5000;
    bob.pet.is_alive = 0;
}

void alice_cat(const int month, const int year)
{
    if ((month == 12) && (year==2026)) {
        alice.account -= 30000;
        alice.pet.is_alive = 1;
    }
    if ((year == 2043) && (month == 3)) {
        alice.pet.is_alive = 0;
        alice.account -= 30; //пакетик полиэтиленовый для сбитого кота 
    }
    if (month == 1){
        alice.pet.food *= 1.1;
    }
    if (alice.pet.is_alive == 1){
        alice.account -= alice.pet.food ;
    }
}

void bob_dog(const int month, const int year)
{
    if ((month == 12) && (year==2025)) {
        bob.account -= 50000;
        bob.pet.is_alive = 1;
    }
    if ((year == 2030) && (month == 12))  { //HAPPY NEW YEAR ^_^
        bob.pet.is_alive = 0;
        bob.account -= 3000;
    }
    if (month == 1) {
        bob.pet.food *= 1.25;
    }
    if (bob.pet.is_alive == 1){
        bob.account -= bob.pet.food;
    }
}


void alice_print()
{
    printf("Alice account = %lld \n", alice.account + alice.mortgage.property_cost);
}

void bob_print()
{
    printf("Bob account = %lld \n", bob.account);
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

void bob_salary(const int month, const int year)
{
    if(month == 12) {
        bob.account += bob.salary;
    }
    if(month == 1) {
        bob.salary *= 1.07;
        bob.mortgage.month_pay *= 1.10;
    }
    bob.account += bob.salary;   
}



void simulation()
{
    int month = 10;
    int year = 2024;

    while( !((month == 10) && (year == 2024 + 30)) ) {

        alice_salary(month, year);
        alice_mortgage(month);
        alice_food(month);
        alice_expences(month );  // одежда, личные вещи
        alice_cat(month, year);
        // alice_car();
        // alice_vacation();
        bob_salary(month, year);
        bob_mortgage(month);
        bob_food(month);
        bob_expences(month);  // одежда, личные вещи
        bob_dog(month, year);
        // bob_car();
        // bob_vacation();
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
