#include <stdio.h>

    int startcap_Alice = 1000000;
    int vznos_ipoteka = 1000000;
    float stavka_ipoteka = 1.22;
    int another_trati_Alice = 35000;
    int kvartira_Alice = 8000000;
    int zp_Alice = 200000;
    int pay_ipoteka = 116971, 31
    float Alice.account = 0;


    float month_year = 9;
    int year = 2024;
    float inflation = 1,09;

    int kvartira_Bob = 25000; 
    int another_trati_Bob = 30000;
    int zp_Bob = 200000;
    int vklad_Bob = 1000000;
    float stavka_vklad = 1.20;
    float Bob.account = 0;


void next_year(){
    if month_year = 13 {
        year ++
        month = 1
    }


    void pay_month_Alice()
    {
        while (year <= 2054)
        {
            Alice.account += zp_Alice;
            Alice.account -= another_trati_Alice + pay_ipoteka;
            month++;
        }
    }
    void inflation_Alice()
    {
        zp_Alice *= 1.07;
        another_trati_Alice *= 1.09;
        kvartira_Alice *= 1.08;
    }

    
    void pay_month_Bob()
    {
        while (year <= 2054)
        {
            Bob.account += zp_Bob;
            Bob.account -= another_trati_Bob + kvartira_Bob;
            month++;
        }
        if (year = 2054)
        {
            Bob.account += stavka_vklad * 30;
        }
    }


void end()
{
    if (year == 2054 && month == 10)
    {
        printf('Bob.account = %d /n')
            printf('Alice.account = %d /n')
    }
      
}
   
