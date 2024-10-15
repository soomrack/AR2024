#include <stdio.h>

typedef long long Money;

int month = 9;
int year = 2024;


struct Person  {
    Money house;
    Money capital;
    Money vklad;
    Money ipoteka;
    Money zp;
    Money rashod;
};

struct Person Alice =
    {
    .capital = 14000000,
    .ipoteka = 185338,
    .zp = 310000,
    .rashod = 60000
};

struct Person Bob =
    {
    .capital = 1000000,
    .zp = 310000,
    .rashod = 85000,
};

void Alice_capital(const int month, const int year) {
    if (month == 12) {
        Alice.zp *= 1.09;
        Alice.house *= 1.09;
    }
    Alice.capital += Alice.zp;
    if (month == 9 && year == 2054) {
        Alice.capital += Alice.house;
    }
}

void Alice_rashod(const int month, const int year) {
    if (month == 12) {
        Alice.rashod *= 1.09;
        Alice.rashod = Alice.rashod + Alice.ipoteka;
            Alice.capital -= Alice.rashod;
    }
}

void Bob_zp(const int month, const int year) {
    if (month == 12) {
        Bob.zp *= 1.09;
    }
    Bob.capital += Bob.zp;
}



void Bob_rashod(const int month, const int year) {
    if (month == 12) {
        Bob.rashod *= 1.09;
    }
}

void simulation() {
    while (!(year == 2054 && month == 10)) {
        Alice_capital(month, year);
        Alice_rashod(month, year);
        Bob_zp(month, year);
        Bob_rashod(month, year);
        month++;
        if (month == 13) {
            year = year + 1;
            month = 1;
        }
    }
}

void result() {
    if (Alice.capital > Bob.capital) {
        printf("\nAlice is richer than Bob on: %lld", Alice.capital - Bob.capital);
        printf("\nAlice: %lld", Alice.capital);
        printf("\nBob: %lld", Bob.capital);
    } else {
        printf("\nBob is richer than Alice on: %lld", Bob.capital - Alice.capital);
        printf("\nAlice: %lld", Alice.capital);
        printf("\nBob: %lld", Bob.capital);


    }
}

int main() {
    simulation();
    result();
    return 0;
}
