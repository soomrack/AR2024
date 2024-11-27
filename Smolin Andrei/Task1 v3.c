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

void salary(struct Person* person) {
    person->salary = (Money)(person->salary * 1.07);
}

void house(struct Person* person) {
    person->house = (Money)(person->house * 1.08);
}

void food(struct Person* person) {
    person->food = (Money)(person->food * 1.08);
}

void transport(struct Person* person) {
    person->transport = (Money)(person->transport * 1.08);
}

void utilities(struct Person* person) {
    person->utilities = (Money)(person->utilities * 1.08);
}

void annual_expenses(struct Person* person) {
    salary(person);
    house(person);
    food(person);
    transport(person);
    utilities(person);
}

void deposit_interest(struct Person* person) {
    person->deposit += person->deposit * person->deposit_interest_rate / 12;
}

void simulation() {
    while (!(year == 2054 && month == 10)) {
        
        if (month == 12) {
            annual_expenses(&Alice);
            annual_expenses(&Bob);
        }

       
        Alice.account += Alice.salary;
        Alice.spendings = Alice.food + Alice.transport + Alice.utilities + Alice.mortgage;
        Alice.account -= Alice.spendings;

        if (Alice.account > 0) {
            Alice.deposit += Alice.account;
            Alice.account = 0;
        }

        deposit_interest(&Alice);

        
        Bob.account += Bob.salary;
        Bob.spendings = Bob.food + Bob.transport + Bob.utilities + Bob.house_rent;
        Bob.account -= Bob.spendings;

        if (Bob.account > 0) {
            Bob.deposit += Bob.account;
            Bob.account = 0;
        }

        deposit_interest(&Bob);

       
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
