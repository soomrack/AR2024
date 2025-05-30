#include<stdio.h>

typedef long long int Money;


struct Mortgage {
    double rate;
    Money credit;
    Money payment;
    Money month_pay;
};

struct Bank_deposit{
    double rate;
    Money deposit_account;
    Money month_add;

};

struct Person{
    Money salary;
    Money account;
    Money flat;
    Money expenses;

    struct Mortgage mortgage;
    struct Bank_deposit deposit;
};

struct Person Bob;
struct Person Alice;


void alice_salary(const int month, const int year){
    if (month == 1){
        Alice.salary *=1.07;
    }
    Alice.account += Alice.salary;
}

void alice_mortgage(){
    Alice.account -= Alice.mortgage.month_pay;
}

void alice_expenses(const int month ){
    if (month == 1) {
        Alice.expenses *= 1.1;
    }
    Alice.account -= Alice.expenses;
}

void alice_flat(const int month){
    if (month == 1){
        Alice.flat *= 1.05;
    }
}

void alice_init()
{
    Alice.account = 1000 * 1000;
    Alice.salary = 200000;
    Alice.expenses = 50 * 1000;

    Alice.mortgage.payment = 1000000;
    Alice.mortgage.credit = 10000 * 1000;
    Alice.mortgage.rate = 0.19;
    Alice.mortgage.month_pay = 150000;
    Alice.account -= Alice.mortgage.payment;
    Alice.flat = 10000000;
}


void alice_print()
{
    printf("Alice account = %lld \n", Alice.flat + Alice.account);
}


void bob_salary(const int month, const int year){
    
    if (month == 1){
        Bob.salary*=1.07;
    }
}


void bob_expenses(const int month, const int year){

    if (month == 1){
        Bob.expenses*=1.09;
    }
}

void bob_flat(const int month, const int year){
    if (month == 1){
        Bob.flat*=1.09;
    }
}

void bob_bank(const int month, const int year){
    Bob.deposit.deposit_account *= ((Bob.deposit.rate/12) + 1);
    Bob.deposit.month_add = Bob.salary - Bob.flat - Bob.expenses;
    Bob.deposit.deposit_account += Bob.deposit.month_add;
}

void bob_init(){
    Bob.salary = 200000;
    Bob.deposit.deposit_account= 1000000;
    Bob.flat = 100000;
    Bob.expenses = 50000;
    Bob.deposit.rate = 0.20;

}

void bob_print()
{
    printf("Bob account = %lld \n", Bob.deposit.deposit_account);
}

void simulation()
{
    int month = 1;
    int year = 2024;

    while( !((month==1) && (year == 2024+30 ))){

            alice_salary(month, year);
            alice_mortgage();
            alice_expenses(month);
            alice_flat(month);

            bob_salary(month, year);
            bob_expenses(month,year);
            bob_flat(month,year);
            bob_bank(month,year);

        month++;
        if (month == 13){
            month = 1;
            year++;
        }
    }


}


int main(){
    alice_init();
    bob_init();
    simulation();

    alice_print();
    bob_print();
    return 1;
}