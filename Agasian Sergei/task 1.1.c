#include <stdio.h>
typedef  long long int Money;

struct Person {
    Money Bank;    // деньги на карте
    Money BankDeposit;   // деньги на депозитном счёте
    Money expenses;  // расходы
    Money zarplata;  // зарплата
    Money Bank_Active;
    Money summa_credita;
    Money mouth_pay;
    Money kvartira_cost;
    Money total;

};

struct Person Alice;

struct Person Bob;


void Alice_init()
{
    Alice.expenses = 70 * 1000;
    Alice.zarplata = 20 * 10000;
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
     if (month == 1){
        Alice.expenses = Alice.expenses * 1.1;
     }
}


void Alice_kvartira_cost(const int mouth)
{
    if (mouth == 1){
       Alice.kvartira_cost = Alice.kvartira_cost * 1.1; 
    }
}


void Alice_credit()
{
    Alice.Bank_Active = Alice.Bank_Active - Alice.mouth_pay;
}


void Alice_zarplata(const int month)
{
    Alice.Bank_Active = Alice.zarplata;
    if (month == 9){
        Alice.zarplata = Alice.zarplata * 1.09;
     }
}


void Alice_Bank_Account()
{
    Alice.Bank = Alice.Bank_Active + Alice.Bank;
    Alice.Bank_Active = 0;
}


void Alice_Deposit(const int month)
{
    if (month ==1){
        Alice.BankDeposit = Alice.BankDeposit * 1.2;
        Alice.BankDeposit = Alice.BankDeposit + Alice.Bank;
        Alice.Bank = 0;
    }
}


void Alice_print()
{
    Alice.total = Alice.BankDeposit + Alice.kvartira_cost + Alice.Bank_Active;
    printf("Alice = %lld\n", Alice.total);
}


void Alice_simulation()
{
    int month = 1;
    int year = 2024;
    while( !((month == 1) && (year == 2054))){
        Alice_zarplata(month);
        Alice_expensens(month);
        Alice_credit();
        Alice_Bank_Account();
        Alice_kvartira_cost(month);
        Alice_Deposit(month);
        month++;
        if (month == 13) {
            month = 1;
            year++;
        }
    }
}


void Bob_init()
{
    Bob.expenses = 50 * 1000;
    Bob.zarplata = 20 * 10000;
    Bob.Bank = 0;
    Bob.BankDeposit = 10 * 100000;
    Bob.mouth_pay = 48000;
}


void Bob_expensens( int month)
{
    Bob.Bank_Active = Bob.Bank_Active - Bob.expenses;
    Bob.Bank_Active = Bob.Bank_Active - Bob.mouth_pay;
     if (month == 1){
        Bob.expenses = Bob.expenses * 1.1;
        Bob.mouth_pay = Bob.mouth_pay * 1.1;
     }
}


void Bob_zarplata( const int month)
{
    Bob.Bank_Active = Bob.zarplata;
    if (month == 9){
        Bob.zarplata = Bob.zarplata * 1.09;
    }
}


void Bob_Bank_Account()
{
    Bob.Bank = Bob.Bank_Active + Bob.Bank;
}


void Bob_Deposit( const int month)
{
    if (month ==1){
        Bob.BankDeposit = Bob.BankDeposit * 1.2;
        Bob.BankDeposit = Bob.BankDeposit + Bob.Bank;
        Bob.Bank = 0;
    }
}


void Bob_education(const int month, const int year)
{
    if ((month == 9) && (year == 2034)){
        Bob.Bank_Active = Bob.Bank_Active - 88000;
    }
    if ((month == 9) && (year == 2035)){
        Bob.Bank_Active = Bob.Bank_Active - 88000;
    }
    if ((month == 9) && (year == 2036)){
        Bob.Bank_Active = Bob.Bank_Active - 87000;
    }
    if ((month == 9) && (year == 2037)){
        Bob.Bank_Active = Bob.Bank_Active - 82000;
    }

}


void Bob_print()
{
    Bob.total = Bob.BankDeposit + Bob.Bank_Active;
    printf("Bob = %lld\n", Bob.total);
}


void Bob_simulation()
{
    int month = 1;
    int year = 2024;
    while( !((month == 1) && (year == 2054))){
        Bob_zarplata(month);
        Bob_expensens(month);
        Bob_education (month, year);
        Bob_Bank_Account();
        Bob_Deposit(month);
        month++;
        if (month == 13){
            month = 1;
            year++;
        }
    }
}


int main()
{
    Alice_init();
    Alice_simulation();
    Alice_print();

    Bob_init();
    Bob_simulation();
    Bob_print();

    return 0;
}