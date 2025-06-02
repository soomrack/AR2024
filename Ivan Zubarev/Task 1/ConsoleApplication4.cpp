#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef long long int Money;
typedef bool Logik;

struct Cat {
    Money food;
    Logik buy_cat;
    Logik cat_is_alive;
};

struct Car {
    Money benzin;
    Money remont;
};

struct Mortgage {
    double rate;
    Money credit;
    Money payment;
    Money month_pay;
};

struct Arenda {
    Money price;
    Money month_pay;
};

struct Person {
    Money salary;
    Money account;
    Money food;
    Money expences;
    struct Cat cat;
    struct Mortgage mortgage;
    struct Arenda arenda;
    struct Car car;
};

struct Person alice;
struct Person bob;

void alice_mortgage() {
    alice.account -= alice.mortgage.month_pay;
}


double calculate_monthly_payment(double rate, double principal, int n) {
    double monthlyRate = rate / 12.0;
    return principal * (monthlyRate * pow(1 + monthlyRate, n)) / (pow(1 + monthlyRate, n) - 1);
}

void alice_food(const int month) {
    if (month == 1) {
        alice.food *= 1.1;
    }
    alice.account -= alice.food;
}


void bob_food(const int month) {
    if (month == 1) {
        bob.food *= 1.1;
    }
    bob.account -= bob.food;
}


void alice_init() {
    alice.account = 1000000;
    alice.salary = 200000;
    alice.food = 10000;
    alice.expences = 70000;

    alice.mortgage.payment = 1000000;
    alice.mortgage.credit = 14000000;
    alice.mortgage.rate = 0.17 / 12.0; 
    alice.mortgage.month_pay = calculate_monthly_payment(alice.mortgage.rate, alice.mortgage.credit, 360); 
    alice.account -= alice.mortgage.payment;

    alice.cat.food = 5000;
    alice.cat.buy_cat = false;
    alice.cat.cat_is_alive = true;
}

void bob_init() {
    bob.account = 1000000;
    bob.salary = 200000;
    bob.food = 15000;
    bob.expences = 50000;

    bob.arenda.price = 30000;
    bob.arenda.month_pay = 10000;

    bob.car.benzin = 100000;
    bob.car.remont = 50000;
    bob.cat.food = 10000; 
    bob.cat.buy_cat = false;
    bob.cat.cat_is_alive = false; 
}


void alice_buy_cat(const int month, const int year) {
    if (month == 10 && year == 2029) {
        alice.cat.cat_is_alive = true;
        alice.cat.buy_cat = true;
        alice.account -= 30000;
    }

  
    if (alice.cat.cat_is_alive == true) {
        alice.account -= alice.cat.food;
    }

    if ((month == 6) && (year == 2040)) {
        alice.cat.cat_is_alive = false;
    }
}
 

void bob_cat(const int month, const int year) {
    if (month == 7 && year == 2037) {
        bob.cat.cat_is_alive = true;
    }
    if (bob.cat.cat_is_alive == true) {
        bob.account -= bob.cat.food;
    }
    if ((month == 6) && (year == 2031)) {
        bob.cat.cat_is_alive = false;
    }
}


void bob_car_obslug(const int month, const int year) {
    if ((month == 11) && (year == 2027)) {
        bob.account -= bob.car.remont;
    }
    if ((month == 3) && (year == 2035)) {
        bob.account -= bob.car.remont;
    }
    if ((month == 6) && (year == 2043)) {
        bob.account -= bob.car.remont;
    }
}

}


void alice_salary(const int month, const int year) {
    alice.account += alice.salary;
}


void bob_salary(const int month, const int year) {
    bob.account += bob.salary;
    if (month == 9) { 
        bob.salary *= 1.08;
    }
}


void bob_deposit()
{
    bob.account *= 1.1;
    if ((month == 3) && (year == 2032))
        bob.account *=1.11
}


void influense(int const month, int const year) {
    if (month == 1) {
        alice.expences *= 1.07;
        bob.expences *= 1.07;
    }
}


void print_result() {
    printf("Alice account = %lld \t", alice.account);
    printf("Bob account = %lld \n", bob.account);
    if (alice.account > bob.account) {
        printf("Alice is richer on %d", alice.account - bob.account);
    }
    else {
        printf("Bob is richer on %d", bob.account - alice.account);
    }
}


void simulation() {
    int month = 9;
    int year = 2024;

    while (!((month == 9) && (year == 2024 + 30))) {

        alice_salary(month, year);
        alice_mortgage();
        alice_food(month);
        alice_buy_cat(month, year);

        bob_salary(month, year);
        bob_food(month);
        bob_car_obslug(month, year);
        bob_cat(month, year);
        bob_deposit();

        influense(month, year);

        month++;
        if (month == 13) {
            month = 1;
            year++;
            print_result();
        }
    }
}


int main() {
    alice_init();
    bob_init();
    simulation();
    return 0;
}