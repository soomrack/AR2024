#include <stdio.h>
typedef long long unsigned Money;
struct Person
{
    Money salary;   //зарплата
    Money account;  //сбережения
    Money house; //цена квартиры
    Money house_rent; //аренда
    Money expenses; //расходы
    Money mortgage; //ипотека
};
struct Person Alice;
struct Person Bob;
void alice()
{
    Alice.mortgage = 150*1000;
    Alice.expenses = 50*1000;
    Alice.house = 14000*1000;
    Alice.salary = 200 * 1000;
    Alice.account = 0;
    int month = 9;
    int year = 2024;
    while ( year <= 2024+30 )
    {
        Alice.account += Alice.salary;  //к сбережениям добавим зп
        Alice.account -= Alice.expenses + Alice.mortgage;   // вычет расходов и ипотеки


        month++;
        if ( month == 13 )
        {
            year++;
            month = 1;
        }
        if (month ==1)
        {
            Alice.salary *= 1.06;   //индексации
            Alice.house *= 1.08;
            Alice.expenses *= 1.08;
        }
        if (year == 2024+30 && month == 10) break;
    }
    Alice.account += Alice.house;   //куплена картира
}

void bob()
{
    Bob.salary = 200 * 1000;
    Bob.expenses = 100*1000;
    Bob.account = 0;
    Bob.house = 14000 * 1000;
    Bob.house_rent = 40 * 1000;
    int month = 9;
    int year = 2024;
    while (year <= 2024+30)
    {
        Bob.account += Bob.salary;  //добавление зп к сбережениям
        Bob.account -= Bob.expenses + Bob.house_rent; //вычет трат и аренды жилья
        month++;
        if (month == 13)
        {
            year = year + 1;
            month = 1;
        }
        if (month == 12)
        {
            Bob.salary *= 1.06; //индексация
            Bob.expenses *= 1.08;
            Bob.house *= 1.08;
        }
        if (year == 2024+30 && month == 10) break;
    }
}

void result()
{
    if (Alice.account > Bob.account)    //сравнение капиталов
    {
        printf("Alice is richer on %llu\n", Alice.account - Bob.account);
    }
    else
    {
        printf("Bob is richer on %llu\n", Bob.account - Alice.account);
    }
}

int main ()
{
    alice();
    bob();
    result();
    return 0;
}
