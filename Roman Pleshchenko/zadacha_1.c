#include <stdio.h>
typedef long long int Money;
struct Person
{
    Money house;
    Money capital;
    Money credit;
    Money salary;
    Money expenses;
    Money bank;

};
struct Deposite
{
    Money deposite_account;
    double deposite_procent;
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
};

struct Deposite Bob_dep =
    {
    .deposite_account = 1000*1000,
    .deposite_procent = 1.1
    };

struct Deposite Alice_dep =
    {
    .deposite_account = 0,
    .deposite_procent = 1.1
    };

void alice_deposite(const int month)
{
    if (month ==1) {
        Alice.capital = Alice_dep.deposite_account * Alice_dep.deposite_procent - Alice_dep.deposite_procent;
        Alice_dep.deposite_account = Alice_dep.deposite_account * Alice_dep.deposite_procent;
    }
}


void bob_deposite(const int month)
{
    if (month ==1) {
        Bob.capital = Bob_dep.deposite_account * Bob_dep.deposite_procent - Bob_dep.deposite_procent;
        Bob_dep.deposite_account = Bob_dep.deposite_account * Bob_dep.deposite_procent;

    }
}


void alice_expenses(const int month)
{
    if (month == 1){
        Alice.expenses = Alice.expenses * 1.07;

    }
    Alice.capital= Alice.capital - Alice.expenses;
    Alice_dep.deposite_account = Alice_dep.deposite_account - Alice.expenses;
}


void alice_salary(const int month)
{
    if (month == 1){
        Alice.salary = Alice.salary * 1.07;

    }
    Alice.capital = Alice.capital + Alice.salary;
    Alice_dep.deposite_account = Alice_dep.deposite_account + Alice.salary;
}


void alice_credit()
{

    Alice.capital = Alice.capital - Alice.credit;
    Alice_dep.deposite_account = Alice_dep.deposite_account - Alice.credit;


}


void bob_expenses(const int month)
{
    if (month == 1){
        Bob.expenses = Bob.expenses * 1.07;

    }
    Bob.capital= Bob.capital - Bob.expenses;
}


void bob_salary(const int month)
{
    if (month == 1){
        Bob.salary = Bob.salary * 1.07;

    }
    Bob.capital = Bob.capital + Bob.salary;
}


void print()
{
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
        bob_salary(month);
        alice_salary(month);
        bob_expenses(month);
        alice_expenses(month);
        alice_credit();
        alice_deposite(month);
        bob_deposite(month);
        month++;
        if (month == 13) {
            month = 1;
            year++;
        }






    }
}


int main() {
    simulation();
    print();
    return 0;




}
