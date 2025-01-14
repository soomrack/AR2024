#include<stdio.h>

typedef long long int Money;  // Rub

struct Cat{
    Money eda;
    int is_alive;
};


struct Ipoteka {
    double rate;
    Money credit;
    Money platez;
    Money month_pay;
};


struct Bank_deposit{
    double rate;
    Money deposit_account;
};


struct Person{
    Money salary;
    Money account;
    Money flat;
    Money expenses;
    struct Ipoteka ipoteka;
    struct Bank_deposit deposit;
    struct Cat cat;
};


struct Person bob;
struct Person alice;


// Alice
void alice_salary(const int month, const int year)
{
    if (month == 1){
        alice.salary *= 1.09;
    }
    alice.account += alice.salary;
    if (month == 9){
        alice.account += alice.salary * 0.5;
    }
}


void alice_ipoteka()
{
    alice.account -= alice.ipoteka.month_pay;
}


void alice_expenses(const int month)
{
    if (month == 1) {
        alice.expenses *= 1.09;
    }
    alice.account -= alice.expenses;
}


void alice_flat(const int month)
{
    if (month == 1){
        alice.flat *= 1.09;
    }
}


void alice_init()
{
    alice.account = 1300 * 1000;
    alice.salary = 300000;
    alice.expenses = 50 * 1000;

    alice.ipoteka.platez = 1300000;
    alice.ipoteka.credit = 13000 * 1000;
    alice.ipoteka.rate = 0.14;
    alice.ipoteka.month_pay = 138630;
    alice.account -= alice.ipoteka.platez;
    alice.flat = 13000000;
    alice.cat.eda = 4000;
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
        alice.cat.eda *= 1.09;
    }
    if (alice.cat.is_alive == 1){
        alice.account -= alice.cat.eda;
    }
}



void alice_print()
{
    printf("Alice account = %lld \n", alice.flat + alice.account);
}




// Bob
void bob_salary(const int month, const int year)
{
    bob.account += bob.salary;
    if (month == 1) {
        bob.salary *= 1.09;
    }
}


void bob_expenses(const int month, const int year)
{
    bob.account -= bob.expenses;
    if (month == 1){
        bob.expenses *= 1.09;
    }
}


void bob_flat (const int month, const int year)
{
    bob.account -= bob.expenses;
    if (month == 1){
        bob.flat *= 1.09;
    }
}


void bob_bank(const int month, const int year)
{
    bob.deposit.deposit_account *= ((bob.deposit.rate / 12) + 1);
    bob.deposit.deposit_account += bob.account;
    bob.account = 0;
}



void bob_init(){
    bob.salary = 300000;
    bob.deposit.deposit_account = 1300000;
    bob.flat = 30000;
    bob.expenses = 50000;
    bob.deposit.rate = 0.20;
}


void bob_print()
{
    printf("Bob account = %lld \n", bob.deposit.deposit_account);
}


void simulation()
{
    int month = 1;
    int year = 2024;

    while( !((month == 9) && (year == 2024 + 30))){

        alice_salary(month, year);
        alice_ipoteka();
        alice_expenses(month);
        alice_flat(month);
        alice_cat(month, year);
        bob_salary(month, year);
        bob_expenses(month,year);
        bob_flat(month,year);
        bob_bank(month,year);
        
            

        month++;
        if (month == 13) {
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

