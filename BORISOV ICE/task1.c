#include <stdio.h>

typedef long long int MONEY;

struct IPOTEKA
{
    double STAVKA;
    MONEY KREDIT;
    MONEY MESYAC_PLATEZH_ALICE;
};

struct CHELOVEK
{
    MONEY ZARPLATA;
    MONEY SKOLKO_DENEG;
    MONEY RASHODI;
    MONEY MASHINA;
    MONEY DENGI;
    MONEY KVARTIRA;
    struct IPOTEKA Ipoteka;
    struct VKLAD Vklad;
};

struct VKLAD
{
    MONEY VKLADIK;    
    MONEY MESYAC_PLATEZH_BOB;
};

struct CHELOVEK ALICE;

struct CHELOVEK BOB;

void alice_ipoteka()
{
    ALICE.SKOLKO_DENEG -= ALICE.Ipoteka.MESYAC_PLATEZH_ALICE;
}

void alice_dengi()
{
    ALICE.SKOLKO_DENEG = 0;
    ALICE.ZARPLATA = 200*1000;
    ALICE.RASHODI = 50*1000;

    ALICE.Ipoteka.STAVKA = 0.17;
    ALICE.Ipoteka.KREDIT = 13*1000*1000;
    ALICE.Ipoteka.MESYAC_PLATEZH_ALICE = 150*1000;
}

void alice_zarplata(const int month, const int year)
{
    if(month == 1) {
        ALICE.SKOLKO_DENEG += ALICE.ZARPLATA;
    }
    if(month==12){
        ALICE.ZARPLATA *= 1.09;
    }
}

void bob_dengi(){
    BOB.SKOLKO_DENEG = 0;
    BOB.ZARPLATA = 200*1000;
    BOB.RASHODI = 50*1000;
    BOB.MASHINA = 10*1000;
    BOB.Vklad.MESYAC_PLATEZH_BOB = 120*10000;
}

void bob_zarplata(const int month, const int year)
{
    if(month == 12) {
        BOB.SKOLKO_DENEG += BOB.ZARPLATA;
    }
    if(month == 1) {
        BOB.ZARPLATA *= 1.09;
    }
    BOB.SKOLKO_DENEG += BOB.ZARPLATA;
}

void Bob_vklad(int deposit)
{
    int month = 9;
    int year = 2024;

    while ( !((month == 9) && (year == 2054)) ) {
        deposit = 20;
        BOB.Vklad.VKLADIK = ((deposit/12)*0.01+1);
        BOB.SKOLKO_DENEG -= BOB.Vklad.MESYAC_PLATEZH_BOB;
        BOB.DENGI += (BOB.ZARPLATA -BOB.Vklad.MESYAC_PLATEZH_BOB - BOB.RASHODI - BOB.MASHINA);
        BOB.SKOLKO_DENEG += (BOB.Vklad.VKLADIK + BOB.DENGI);
    }
}

void bob_mashina(int year, int month)
{   
    if (year == 2031 && month == 3 && BOB.SKOLKO_DENEG == 15 * 1000 * 1000){
        BOB.SKOLKO_DENEG -= 15 * 1000 * 1000;
    }
    else if(year >= 2031 && month > 3){
        BOB.SKOLKO_DENEG -= 15 * 1000;
    }
    else if(month == 9){
        BOB.SKOLKO_DENEG -= 50 * 1000;
    }
}

void bob_kvartira(int year)
{
    year = 2024;
    if (year== 2034 || year == 2044 || year == 2054) {
        BOB.KVARTIRA += 1000;
    }
} 

void simulation()
{
    int month = 9;
    int year = 2024;

    while( !((month == 9) && (year == 2054)) ) {
        
        alice_zarplata(month, year);
        alice_ipoteka();
        
        bob_zarplata(month, year);
        bob_kvartira(year);

        month++;
        if(month == 13) {
            month = 1;
            year++;
        }
    }
}

void alice_print()
{
    printf ("ALICE = %lld \n", ALICE.SKOLKO_DENEG);
}

void bob_print()
{
    printf ("BOB = %lld \n", BOB.SKOLKO_DENEG);
}

int main()
{
    alice_dengi();

    bob_dengi();

    simulation();

    alice_print();

    bob_print();
    return 1;
}
