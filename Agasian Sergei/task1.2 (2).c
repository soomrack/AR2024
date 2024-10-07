#include <stdio.h>

struct person
{
    float Bank;    // деньги на карте
    float BankD;   // деньги на депозитном счёте
    float rashodi;  // расходы
    float zarplata;  // зарплата
    float karman;   // неважно)
    float summa_credita;
    float mouth_pay;

};

struct person Alice;

void Alice_znach()
{
    Alice.rashodi = 70*1000;
    Alice.zarplata = 20*10000;
    Alice.summa_credita = 11999880;
    Alice.Bank = 0;
    Alice.BankD = 0;
    Alice.mouth_pay = 33333;
}

void Alice_rashodi()
{
    Alice.karman = Alice.karman - Alice.rashodi;
}
void Alice_credit()
{
    Alice.karman = Alice.karman - Alice.mouth_pay;
}
void Alice_zarplata()
{
    Alice.karman = Alice.zarplata;
}
void Alice_inf_ind()
{
    Alice.zarplata = Alice.zarplata*1.09;
    Alice.rashodi = Alice.rashodi*1.1;
}
void Alice_Bank_Account()
{
    Alice.Bank = Alice.karman + Alice.Bank;
}
void Alice_Deposit()
{
    Alice.BankD = Alice.BankD*1.2;
    Alice.BankD = Alice.BankD + Alice.Bank;
}
void Alice_simulation()
{
    for(int e=1; e<=360; e+=12)
    {
        for(int e=1; e<=360; e++)
        {
           Alice_zarplata();
           Alice_rashodi();
           Alice_credit();
           Alice_Bank_Account();
           printf("\n Alice %10.2f", Alice.Bank);
           if (e % 12 == 0) break;
        }
        Alice_Deposit();
        printf("\n Alice %10.2f", Alice.BankD);
        Alice.Bank = 0;
        printf("\n %10.2f", Alice.Bank);
        Alice_inf_ind();
    }
}
void Alice_print()
{
    printf("\n Alice %10.2f", Alice.BankD);
}

struct person Bob;

void Bob_znach()
{
    Bob.rashodi = 50*1000;
    Bob.zarplata = 20*10000;
    Bob.Bank = 0;
    Bob.BankD = 10*100000;
    Bob.mouth_pay = 48000;
}
void Bob_rashodi()
{
    Bob.karman = Bob.karman - Bob.rashodi;
}
void Bob_rent()
{
    Bob.karman = Bob.karman - Bob.mouth_pay;
}
void Bob_zarplata()
{
    Bob.karman = Bob.zarplata;
}
void Bob_inf_ind()
{
    Bob.zarplata = Bob.zarplata*1.09;
    Bob.rashodi = Bob.rashodi*1.1;
    Bob.mouth_pay = Bob.mouth_pay*1.1;
}
void Bob_Bank_Account()
{
    Bob.Bank = Bob.karman + Bob.Bank;
}
void Bob_Deposit()
{
    Bob.BankD = Bob.BankD*1.2;
    Bob.BankD = Bob.BankD + Bob.Bank;
}
void Bob_print()
{
    printf("\n %10.2f", Bob.BankD);
}
void Bob_simulation()
{
    Bob_Deposit();
    for(int e=1; e<=360; e+=12)
    {
        for(int e=1; e<=360; e++)
        {
           Bob_zarplata();
           Bob_rashodi();
           Bob_rent();
           Bob_Bank_Account();
           printf("\n %10.2f", Bob.Bank);
           if (e % 12 == 0) break;
        }
        Bob_Deposit();
        printf("\n Bob %10.2f", Bob.BankD);
        Bob.Bank = 0;
        printf("\n %10.2f", Bob.Bank);
        Bob_inf_ind();
    }
}
int main()
{
    Alice_znach();
    Alice_simulation();
    Alice_print();
    Bob_znach();
    Bob_simulation();
    Bob_print();
    return 0;
}