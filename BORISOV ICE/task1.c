#include <stdio.h>


typedef long long int Money;


struct Mortgage {
    double rate;
    Money credit;
    Money pay;
    Money month_pay;
};


struct Bank {
    Money vklad;
    Money month_pay;
};


struct Individual {
    Money zarplata;
    Money rashod;
    Money status;
    Money kvartira;
    Money rubles; 
    struct Mortgage mortgage;
    struct Bank bank;
};


struct Individual Alice;
struct Individual Robert;  


void Alice_money() {
    Alice.status = 0;
    Alice.zarplata = 200*1000;
    Alice.rashod = 50*1000;
    Alice.rubles = 0;

    Alice.mortgage.rate = 0.17;
    Alice.mortgage.credit = 13*1000*1000;
    Alice.mortgage.month_pay = 150*1000;
}


void Alice_mortgage() {
    Alice.status -= Alice.mortgage.month_pay;
}


void Alice_zarplata(const int month, const int year) {
    if(month == 12) {
        Alice.status += Alice.zarplata;
    }
    if(month == 1) {
        Alice.zarplata *= 1.09;
    }
    Alice.status += Alice.zarplata;
}


void Alice_print() {
    if (Alice.status > Robert.status) {
        printf ("Alice has more money than Robert on %lld\n", Alice.status - Robert.status);
    }

    if (Alice.status < Robert.status) {
        printf ("Robert has more money than Alice on %lld\n", Robert.status - Alice.status);
    }

    printf ("Alice capital = %lld \n", Alice.status);
}


void Robert_money() {
    Robert.status = 0;
    Robert.zarplata = 200*1000;
    Robert.rashod = 50*1000;
    Robert.kvartira = 30*1000; 
    Robert.rubles = 0;
    Robert.bank.month_pay = 120*1000;
}


void Robert_zarplata(const int month, const int year) {
    if(month == 12) {
        Robert.status += Robert.zarplata;
    }
    if(month == 1) {
        Robert.zarplata *= 1.09;
    }
    Robert.status += Robert.zarplata;
}


void Robert_bank(int deposit) {
    int month = 9;
    int year = 2024;

    while( !((month == 9) && (year == 2054)) ) {

    deposit = 20; 
    Robert.status -= Robert.bank.month_pay;
    Robert.bank.vklad = ((deposit/12)*0.01+1);
    Robert.rubles += (Robert.zarplata - Robert.bank.month_pay - Robert.rashod - Robert.kvartira);
    Robert.status += (Robert.bank.vklad + Robert.rubles);
    }
}


void Robert_print() {
    printf ("Robert capital = %lld \n", Robert.status);

}


void simulation() {
    int month = 9;
    int year = 2024;

    while( !((month == 9) && (year == 2054)) ) {
        
        Alice_zarplata(month, year);
        Alice_mortgage();
        
        Robert_zarplata(month, year);
        Robert_kvartira(year);

        month++;
        if(month == 13) {
            month = 1;
            year++;
        }
    }
    
}


int main() {
    Alice_money();

    Robert_money();

    simulation();

    Alice_print();

    Robert_print();
    return 1;
}
