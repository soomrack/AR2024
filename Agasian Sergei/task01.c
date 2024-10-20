#include <stdio.h>

typedef  long long int Money;

struct person
{
    Money Bank;    // деньги на карте
    Money BankDeposit;   // деньги на депозитном счёте
    Money expenses;  // расходы
    Money zarplata;  // зарплата
    Money Bank_Active;
    Money summa_credita;
    Money mouth_pay;
    Money kvartira_cost;

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
    Alice.Bank_Active = 0;
    Alice.mouth_pay = 33333;
    Alice.kvartira_cost = Alice.summa_credita + 10 * 100000;
}


void Alice_expensens(const int month)
{
    Alice.Bank_Active = Alice.Bank_Active - Alice.expenses;
     if (month == 1)
     {
        Alice.expenses = Alice.expenses * 1.1;
     }
}

void Alice_kvartira_cost(const int mouth)
{
    if (mouth == 1)
    {
       Alice.kvartira_cost = Alice.kvartira_cost * 1.1; 
    }
}

void Alice_credit()
{
    Alice.Bank_Active = Alice.Bank_Active - Alice.mouth_pay;
}


void Alice_zarplata( int month)
{
    Alice.Bank_Active = Alice.zarplata;
    if (month == 9)
     {
        Alice.zarplata = Alice.zarplata * 1.09;
     }
}


void Alice_Bank_Account()
{
    Alice.Bank = Alice.Bank_Active + Alice.Bank;
    Alice.Bank_Active = 0;
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
            Alice_kvartira_cost(month);
            Alice_Deposit();
            year++;
        }
    }
    long long int totalA = Alice.BankDeposit + Alice.kvartira_cost + Alice.Bank_Active;
    printf("Alice = %lld\n", totalA);
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
    Bob.Bank_Active = Bob.Bank_Active - Bob.expenses;
    Bob.Bank_Active = Bob.Bank_Active - Bob.mouth_pay;
     if (month == 1)
     {
        Bob.expenses = Bob.expenses * 1.1;
        Bob.mouth_pay = Bob.mouth_pay * 1.1;
     }
}


void Bob_zarplata( int month)
{
    Bob.Bank_Active = Bob.zarplata;
    if (month == 9)
     {
        Bob.zarplata = Bob.zarplata * 1.09;
     }
}


void Bob_Bank_Account()
{
    Bob.Bank = Bob.Bank_Active + Bob.Bank;
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
    long long int totalB = Bob.BankDeposit + Bob.Bank_Active;
    printf("Bob = %lld\n", totalB);
}


int main()
{
    Alice_values();

    Alice_simulation();

    Bob_values();

    Bob_simulation();

    return 0;
}