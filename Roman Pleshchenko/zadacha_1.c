#include <stdio.h>
typedef long long int Money;
struct Person  {
    Money house;
    Money capital;
    Money bank_deposit;
    Money credit;
    Money salary;
    Money expenses;
    Money bank;
};
struct Person Alice =
    {
    .capital = 14* 1000 * 1000,
    .credit = 185337,
    .salary = 300 * 1000,
    .expenses = 60 * 1000
};

struct Person Bob =
    {
    .capital = 1000*1000,
    .salary = 300*1000,
    .expenses = 95 * 1000,
    .bank = 1000*1000
};

void alice_credit() {
    Alice.capital = Alice.capital - Alice.credit;
}


void alice_expenses() {
    Alice.capital= Alice.capital - Alice.expenses;
}


void alice_salary() {
    Alice.capital = Alice.capital + Alice.salary;
}


void bob_deposit() {

    Bob.capital = Bob.capital + Bob.bank*((20/12) * 0.01);
    Bob.bank = Bob.bank * ((20/12) * 0.01+1);
}


void bob_expenses() {
    Bob.capital= Bob.capital - Bob.expenses;
}


void bob_salary() {
    Bob.capital = Bob.capital + Bob.salary;
}


void infl()
{
    Alice.expenses = Alice.expenses * 1.07;
    Bob.expenses = Bob.expenses * 1.07;
    Alice.salary = Alice.salary * 1.07;
    Bob.salary = Bob.salary * 1,07;
}

void print() {
    if (Bob.capital>Alice.capital){
        printf("Bob richer  = %lld \n ", Bob.capital - Alice.capital);
    }
    if (Bob.capital < Alice.capital){
        printf("Alice richer =  %lld \n ", Alice.capital - Bob.capital);
    }
    if (Bob.capital == Alice.capital){
        printf("Bob and Alice have the same capital");
    }
}

void simulation()
{
    int month = 9;
    int year = 2024;
    while ( !((month == 10) && (year == 2054)) ) {
        bob_salary();
        alice_salary();
        bob_expenses();
        alice_expenses();
        alice_credit();
        bob_deposit();

        month++;
        if (month == 13) {
            month = 1;
            year++;
            //infl();
        }






    }
}


int main() {
    simulation();
    print();
    return 0;




}
