#include <stdio.h>
#include <locale.h>

typedef long long int Money;

int month = 9;
int year = 2024;

struct Person {
    Money salary;
    Money food;
    Money transport;
    Money utilities;
    Money spendings;
    Money mortgage;
    Money account;
    Money house;
    Money house_rent;
    Money deposit;
    double deposit_interest_rate;
};

struct Person Alice;
struct Person Bob;

void init() {
    Alice.salary = 300 * 1000;
    Alice.food = 50 * 1000;
    Alice.transport = 30 * 1000;
    Alice.utilities = 20 * 1000;
    Alice.spendings = 0;
    Alice.mortgage = 180 * 1000;
    Alice.account = 0;
    Alice.house = 14000 * 1000;
    Alice.house_rent = 0;
    Alice.deposit = 0;
    Alice.deposit_interest_rate = 0.05;

    Bob.salary = 300 * 1000;
    Bob.food = 50 * 1000;
    Bob.transport = 30 * 1000;
    Bob.utilities = 20 * 1000;
    Bob.spendings = 0;
    Bob.mortgage = 0;
    Bob.account = 0;
    Bob.house = 0;
    Bob.house_rent = 400 * 100;
    Bob.deposit = 0;
    Bob.deposit_interest_rate = 0.05;
}

void salary_alice(struct Person* person) {
    person->salary = (Money)(person->salary * 1.07);
}

void house_alice(struct Person* person) {
    person->house = (Money)(person->house * 1.08);
}

void food_alice(struct Person* person) {
    person->food = (Money)(person->food * 1.08);
}

void transport_alice(struct Person* person) {
    person->transport = (Money)(person->transport * 1.08);
}

void utilities_alice(struct Person* person) {
    person->utilities = (Money)(person->utilities * 1.08);
}

void annual_expenses_alice(struct Person* person) {
    salary_alice(person);
    house_alice(person);
    food_alice(person);
    transport_alice(person);
    utilities_alice(person);
}

void deposit_interest_alice(struct Person* person) {
    person->deposit += person->deposit * person->deposit_interest_rate / 12;
}

void salary_bob(struct Person* person) {
    person->salary = (Money)(person->salary * 1.07);
}

void house_bob(struct Person* person) {
    person->house = (Money)(person->house * 1.08);
}

void food_bob(struct Person* person) {
    person->food = (Money)(person->food * 1.08);
}

void transport_bob(struct Person* person) {
    person->transport = (Money)(person->transport * 1.08);
}

void utilities_bob(struct Person* person) {
    person->utilities = (Money)(person->utilities * 1.08);
}

void annual_expenses_bob(struct Person* person) {
    salary_bob(person);
    house_bob(person);
    food_bob(person);
    transport_bob(person);
    utilities_bob(person);
}

void deposit_interest_bob(struct Person* person) {
    person->deposit += person->deposit * person->deposit_interest_rate / 12;
}

void simulation() {
    while (!(year == 2054 && month == 10)) {

        if (year == 2026 && month == 3) {
            Alice.food *= 2;
            Bob.food *= 2;

        }

        if (month == 12) {
            annual_expenses_alice(&Alice);
            annual_expenses_bob(&Bob);
        }


        Alice.account += Alice.salary;
        Alice.spendings = Alice.food + Alice.transport + Alice.utilities + Alice.mortgage;
        Alice.account -= Alice.spendings;

        if (Alice.account > 0) {
            Alice.deposit += Alice.account;
            Alice.account = 0;
        }

        deposit_interest_alice(&Alice);


        Bob.account += Bob.salary;
        Bob.spendings = Bob.food + Bob.transport + Bob.utilities + Bob.house_rent;
        Bob.account -= Bob.spendings;

        if (Bob.account > 0) {
            Bob.deposit += Bob.account;
            Bob.account = 0;
        }

        deposit_interest_bob(&Bob);


        month++;
        if (month == 13) {
            month = 1;
            year++;
        }
    }
}

void result() {
    Money Alice_total = Alice.account + Alice.deposit;
    Money Bob_total = Bob.account + Bob.deposit;

    if (Alice_total > Bob_total) {
        printf("\nАлиса богаче на: %lld рублей\n", Alice_total - Bob_total);
    }
    else {
        printf("\nБоб богаче на: %lld рублей\n", Bob_total - Alice_total);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    init();
    simulation();
    result();
    return 0;
}
