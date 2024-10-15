#include <stdio.h>

typedef long money;

struct person {
    money salary;
    money account;
    money charges;
    money rent;
    money flat;
    money loan;
    money unforeseen_situations;
};
person Bob{ 200 * 1000, 1000 * 1000, 25 * 1000, 40 * 1000, 0, 100 * 1000, 10 * 1000 };
person Alice{ 200 * 1000, 1000 * 1000, 30 * 1000, 0, 14000 * 1000, 100 * 1000, 10 * 1000 };

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

int year;
int month;

void simulation() {
    while (!(year == 2054 && month == 10)) {
        Alice_salary(month, year);
        Alice_charges(month, year);
        Bob_salary(month, year);
        Bob_charges(month, year);
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
    } else {
        printf("Alice is richer\n");
    }
}
int main() {
    simulation();
    result();
    return 0;
}
