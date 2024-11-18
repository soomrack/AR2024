#include<stdio.h>
#include<math.h>

typedef long long int Money;   // RUB

struct Deposits {
    double protsent; // процент вклада
    Money account;
};

struct Hypothec {  
    double protsent;
    Money credit;
    Money platez;
    Money month_pay;
};

struct Robotics {   // Хобби
    Money courses;
    int is_interesting;
};

struct Basketball {  // Хобби
    Money lesson;
    int is_interesting;
};

struct Car {
    Money petrol;  // Бензин
    Money insurance; // Страховка
    Money maintenance; // Тех. обслуживание
    int is_car;
};


struct Human {
    Money salary;
    Money account;
    Money food;
    Money exepenses; 
    Money rent;
    struct Hypothec hypothec;
    struct Basketball basketball;
    struct Robotics robotics;
    struct Car car;
    struct Deposits deposits;
};

struct Human alice;
struct Human bob;


void alice_hypothec(const int month) {
    alice.account -= alice.hypothec.month_pay;
    
    alice.hypothec.credit -= alice.hypothec.month_pay;

    if (month == 1) {
        alice.hypothec.month_pay *= 1.04;

        alice.hypothec.credit *= 1.04;
    }
}


void alice_food(const int month) {
    if (month == 1) {
        alice.food *= 1.08;
    }
    alice.account -= alice.food;
}


void alice_exepenses(const int month) {
    if (month == 1) {
        alice.exepenses *= 1.06;
    }
    alice.account -= alice.exepenses;
}


void alice_init() {
    alice.account = 1000 * 1000;
    alice.salary = 250 * 1000;
    alice.food = 10 * 1000;
    alice.exepenses = 7 * 1000;

    alice.hypothec.platez = 1000 * 1000;
    alice.hypothec.credit = 14000 * 1000;
    alice.hypothec.protsent = 0.14;
    alice.hypothec.month_pay = 285 * 1000;
    alice.account -= alice.hypothec.platez;
    alice.hypothec.credit -= alice.hypothec.platez;
    alice.hypothec.credit -= alice.hypothec.month_pay;

    alice.robotics.courses = 4000;
    alice.robotics.is_interesting = 0;

    alice.basketball.lesson = 2000;
    alice.robotics.is_interesting = 0;
}


void alice_robotics(const int month, const int year) {
    if ((month == 12) && (year == 2025))
    {
        alice.account -= 37000;
        alice.robotics.is_interesting = 1;
    }
    if ((year == 2032) && (month == 9))
    {
        alice.robotics.is_interesting = 0;
    }
    if (month == 1)
    {
        alice.robotics.courses *= 1.09;
    }
    if (alice.robotics.is_interesting = 1)
    {
        alice.account -= alice.robotics.courses;
    }
}


void alice_basketball(const int month, const int year) {
    if ((month == 2) && (year == 2033))
    {
        alice.account -= 20000;
        alice.basketball.is_interesting = 1;
    }
    if ((year == 2040) && (month == 6))
    {
        alice.basketball.is_interesting = 0;
    }
    if (month == 1)
    {
        alice.basketball.lesson *= 1.05;
    }
    if (alice.basketball.is_interesting = 1)
    {
        alice.account -= alice.basketball.lesson;
    }
}


void alice_salary(int month) {
    if (month == 12) {
        alice.account += alice.salary;
    }
    if (month == 1)
    {
        alice.salary *= 1.1;
    }
    alice.account += alice.salary;
}


void bob_exepenses(const int month) {
    if (month == 1)
    {
        alice.exepenses *= 1.06;
    }
    bob.account -= bob.exepenses;
}


void bob_rent(const int month) {
    if (month == 1){

        bob.rent *= 1.06;
    }
    bob.account -= bob.rent;
}


void bob_food(const int month) {
    if (month == 1)
    {
        bob.food *= 1.08;
    }
    bob.account -= bob.food;
}


void bob_deposits(const int year) {
    bob.deposits.account *= 1.01;  
    bob.deposits.account += bob.account;

}


void bob_init() {
    bob.account = 1000 * 1000;
    bob.salary = 300 * 1000;
    bob.food = 10 * 1000;
    bob.exepenses = 7 * 1000;

    bob.rent = 32 * 1000;

    bob.deposits.account += bob.account;
    bob.deposits.account = 0;
    bob.deposits.protsent = 0.12;

    bob.robotics.courses = 5000;
    bob.robotics.is_interesting = 0;

    bob.car.petrol = 8000;
    bob.car.insurance = 3339;
    bob.car.maintenance = 6000;

}


void bob_car(const int month, const int year) {
    if ((month == 12) && (year == 2030))
    {
        bob.car.is_car = 1;
        bob.account -= 500 * 1000;
        bob.account -= bob.car.petrol;
        bob.account -= bob.car.insurance;
        bob.account -= bob.car.maintenance;
    }
    if (month == 1)
    {
        bob.car.petrol *= 1.09;
        bob.account -= bob.car.insurance;
        bob.account -= bob.car.maintenance;
    }
    if (bob.car.is_car == 1)
    {
        bob.account -= bob.car.petrol;
    }
}


void bob_robotics(const int month, const int year) {
    if ((month == 12) && (year == 2025))
    {
        bob.account -= 45000;
        bob.robotics.is_interesting = 1;
    }
    if ((year == 2032) && (month == 9))
    {
        bob.robotics.is_interesting = 0;
    }
    if (month == 1)
    {
        bob.robotics.courses *= 1.09;
    }
    if (bob.robotics.is_interesting = 1)
        bob.account -= bob.robotics.courses;
}


void bob_salary(int month) {
    if (month == 12) {
        alice.account += alice.salary;
    }
    if (month == 1)
    {
        alice.salary *= 1.09;
    }
    alice.account += alice.salary;
}


void simulation() {
    int month = 9;
    int year = 2024;

    while (!((month == 9) && (year == 2024 + 30))) {
        alice_init();
        alice_salary(month);
        alice_food(month);
        alice_exepenses(month);
        alice_basketball(month, year);
        alice_robotics(month, year);
        alice_hypothec(month);

        bob_init();
        bob_salary(month);
        bob_food(month);
        bob_exepenses(month);
        bob_robotics(month, year);
        bob_car(month, year);
        bob_deposits(year);

        month++;
        if (month == 13)
        {
            month = 1;
            year++;
        }
    }

}


void alice_print() {
    printf("Alice account = %lld \n", alice.account); 
}

void bob_print() {
    printf("Bob account = %lld \n", bob.account); 
}


int main() {
    alice_init();
    bob_init();

    simulation();

    alice_print();
    bob_print();
    return 1;
}
