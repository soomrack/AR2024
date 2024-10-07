#include <stdio.h>

typedef long long Money;
int month = 9;
int year = 2024;

struct Person {
    Money salary;   //зарплата
    Money for_living;   //деньги для жизни
    Money account;  //сбережения
    Money house; //цена квартиры
    Money house_rent; //аренда
    Money expenses; //расходы
    Money mortgage; //ипотека
};

struct Person Alice = {200*1000,100*1000,0,14000*1000,0,0,150*1000};

struct Person Bob = {200*1000,100*1000,0,14000*1000,40*1000,0,0};


void alice_salary(const int month, const int year) {
    if (month == 12) {
        Alice.salary *= 1.06;   //индексации
        Alice.house *= 1.08;
    }
    Alice.account += Alice.salary;  //к сбережениям добавим зп
    if (month == 9 && year == 2024+30) {
        Alice.account += Alice.house;   //куплена картира
    }
}

void alice_expenses(const int month,const int year) {
    if (month == 12) {
        Alice.for_living *=1.08;    //индексации
    }
    Alice.expenses = Alice.for_living + Alice.mortgage;
    Alice.account -= Alice.expenses;
}



void bob_salary(const int month,const int year) {
    if (month == 12) {
        Bob.salary *= 1.06; //индексации
    }
    Bob.account += Bob.salary;
}

void bob_expenses(const int month,const int year) {
    if (month == 12) {
        Bob.for_living *= 1.08; //индексации
        Bob.house_rent *= 1.08;
    }
    Bob.expenses = Bob.for_living + Bob.house_rent;
    Bob.account -= Bob.expenses;    //вычет трат с учётом аренды жилья
}

void simulation() {
    while (!(year == 2024+30 && month == 10)) {
        alice_salary(month, year);
        alice_expenses(month, year);
        bob_salary(month,year);
        bob_expenses(month, year);
        month++;
        if (month == 13) {
            year++;
            month = 1;
        }
    }
}

//сравнение капиталов
void result() {
    if (Alice.account > Bob.account) {
        printf("Alice is richer on %lld\n", Alice.account - Bob.account);
    } else {
        printf("Bob is richer on %lld\n", Bob.account - Alice.account);
    }
}

int main () {
    simulation();
    result();
    return 0;
}
