#include <stdio.h>

typedef long long int money;

// Структура ипотеки
struct Mortgage
{
    double rate;
    money credit;
    money pay;
    money month_pay;
};

// Структура человека
struct Individual
{
    money zarplata;
    money rashod;
    money status;
    money kvartira;
    struct Mortgage mortgage;

};

// Персонажи
struct Individual Alice;
struct Individual Bob;  

//ALICE
void Alice_money()
{
    Alice.zarplata = 2e5;
    Alice.mortgage.rate = 0.17;
    Alice.rashod = 5e4;

}
    //Кредит Алисы (ежемесячный платеж)
void Alice_mortgage()
{
    Alice.status -= Alice.mortgage.month_pay
}

//Bob
void Bob_money()
{
    Bob.zarplata = 2e5;
    Bob.rashod = 5e4;
    Bob.kvartira = 3e4;
}

