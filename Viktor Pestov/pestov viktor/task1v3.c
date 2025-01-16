#include <stdio.h>

typedef long long int Money;  // Рубли

struct Mortgage {
    double rate;
    Money credit;
    Money platez;
    Money month_pay;
};

struct Bank_deposit {
    double rate;
    Money deposit_account;
};

struct Cat {
    int is_alive;
    Money cost;
    Money monthly_exp;
};

struct Car {
    int is_owned;
    Money value;
    Money monthly_exp;
    Money repair_cost;
};

struct Person {
    Money salary;
    Money account;
    Money kvartira;
    Money expenses;
    Money vacation_account;
    Money vacation_cost;
    struct Mortgage mortgage;
    struct Bank_deposit deposit;
    struct Cat cat;
    struct Car car;
};

struct Person bob;
struct Person alice;

// Alice
void alice_init() {
    alice.account = 1000 * 1000;
    alice.salary = 200 * 1000;
    alice.expenses = 50 * 1000;

    alice.mortgage.platez = 100 * 1000;
    alice.mortgage.credit = 10 * 1000 * 1000;
    alice.mortgage.rate = 0.19;
    alice.mortgage.month_pay = 100000;
    alice.account -= alice.mortgage.platez;
    alice.kvartira = 10000000;

    alice.cat.is_alive = 0;
}

void alice_buy_cat(int year) {
    if (year == 2030 && !alice.cat.is_alive) {
        alice.cat.cost = 40000;
        alice.cat.monthly_exp = 5000;
        alice.cat.is_alive = 1;
        alice.account -= alice.cat.cost;
    }
}

void alice_care_for_cat(int year) {
    if (alice.cat.is_alive) {
        if (year == 2039) {
            alice.cat.is_alive = 0;
        } else {
            alice.account -= alice.cat.monthly_exp;
        }
    }
}

void alice_salary(const int month, const int year) {
    if (month == 1) {
        alice.salary *= 1.07;
    }
    alice.account += alice.salary;
}

void alice_mortgage() {
    if (alice.account >= alice.mortgage.month_pay) {
        alice.account -= alice.mortgage.month_pay;
    } else {
        // Обработка ситуации, когда денег недостаточно
    }
}

void alice_expenses(const int month) {
    if (month == 1) {
        alice.expenses *= 1.08;
    }
    if (alice.account >= alice.expenses) {
        alice.account -= alice.expenses;
    } else {
        // Обработка ситуации, когда денег недостаточно
    }
}

void alice_kvartira(const int month) {
    if (month == 1) {
        alice.kvartira *= 1.08;
    }
}

void alice_print() {
    printf("Alice account = %Ld \n", alice.kvartira + alice.account);
}

// Bob
void bob_init() {
    bob.salary = 200000;
    bob.deposit.deposit_account = 1000000;
    bob.kvartira = 100000;
    bob.expenses = 60000;
    bob.deposit.rate = 0.12;
    bob.vacation_account = 0;
    bob.vacation_cost = 40000;

    bob.car.is_owned = 0;
}

void bob_win_car(int year) {
    if (year == 2035 && !bob.car.is_owned) {
        bob.car.value = 4000000;
        bob.car.monthly_exp = 35000;
        bob.car.is_owned = 1;
    }
}

void bob_maintain_car(int year) {
    if (bob.car.is_owned) {
        bob.account -= bob.car.monthly_exp;
    }
}

void bob_repair_car(int year) {
    if (year == 2039 && bob.car.is_owned) {
        bob.car.repair_cost = 300000;
        bob.account -= bob.car.repair_cost;
    }
}

void bob_sell_car(int year) {
    if (year == 2040 && bob.car.is_owned) {
        bob.account += 2000000;
        bob.car.is_owned = 0;
    }
}

void bob_salary(const int month) {
    if (month == 1) {
        bob.salary *= 1.08;
    }
    
    if (month == 2) {
        bob.account += bob.salary;  // Обычная зарплата
        bob.account += bob.salary;  // Премия, равная зарплате
    } else {
        bob.account += bob.salary;
    }
}

void bob_expenses(const int month) {
    if (month == 1) {
        bob.expenses *= 1.08;
    }
    if (bob.account >= bob.expenses) {
        bob.account -= bob.expenses;
    } else {
        // Обработка ситуации, когда денег недостаточно
    }
}

void bob_kvartira(const int month, const int year) {
    if (month == 1) {
        bob.kvartira *= 1.08;
    }
    if (bob.account >= bob.kvartira) {
        bob.account -= bob.kvartira;
    } else {
        // Обработка ситуации, когда денег недостаточно
    }
}

void bob_bank(const int month, const int year) {
    bob.deposit.deposit_account *= ((bob.deposit.rate / 12) + 1);
    bob.deposit.deposit_account += bob.account;
    bob.account = 0;
}

void bob_vacation(const int month) {
    if (month == 1) {
        bob.vacation_cost *= 1.08;
    }
    if (bob.account >= bob.vacation_cost) {
        bob.vacation_account += bob.vacation_cost;
        bob.account -= bob.vacation_cost;
    } else {
        // Обработка ситуации, когда денег недостаточно
    }
    if (month == 9) {
        bob.vacation_account = 0;
    }
}

void bob_print() {
    printf("Bob account = %Ld \n", bob.deposit.deposit_account);
}

void simulation() {
    int month = 1;
    int year = 2024;

    while (year <= 2024 + 29) {
        alice_buy_cat(year);
        alice_care_for_cat(year);

        alice_salary(month, year);
        alice_mortgage();
        alice_expenses(month);
        alice_kvartira(month);

        bob_win_car(year);
        bob_maintain_car(year);
        bob_repair_car(year);
        bob_sell_car(year);

        bob_salary(month);
        bob_expenses(month);
        bob_kvartira(month, year);
        bob_vacation(month);
        bob_bank(month, year);

        month++;
        if (month == 13) {
            month = 1;
            year++;
        }
    }
}

int main() {
    alice_init();
    bob_init();
    simulation();

    alice_print();
    bob_print();
    return 0;
}