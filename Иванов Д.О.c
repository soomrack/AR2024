#include<stdio.h>
#include <stdlib.h>
#include <ctime>
typedef long long int Money;


struct Cat {
    Money food;
    int with_alice;
};

struct Car//у Алисы уже есть папина машина
{
    Money benzin;//в среднем расход 300 литров в месяц(на 2025 год 1л=65рубей)
    Money remont;//машина может ломаться раз в месяц на 30 тысяч с шансом 1%
    Money moyka;//Алиса тратит на мойку 5000 рублей в месяц
};

struct Otpusk 
{
    Money bileti;//пусть она едет в плацкарте
    Money kurort;//пусть она поехала в Сочи
};

struct Ipoteka 
{
    Money flat;
    Money vznos;
    Money mes_plata;
};

struct Vklad {
    Money den_vklad;
    double proc_vklad;
};

struct Kvartira{
     Money kvart_plata;
};
struct Chel 
{
    Money zarplata;
    Money account;
    Money food;
    Money rashodi;
    Money kvart_plata;
    struct Ipoteka ipoteka;
    struct Cat cat;
    struct Car car;
    struct Otpusk otpusk;
    struct Vklad vklad;
    struct Kvartira kvartira;
};

struct Chel alice; 
struct Chel bob;

void alice_init()
{
    //база
    alice.account = 1000 * 1000;
    alice.zarplata = 200 * 1000;
    alice.food = 40 * 1000;
    alice.rashodi = 70 * 1000;
    //ипотека
    alice.ipoteka.vznos = 1000 * 1000;
    alice.ipoteka.flat = 14000 * 1000;
    alice.ipoteka.mes_plata = 100 * 1000;  
    alice.account -= alice.ipoteka.vznos;
    //кот
    alice.cat.food = 5000;
    alice.cat.with_alice = 0;
    //машина
    alice.car.benzin = 300 * 65;
    alice.car.remont = 30 * 1000;
    alice.car.moyka = 5000;
    //отпуск
    alice.otpusk.bileti = 10 * 1000;
    alice.otpusk.kurort = 15 * 1000;
    //вклад
    alice.vklad.den_vklad = 0;
    alice.vklad.proc_vklad = 0.19;
}

void alice_ipoteka(const int month, const int year)
{
    alice.account -= alice.ipoteka.mes_plata;
    if(month == 1){
        alice.ipoteka.flat*=1.08;
        alice.ipoteka.mes_plata*=1.09;
    };
    if((month == 11) && (year == 2024+30)) {
        alice.account+=alice.ipoteka.flat;
    };
}

void alice_food(const int month)
{
    if (month == 1) {
        alice.food *= 1.1;
    }
    alice.account -= alice.food;
}

void alice_rashodi()
{
    
    alice.account -= alice.rashodi;
}

void alice_cat(const int month, const int year)
{
    if ((month == 12) && (year==2026)) {
        alice.account -= 30000;
        alice.cat.with_alice = 1;
    }
    if ((year == 2043) && (month == 3)) {
        alice.cat.with_alice = 0;
        alice.account -= 3000;
    }
    if (month == 1){
        alice.cat.food *= 1.1;
    }
    if (alice.cat.with_alice == 1){
        alice.account -= alice.cat.food ;
    }
}

void alice_car(const int month, const int year)
{
    if (month == 12){
        alice.account-= alice.car.benzin;
    }
    if (month == 1){
        alice.car.benzin *= 1.08;
        alice.car.remont *= 1.08;
    }
    alice.account-=alice.car.moyka;
    int polomka=rand()%100;
    if(polomka == 1){
        alice.account-=alice.car.remont;
        printf("У машины Алисы поломка на %d рублей в %d году.\n",alice.car.remont,year);
    }


}

void alice_otpusk(const int month, const int year)
{
    if ((month == 12) && (year==2030)){
        alice.account-= alice.otpusk.bileti;
        alice.account-= alice.otpusk.kurort;
    }
    if (month == 1){
        alice.otpusk.bileti *= 1.08;
        alice.otpusk.kurort *= 1.08;
    }
    
}

void alice_zarplata(const int month, const int year)
{
    if(month == 12) {
        alice.account += alice.zarplata;//выплата зп
    }
    if(month == 1) {
        alice.zarplata *= 1.07;//индексация
    }
    alice.account += alice.zarplata; 
    
}

void alice_vklad(const int month, const int year)
{
    alice.vklad.den_vklad += alice.account;
    alice.account = 0;
    if((year == 2024+30) && (month==11)){
        alice.account+=alice.vklad.den_vklad;
    };
    if(month == 12){
        alice.vklad.den_vklad *=alice.vklad.proc_vklad;
    };
};

void bob_init()
{
    //база
    bob.account = 1000 * 1000;
    bob.zarplata = 200 * 1000;
    bob.food = 40 * 1000;
    bob.rashodi = 70 * 1000;
    //квартира
    bob.kvart_plata = 100 * 1000;
    //вклад
    bob.vklad.den_vklad = bob.account;
    bob.account = 0;
    bob.vklad.proc_vklad = 1.19;
}

void bob_zarplata(const int month, const int year)
{
    if(month == 12) {
        bob.account += bob.zarplata;//выплата зп
    }
    if(month == 1) {
        bob.zarplata *= 1.07;//индексация
    }
    bob.account += bob.zarplata; 
    
}

void bob_kvartira(const int month, const int year){
    if(month == 1){
        bob.kvart_plata*=1.1;
    }
    bob.account-=bob.kvart_plata;
}

void bob_vklad(const int month, const int year)
{
    bob.vklad.den_vklad += bob.account;
    bob.account = 0;
    if((year == 2024+30) && (month==11)){
        bob.account+=bob.vklad.den_vklad;
    
    };
    if(month == 12){
        bob.vklad.den_vklad *=bob.vklad.proc_vklad;
    };
};

void bob_rashodi(){
    
    bob.account -= bob.rashodi;
}

void bob_food(const int month)
{
    if (month == 1) {
        bob.food *= 1.1;
    }
    bob.account -= bob.food;
}

void alice_print()
{
    printf("У Алисы на счету %lld рублей.\n", alice.account);
}

void bob_print()
{
    printf("У Боба на  счету %lld рублей.\n", bob.account);
}

void simulation()
{
    int month = 9;
    int year = 2024;
    srand ( time(NULL) );
    while( !((month == 12) && (year == 2024 + 30)) ) {
        alice_zarplata(month, year);
        alice_ipoteka(month, year);
        alice_food(month);
        alice_rashodi();  
        alice_cat(month, year);
        alice_car(month, year);
        alice_otpusk(month, year);
        alice_vklad(month, year);
        bob_zarplata(month, year);
        bob_kvartira(month, year);
        bob_vklad(month, year);
        bob_rashodi();
        bob_food(month);
        month++;
        if(month == 13) {
            month = 1;
            year++;
        }
    }
}
void sravnenie(){
    if(bob.account>alice.account){
        printf("У Боба капитал больше, чем у Алисы на %d рублей\n",bob.account-alice.account);
    }
    if(bob.account<alice.account){
        printf("У Алисы капитал больше, чем у Боба на %d рублей\n",alice.account-bob.account);
    }
}
int main()
{
    alice_init();
    bob_init();
    simulation();

    alice_print();
    bob_print();
    sravnenie();
}