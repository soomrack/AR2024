#include <stdio.h>

typedef long long int money;

int year = 2024;
int month = 9;

// Структура ипотеки
struct Mortgage
{
    double rate;
    money credit;
    money pay;
    money month_pay;
};

struct Bank
{
    money vklad;
    money month_pay;
    
};


// Структура человека
struct Individual
{
    money zarplata;
    money rashod;
    money status;
    money kvartira;
    money rubles; //Оставшиеся деньги после всех расходов
    struct Mortgage mortgage;
    struct Bank bank;

};

// Персонажи
struct Individual Alice;
struct Individual Bob;  

//ALICE
void Alice_money()
{
    Alice.status = 0;
    Alice.zarplata = 2e5;
    Alice.rashod = 5e4;
    Alice.rubles = 0;

    Alice.mortgage.rate = 0.17;
    Alice.mortgage.credit = 13e6;
    Alice.mortgage.month_pay = 15e4;

}
    //Кредит Алисы (ежемесячный платеж)
void Alice_mortgage()
{
    Alice.status -= Alice.mortgage.month_pay;
}

void Alice_zarplata(const int month, const int year)
{
    if(month == 12){
        Alice.status += Alice.zarplata;
    }
    if(month == 1){
        Alice.zarplata *= 1.09;
    }
    Alice.status += Alice.zarplata;
}

void Alice_print()
{
    printf ("Alice capital = %lld \n", Alice.status);
}

//BOB
void Bob_money()
{
    Bob.status = 0;
    Bob.zarplata = 2e5;
    Bob.rashod = 5e4;
    Bob.kvartira = 3e4; 
    Bob.rubles = 0;
    Bob.bank.month_pay = 12e4;
}

void Bob_zarplata(const int month, const int year)
{
    if(month == 12){
        Bob.status += Bob.zarplata;
    }
    if(month == 1){
        Bob.zarplata *= 1.09;
    }
    Bob.status += Bob.zarplata;
}

void Bob_bank(int deposit)
{
    int month = 9;
    int year = 2024;

    while( !((month == 9) && (year == 2054)) ) {

    deposit = 20; //Процент за депозит
    Bob.status -= Bob.bank.month_pay;
    Bob.bank.vklad = ((deposit/12)*0.01+1);
    Bob.rubles += (Bob.zarplata -Bob.bank.month_pay - Bob.rashod - Bob.kvartira);
    Bob.status += (Bob.bank.vklad + Bob.rubles);

    }
}


void Bob_kvartira(int year)
{
    if (year== 2034 || year == 2044 || year == 2054){
        Bob.kvartira += 5e3;
    }
}

void Bob_print()
{
    printf ("Bob capital = %lld \n", Bob.status);
}

void simulation()
{
    int month = 9;
    int year = 2024;

    while( !((month == 9) && (year == 2054)) ) {
        
        //Alice
        Alice_zarplata(month, year);
        Alice_mortgage();
        
        //Bob
        Bob_zarplata(month, year);
        Bob_kvartira(year);

        month++;
        if(month == 13) {
            month = 1;
            year++;
        }
    }
}

// У кого больше денег
void Status_Alice_and_Bob()
{
    if (Alice.status > Bob.status){
        printf ("Alice has more money than Bob on %lld\n", Alice.status - Bob.status);
    }

    if (Alice.status < Bob.status){
        printf ("Bob has more money than Alice on %lld\n", Bob.status - Alice.status);
    }
}

int main()
{
    Status_Alice_and_Bob();

    Alice_money();

    Bob_money();

    simulation();

    Alice_print();

    Bob_print();
    return 1;
}
