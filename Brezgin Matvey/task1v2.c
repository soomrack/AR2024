#include<stdio.h>

typedef long long int Money;  // Rub


struct Mortgage {
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
    Money kvartira;
    Money expenses;
    Money vacation;
    Money ostatok;
    struct Mortgage mortgage;
    struct Bank_deposit deposit;
};


struct Person bob;
struct Person alice;


// Alice
void alice_salary(const int month, const int year)
{
    if (month == 1){
        alice.salary *=1.07;
    }
    alice.account += alice.salary;
}


void alice_mortgage()
{
    alice.account -= alice.mortgage.month_pay;
}


void alice_expenses(const int month)
{
    if (month == 1) {
        alice.expenses *= 1.1;
    }
    alice.account -= alice.expenses;
}


void alice_kvartira(const int month)
{
    if (month == 1){
        alice.kvartira *= 1.05;
    }
}


void alice_init()
{
    alice.account = 1000 * 1000;
    alice.salary = 200000;
    alice.expenses = 50 * 1000;

    alice.mortgage.platez = 1000000;
    alice.mortgage.credit = 10000 * 1000;
    alice.mortgage.rate = 0.19;
    alice.mortgage.month_pay = 150000;
    alice.account -= alice.mortgage.platez;
    alice.kvartira = 10000000;
}


void alice_print()
{
    printf("Alice account = %lld \n", alice.kvartira + alice.account);
}




// Bob
void bob_salary(const int month, const int year)
{
    
    if (month == 1) {
        bob.salary *= 1.07;
    }
}


void bob_expenses(const int month, const int year)
{

    if (month == 1){
        bob.expenses *= 1.09;
    }
}


void bob_kvartira(const int month, const int year)
{
    if (month == 1){
        bob.kvartira *= 1.09;
    }
}


void bob_ostatok(const int month)
{
    bob.ostatok = bob.salary - bob.expenses - bob.kvartira;
}


void bob_bank(const int month, const int year)
{
    //printf("Bob account = %lld \n", bob.deposit.deposit_account);
    bob.deposit.deposit_account *= ((bob.deposit.rate / 12) + 1);
    bob.deposit.deposit_account += (bob.ostatok / 2);
}


void bob_vacation(const int month) 
{
    bob.vacation += (bob.ostatok / 2);
    if (month == 9) {
        bob.vacation = 0;
    }
}


void bob_init(){
    bob.salary = 200000;
    bob.deposit.deposit_account = 1000000;
    bob.kvartira = 100000;
    bob.expenses = 50000;
    bob.deposit.rate = 0.12;
    bob.vacation = 0;
}


void bob_print()
{
    printf("Bob account = %lld \n", bob.deposit.deposit_account);
}


void simulation()
{
    int month = 1;
    int year = 2024;

    while( !((month == 1) && (year == 2024+30 ))){

            alice_salary(month, year);
            alice_mortgage();
            alice_expenses(month);
            alice_kvartira(month);

            bob_salary(month, year);
            bob_expenses(month,year);
            bob_kvartira(month,year);
            bob_ostatok(month);
            bob_bank(month,year);
            bob_vacation(month);
            

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