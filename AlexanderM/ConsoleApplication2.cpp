#include <stdio.h> 


typedef long Money;
int month = 9;
int year = 2024;


struct Person {
    Money salary;
    Money account;
    Money charges;
    Money rent;
    Money flat;
    Money loan;
    Money unforeseen_situations;
    Money deposit;
    double deposit_percent;
};


struct Person Alice;
struct Person Bob;


void Bob_init() {
    Bob.salary = 200 * 1000;
    Bob.account = 1000 * 1000;
    Bob.charges = 25 * 1000;
    Bob.rent = 40 * 1000;
    Bob.flat = 0;
    Bob.loan = 100 * 1000;
    Bob.unforeseen_situations = 10 * 1000;
    Bob.deposit = 0;
    Bob.deposit_percent = 1.004;
};


void Alice_init() {
    Alice.salary = 200 * 1000;
    Alice.account = 1000 * 1000;
    Alice.charges = 30 * 1000;
    Alice.rent = 0;
    Alice.flat = 14000 * 1000;
    Alice.loan = 100 * 1000;
    Alice.unforeseen_situations = 10 * 1000;
    Alice.deposit = 0;
    Alice.deposit_percent = 1.004;
}


void Bob_salary(const int month, const int year) {
    if (month == 12) {
        Bob.salary *= 1.08;
    }
    Bob.account += Bob.salary;
}


void Bob_charges(const int month, const int year) {
    if (month == 12) {
        Bob.rent *= 1.08;
        Bob.unforeseen_situations *= 1.08;
    }
    Bob.charges = Bob.unforeseen_situations + Bob.rent;
    Bob.account -= Bob.charges;
}


void Bob_deposite()
{
    Bob.deposit += Bob.salary;
    Bob.deposit -= Bob.unforeseen_situations;
    Bob.deposit -= Bob.charges;
    Bob.deposit -= Bob.rent;
    Bob.deposit *= Bob.deposit_percent;
}


void Alice_salary(const int month, const int year) {
    if (month == 12) {
        Alice.salary *= 1.08;
        Alice.flat *= 1.08;
    }
    Alice.account += Alice.salary;
}


void Alice_charges(const int month, const int year) {
    if (month == 12) {
        Alice.unforeseen_situations *= 1.08;
    }
    Alice.charges = Alice.unforeseen_situations + Alice.loan;
    Alice.account -= Alice.charges;
}


void Alice_deposite() {
    Alice.deposit += Alice.salary;
    Alice.deposit -= Alice.unforeseen_situations;
    Alice.deposit -= Alice.charges;
    Alice.deposit -= Alice.loan;
    Alice.deposit *= Alice.deposit_percent;
}


void simulation() {
    while (!(year == 2054 && month == 10)) {
        Alice_salary(month, year);
        Alice_charges(month, year);
        Alice_deposite();
        Bob_salary(month, year);
        Bob_charges(month, year);
        Bob_deposite();
        month++;
        if (month == 13) {
            year = year + 1;
            month = 1;
        }
    }
}


void result() {
    if (Bob.account > Alice.account) {
        printf("Bob is richer\n");
    }
    else {
        printf("Alice is richer\n");
    }
}


int main() {
    simulation();
    result();
    return 0;
}
