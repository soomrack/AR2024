#include <stdio.h>

typedef long long Money;
int month = 9;
int year = 2024;

struct Person {
    Money salary;
    Money money_for_living;
    Money spendings;
    Money mortgage;
    Money account;
    Money house;
    Money house_rent;
};

struct Person Alice = {300 * 1000, 100 * 1000, 0, 180 * 1000, 0, 14000 * 1000, 400 * 100};
struct Person Bob = {300 * 1000, 100 * 1000, 0, 180 * 1000, 0, 14000 * 1000, 400 * 100};

void bob_salary(const int month, const int year) {
    if (month == 12) {
        Bob.salary *= 1.07;
    }
    Bob.account += Bob.salary;
}

void bob_spendings(const int month, const int year) {
    if (month == 12) {
        Bob.money_for_living *= 1.08;
        Bob.house_rent *= 1.08;
    }
    Bob.spendings = Bob.money_for_living + Bob.house_rent;
    Bob.account -= Bob.spendings;
}

void alice_salary(const int month, const int year) {
    static Money better_salary = Alice.salary * 1.5;
    if (month == 12) {
        Alice.salary *= 1.07;
        Alice.house *= 1.08;
    }
    Alice.account += Alice.salary;
    if (month == 9 && year == 2054) {
        Alice.account += Alice.house;
    }
    if ( year == 2028 && month == 3 ) {
        Alice.salary = 0;
    }
    if ( year == 2028 && month == 4 ) {
        Alice.salary = 0;
    }
    if ( year == 2028 && month == 5 ) {
        Alice.salary = better_salary;
    }
}

void alice_spendings(const int month, const int year) {
    if (month == 12) {
        Alice.money_for_living *= 1.08;
    }
    Alice.spendings = Alice.money_for_living + Alice.mortgage;
    Alice.account -= Alice.spendings;
}

void simulation() {
    while (!(year == 2054 && month == 10)) {
        alice_salary(month, year);
        alice_spendings(month, year);
        bob_salary(month, year);
        bob_spendings(month, year);
        month++;
        if (month == 13) {
            year = year + 1;
            month = 1;
        }
    }
}

void result() {
    if (Alice.account > Bob.account) {
        printf("\nAlice is richer on: %lld", Alice.account - Bob.account);
    } else {
        printf("\nBob is richer on: %lld", Bob.account - Alice.account);
    }
}

int main() {
    simulation();
    result();
    return 0;
}

