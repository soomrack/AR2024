#include <stdio.h>

typedef  long long int Money;

struct person
{
    Money Bank;    // деньги на карте
    Money BankDeposit;   // деньги на депозитном счёте
    Money expenses;  // расходы
    Money zarplata;  // зарплата
    Money karman;   // неважно)
    Money summa_credita;
    Money mouth_pay;

};

struct person Alice;

struct person Bob;


void Alice_values()
{
    Alice.expenses = 70*1000;
    Alice.zarplata = 20*10000;
    Alice.summa_credita = 11999880;
    Alice.Bank = 0;
    Alice.BankDeposit = 0;
    Alice.karman = 0;
    Alice.mouth_pay = 33333;
}


void Alice_expensens(const int month)
{
    Alice.karman = Alice.karman - Alice.expenses;
     if (month == 1)
     {
        Alice.expenses = Alice.expenses * 1.1;
     }
}


void Alice_credit()
{
    Alice.karman = Alice.karman - Alice.mouth_pay;
}


void Alice_zarplata( int month)
{
    Alice.karman = Alice.zarplata;
    if (month == 9)
     {
        Alice.zarplata = Alice.zarplata * 1.09;
     }
}


void Alice_Bank_Account()
{
    Alice.Bank = Alice.karman + Alice.Bank;
    Alice.karman = 0;
}


void Alice_Deposit()
{
    Alice.BankDeposit = Alice.BankDeposit * 1.2;
    Alice.BankDeposit = Alice.BankDeposit + Alice.Bank;
    Alice.Bank = 0;
}


void Alice_simulation()
{
    int month = 1;
    int year = 2024;
    while( !((month == 1) && (year == 2054)))
    {
        Alice_zarplata(month);
        Alice_expensens(month);
        Alice_credit();
        Alice_Bank_Account();
        month++;
        if (month == 13) 
        {
            month = 1;
            Alice_Deposit();
            year++;
        }
    }
    printf("Alice = %lld\n", Alice.BankDeposit);
    printf("Year = %d\n", year);
}


void Bob_values()
{
    Bob.expenses = 50*1000;
    Bob.zarplata = 20*10000;
    Bob.Bank = 0;
    Bob.BankDeposit = 10*100000;
    Bob.mouth_pay = 48000;
}


void Bob_expensens( int month)
{
    Bob.karman = Bob.karman - Bob.expenses;
    Bob.karman = Bob.karman - Bob.mouth_pay;
     if (month == 1)
     {
        Bob.expenses = Bob.expenses * 1.1;
        Bob.mouth_pay = Bob.mouth_pay * 1.1;
     }
}


void Bob_zarplata( int month)
{
    Bob.karman = Bob.zarplata;
    if (month == 9)
     {
        Bob.zarplata = Bob.zarplata * 1.09;
     }
}


void Bob_Bank_Account()
{
    Bob.Bank = Bob.karman + Bob.Bank;
}


void Bob_Deposit()
{
    Bob.BankDeposit = Bob.BankDeposit * 1.2;
    Bob.BankDeposit = Bob.BankDeposit + Bob.Bank;
    Bob.Bank = 0;
}


void Bob_simulation()
{
    int month = 1;
    int year = 2024;
    while( !((month == 1) && (year == 2054)))
    {
        Bob_zarplata(month);
        Bob_expensens(month);
        Bob_Bank_Account();
        month++;
        if (month == 13) 
        {
            month = 1;
            Bob_Deposit();
            year++;
        }
    }
    printf("Bob = %lld\n", Bob.BankDeposit);
    printf("Year = %d\n", year);
}


int main()
{
    Alice_values();

    Alice_simulation();

    Bob_values();

    Bob_simulation();

    return 0;
}