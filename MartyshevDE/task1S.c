#include <stdio.h>


typedef long long int Money;


struct Mortgage
{
    double rate;
    Money credit;
    Money pay;
    Money month_pay;
};


struct Bank
{
    Money vklad;
    Money month_pay;
};


struct Individual
{
    Money zarplata;
    Money rashod;
    Money status;
    Money kvartira;
    Money rubles; 
    struct Mortgage mortgage;
    struct Bank bank;
};


struct Individual Alice;
struct Individual Bob;  


void Alice_money()
{
    Alice.status = 0;
    Alice.zarplata = 200*1000;
    Alice.rashod = 50*1000;
    Alice.rubles = 0;

    Alice.mortgage.rate = 0.17;
    Alice.mortgage.credit = 13*1000*1000;
    Alice.mortgage.month_pay = 150*1000;
}


void Alice_mortgage()
{
    Alice.status -= Alice.mortgage.month_pay;
}


void Alice_zarplata(const int month, const int year)
{
    if(month == 12) {
        Alice.status += Alice.zarplata;
    }
    if(month == 1) {
        Alice.zarplata *= 1.09;
    }
    Alice.status += Alice.zarplata;
}


void Alice_print()
{
    if (Alice.status > Bob.status) {
        printf ("Alice has more money than Bob on %lld\n", Alice.status - Bob.status);
    }

    if (Alice.status < Bob.status) {
        printf ("Bob has more money than Alice on %lld\n", Bob.status - Alice.status);
    }

    printf ("Alice capital = %lld \n", Alice.status);
}


void Bob_money()
{
    Bob.status = 0;
    Bob.zarplata = 200*1000;
    Bob.rashod = 50*1000;
    Bob.kvartira = 30*1000; 
    Bob.rubles = 0;
    Bob.bank.month_pay = 120*1000;
}


void Bob_zarplata(const int month, const int year)
{
    if(month == 12) {
        Bob.status += Bob.zarplata;
    }
    if(month == 1) {
        Bob.zarplata *= 1.09;
    }
    Bob.status += Bob.zarplata;
}


void Bob_bank(int deposit)
{
    int month = 9;
    int year = 2024;

    while( !((month == 9) && (year == 2054)) ) {

    deposit = 20; 
    Bob.status -= Bob.bank.month_pay;
    Bob.bank.vklad = ((deposit/12)*0.01+1);
    Bob.rubles += (Bob.zarplata -Bob.bank.month_pay - Bob.rashod - Bob.kvartira);
    Bob.status += (Bob.bank.vklad + Bob.rubles);
    }
}


void Bob_kvartira(int year)
{
    year = 2024;
    if (year== 2034 || year == 2044 || year == 2054) {
        Bob.kvartira += 5000;
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
        
        Alice_zarplata(month, year);
        Alice_mortgage();
        
        Bob_zarplata(month, year);
        Bob_kvartira(year);

        month++;
        if(month == 13) {
            month = 1;
            year++;
        }
    }
}


int main()
{
    Alice_money();

    Bob_money();

    simulation();

    Alice_print();

    Bob_print();
    return 1;
}

Да
