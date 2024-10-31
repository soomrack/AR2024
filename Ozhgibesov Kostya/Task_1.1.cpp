#include <iostream>
#include <stdio.h>

typedef long long int Money;

struct Person {
    Money salary;
    Money every_month_pays;
    Money mortage;
    Money deposit;
    Money house;
    Money account;
    Money a_rent;
    Money cat; // кот включен в ежемесячные расходы и тратит 5% от зп ежемесячно
};

Person ash;
Person pin;

// Параметры структуры объекта
void person_ash() {
    ash.account = 0;
    ash.salary = 200 * 1000;
    ash.mortage = 0.35 * ash.salary;
    ash.every_month_pays = 0.45 * ash.salary;
    ash.cat = 0.05 * ash.salary;
    ash.house = 9000 * 1000;
}

void person_pin() {
    pin.account = 0;
    pin.salary = 200 * 1000;
    pin.deposit = 1000 * 1000;
    pin.a_rent = 0.3 * pin.salary;
    pin.every_month_pays = 0.45 * pin.salary;
    pin.cat = 0.05 * pin.salary;
}

void ash_salary(int month, int year) {
    if (month == 12) {
        ash.salary *= 1.08;
    }
    ash.account += ash.salary;
}

void ash_house(int month, int year) {
    if (month == 12) {
        ash.house *= 1.12;
    }
}

void ash_every_month_pays(int month, int year) {
    if (month == 12) {
        ash.every_month_pays *= 1.08;
    }
    ash.account -= ash.every_month_pays;
}

void pin_deposit() {
    pin.deposit *= (1 + 0.12 / 12);
}

void pin_salary(int month, int year) {
    if (month == 12) {
        pin.salary *= 1.08;
    }
    pin.account += pin.salary;
}

void pin_every_month_pays(int month, int year) {
    if (month == 12) {
        pin.every_month_pays *= 1.08;
    }
    pin.account -= pin.every_month_pays; // Исправлено
}

void ash_and_pin_accounts(int month, int year) {
    if (year == 2054 && month == 10) {
        ash.account += ash.house;
    }

    if (year == 2054 && month == 10) {
        pin.account += pin.deposit;
    }
}

void simulation() {
    person_ash(); // инициализация
    person_pin(); // инициализация

    int month = 10;
    int year = 2024;

    while (!(year == 2054 && month == 10)) {
        ash_salary(month, year);
        ash_every_month_pays(month, year);
        ash_house(month, year);

        pin_salary(month, year);
        pin_every_month_pays(month, year);
        pin_deposit();

        ash_and_pin_accounts(month, year);

        month++;
        if (month == 13) {
            year++;
            month = 1;
        }
    }
}

void result() {
    if (ash.account > pin.account) {
        printf("\\nAsh has more capital on: %lld\\n", ash.account - pin.account);
    }
    else {
        printf("\\nPin has more capital on: %lld\\n", pin.account - ash.account);
    }
}

int main() {
    simulation();
    result();
    return 0;
}
