#include <stdio.h>

typedef long long Money;  // RUB
int MONTH = 9;
int YEAR = 2024;

struct Person {
    Money salary;
    Money for_living;
    Money account;
    Money house;
    Money house_rent;
    Money expenses;
    Money mortgage;
    double rate = 1.1;
};

struct Person Alice, Bob;

void alice_init() {
    Alice.salary = 300 * 1000;
    Alice.for_living = 100 * 1000;
    Alice.account = 0;
    Alice.house = 14000 * 1000;
    Alice.house_rent = 0;
    Alice.expenses = 0;
    Alice.mortgage = 150 * 1000;
}

void bob_init() {
    Bob.salary = 300 * 1000;
    Bob.for_living = 100 * 1000;
    Bob.account = 0;
    Bob.house_rent = 40 * 1000;
    Bob.expenses = 0;
    Bob.mortgage = 0;
}

void alice_house(const int MONTH, const int YEAR) {
    if (MONTH == 12) {
        Alice.house *= 1.08;
    }
    if (MONTH == 9 && YEAR == 2024 + 30) {
        Alice.account += Alice.house;
    }
}

void alice_salary(const int MONTH, const int YEAR) {
    if (MONTH == 12) {
        Alice.salary *= 1.06;
    }

    Alice.account += Alice.salary;
}

void alice_expenses(const int MONTH, const int YEAR) {
    if (MONTH == 12) {
        Alice.for_living *= 1.08;
    }

    Alice.expenses = Alice.for_living + Alice.mortgage;
    Alice.account -= Alice.expenses;
}

void alice_deposit(const int MONTH, const int YEAR) {
    if (MONTH == 12) {
        Alice.account *= Alice.rate;
    }
}

void bob_salary(const int MONTH, const int YEAR) {
    if (MONTH == 12) {
        Bob.salary *= 1.06;
    }

    Bob.account += Bob.salary;
}

void bob_expenses(const int MONTH, const int YEAR) {
    if (MONTH == 12) {
        Bob.for_living *= 1.08;
        Bob.house_rent *= 1.08;
    }

    Bob.expenses = Bob.for_living + Bob.house_rent;
    Bob.account -= Bob.expenses;
}

void bob_deposit(const int MONTH, const int YEAR) {
    if (MONTH == 12) {
        Bob.account *= Bob.rate;
    }
}

void simulation() {
    while (!(YEAR == 2024 + 30 && MONTH == 10)) {
        alice_house(MONTH, YEAR);
        alice_salary(MONTH, YEAR);
        alice_expenses(MONTH, YEAR);
        alice_deposit(MONTH, YEAR);

        bob_salary(MONTH, YEAR);
        bob_expenses(MONTH, YEAR);
        bob_deposit(MONTH, YEAR);

        MONTH++;

        if (MONTH == 13) {
            YEAR++;
            MONTH = 1;
        }
    }
}

void print_result() {
    if (Alice.account > Bob.account) {
        printf("Alice is richer on %lld\n", Alice.account - Bob.account);
    }
    else {
        printf("Bob is richer on %lld\n", Bob.account - Alice.account);
    }
}

int main() {
    alice_init();
    bob_init();
    simulation();
    print_result();
    return 0;
}
