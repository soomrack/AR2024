#include<stdio.h>

typedef long long int Money;


struct Person {
    Money salary;
    Money account;
};


struct Person alice;


void alice_init()
{
    alice.account = 1000 * 1000;
    alice.salary = 200 * 1000;
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
        // alice_mortgage();
        // alice_food();
        // alice_expences();
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
