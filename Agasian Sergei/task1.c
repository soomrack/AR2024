#include <stdio.h>
#include <math.h>
int main()
{
    float a=38000; //рента
    float b=70000; //расходы A
    float B=70000; //расходы B
    float c=1.1; //инфляция
    float d=1.09; //индексация
    int e=360; //срок ипотеки
    float f=33333; //платеж по ипотеке
    float g=200000; //зарплата Alice
    float zp=200000; // зарплата Bob
    int n=12; //месяцев в году
    float s=0; //сумма на кармане Alice
    float w=1000000; // сумма на кармане Bob
    float i=11999880; //сумма ипотеки
    float BankA=0; //сумма на счету в банке Alice
    float BankB=0; //сумма на счету в банке Bob
    float BankAD = 0;
    float BankBD = 0;
    float p=1.2; //процент по вкладу
//Alice
        for(int e=1; e<=360; e+=n) //цикл года
        {
            for(int e=1; e<=360; e++) //цикл месяца
            {
                s=s-b-f+g;
                BankA=s+BankA;
                s=0;    // обнулил карман т.к перевел деньги в банк
                printf("\n mouth %d %9.2f", e, BankA);
                if (e % 12 == 0) break;
            }
        printf("\n year %d %9.2f", e/n+1, BankA);
        BankAD=BankAD*p;    // капает процент по депозиту
        BankAD=BankA+BankAD;    // переводим деньги на депозитный счет каждый год с со счёта в банке
        printf("\n year %d %9.2f", e/n+1, BankAD);
        BankA=0;    // счёт в банке обнулил, из-за перевода на депозитный счёт
        b=b*c;
        g=g*d;
        printf("\n year %d %9.2f", e/n+1, BankAD);
        }
    printf("\n total %9.2f", BankAD);
    // Bob
    printf("\n Bob");
    for(int e=1; e<=360; e+=n) //цикл года
        {
            for(int e=1; e<=360; e++) //цикл месяца
            {
                w=w-B-a+zp;
                BankB=w+BankB;
                w=0;
                printf("\n mounth %d %9.2f", e, BankB);
                if (e % 12 == 0) break;
            }
        printf("\n year %d %9.2f", e/n+1, BankB);
        BankBD=BankBD*p;    // капает процент по депозиту
        BankBD=BankB+BankBD;    // переводим деньги на депозитный счет каждый год с со счёта в банке
        printf("\n year %d %9.2f", e/n+1, BankBD);
        BankA=0;
        B=B*c;
        a=a*c;
        zp=zp*d;
        printf("\n year %d %9.2f", e/n+1, BankBD);
        }
    printf("\n total %9.2f", BankBD);
    return 0;
}