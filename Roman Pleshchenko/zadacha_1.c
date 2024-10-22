#include <stdio.h>
typedef long long int Money; //Rub
typedef int time; // год жизни


struct Person {
    Money house;
    Money account;
    Money month_credit;
    Money salary;
    Money expenses;

};


struct Cat {
    Money cat_expenses;
    time cat_life;

};


struct Deposite {
    Money deposite_account;
    double deposite_procent;
};


struct Person Alice = {
    .account = 0,
    .month_credit = 185337,
    .salary = 300 * 1000,
    .expenses = 60 * 1000
};


struct Cat Alice_cat = {
    .cat_expenses = 5000,
    .cat_life = 0


};
struct Person Bob = {
    .account = 0,
    .salary = 300 * 1000,
    .expenses = 95 * 1000,
};


struct Deposite Bob_dep = {
    .deposite_account = 1000*1000,
    .deposite_procent = 1.016
    };


struct Deposite Alice_dep = {
    .deposite_account = 0,
    .deposite_procent = 1.016
    };


void alice_deposite()
{
    Alice_dep.deposite_account = Alice_dep.deposite_account * Alice_dep.deposite_procent;

    Alice_dep.deposite_account += Alice.account;
    Alice.account = 0;
}


void bob_deposite()
{
    Bob_dep.deposite_account = Bob_dep.deposite_account * Bob_dep.deposite_procent;

    Bob_dep.deposite_account += Bob.account;
    Bob.account = 0;
}


void alice_expenses(const int month)
{
    if (month == 1){
        Alice.expenses = Alice.expenses * 1.07;

    }
    Alice.account -= Alice.expenses;
}


void alice_salary(const int month)
{
    if (month == 1){
        Alice.salary = Alice.salary * 1.07;

    }
    Alice.account += Alice.salary;
}


void alice_credit()
{

    Alice.account -= Alice.month_credit;
}


void alice_house(const int month)
{
    if (month == 1) {
        Alice.house *= 1.07;
    }

}


void alice_cat(const int month) {
    if (Alice_cat.cat_life < 15){ // когда коту исполняется 15 лет, он умирает
        if (month ==1) {
            Alice_cat.cat_expenses *= 1,07;
        }
        Alice.account -= Alice_cat.cat_expenses;
        if (month == 5 ) {      //у кота в мае День Рождения
            Alice_cat.cat_life += 1;
        }
        Alice.account -= Alice_cat.cat_expenses;
    }
}

void bob_expenses(const int month)
{
    if (month == 1){
        Bob.expenses = Bob.expenses * 1.07;

    }
    Bob.account -= Bob.expenses;
}


void bob_salary(const int month)
{
    if (month == 1){
        Bob.salary = Bob.salary * 1.07;

    }
    Bob.account -= Bob.salary;
}


void print()
{
    if (Bob_dep.deposite_account > Alice_dep.deposite_account + Alice.house){
        printf("Bob richer  = %lld \n ", Bob_dep.deposite_account - (Alice_dep.deposite_account + Alice.house));
    }
    if (Bob_dep.deposite_account < Alice.house + Alice_dep.deposite_account){
        printf("Alice richer =  %lld \n ", Alice.house + Alice_dep.deposite_account - Bob_dep.deposite_account);
    }
    if (Bob_dep.deposite_account == Alice.house + Alice_dep.deposite_account){
        printf("Bob and Alice have the same capital");
    }
}


void simulation()
{
    int month = 9;
    int year = 2024;
    while ( !((month == 10) && (year == 2054)) ) {
        //Bob
        bob_salary(month);
        bob_expenses(month);
        bob_deposite();

        //Alice
        alice_salary(month);
        alice_expenses(month);
        alice_credit();
        alice_cat(month);
        alice_deposite();
        alice_house(month);

        month++;
        if (month == 13) {
            month = 1;
            year++;
        }

    }
}


int main()
{
    simulation();
    print();
    return 0;
}
