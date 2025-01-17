#include <stdio.h>

typedef long long int Money;


struct Deposit {
    Money account;
    double interest; //процент депозита
};


struct Person {
    Money expenditure;// расходы
    Money salary; //зарплата
    Money account;  //деньги на руках
    Money apartment_price; //цена квартиры
    Money rent; // аренда
    Money credit_monthly_payment; //ежемесячный платеж по кредиту
    struct Deposit deposite;
};


long double inflation = 0.09;
int month_counter = 1;
int year_counter = 2024;
int year = 0;

struct Person alice;
struct Person bob;


void alice_init()
{
    alice.deposite.account = 0;
    alice.deposite.interest = 0.2;
    alice.expenditure = 50000;
    alice.salary = 300000; 
    alice.account = 0;
    alice.credit_monthly_payment = 195509;
}


void bob_init()
{
    bob.deposite.account = 1300000;// вклад первый
    bob.deposite.interest = 0.2;
    bob.expenditure = 50000;
    bob.salary = 300000;
    bob.account = 0;
    bob.rent = 30000;
    bob.apartment_price = 13000000;

}


void alice_deposite_counting()
{
    alice.deposite.account += alice.deposite.account * alice.deposite.interest / 12;
    alice.deposite.account += alice.account;
    alice.account = 0;
};


void bob_deposite_counting()
{
    bob.deposite.account += bob.deposite.account * bob.deposite.interest / 12;
    bob.deposite.account += bob.account;
    bob.account = 0;
};


void alice_inflation()
{
    if (year == 1) {
        alice.expenditure += alice.expenditure * inflation; 
        alice.salary += alice.salary * inflation;
    };
};

void bob_inflation()
{
    if (year == 1) {
        bob.expenditure += bob.expenditure * inflation;  
        bob.rent += bob.rent * inflation;
        bob.apartment_price += bob.apartment_price * inflation;
        bob.salary += bob.salary * inflation;
    };

};

  
        
void time_counter() //счет лет
{
    year = 0;

    month_counter++;
    if (month_counter == 13) {
        year_counter++;
        month_counter = 1;
        year = 1;
    };
};



void bob_account()
{
    bob.account = bob.salary - bob.expenditure - bob.rent;
};


void alice_account()
{
    alice.account = alice.salary - alice.expenditure - alice.credit_monthly_payment;
};


void simulation()
{
    while (year_counter != 2054 || month_counter != 9) {

        bob_inflation();
        bob_account();
        bob_deposite_counting();

        alice_inflation();
        alice_account();
        alice_deposite_counting();

        time_counter();
    };
};


void print()
{
    if(bob.deposite.account >= bob.apartment_price){
        printf("Боб накопит на квартиру раньше");
    } else{
        printf("Алиса закроет ипотеку раньше");
    }
};


int main()
{
    alice_init();    
    bob_init();
    
    simulation();

    print();
    return 0;
}