#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

typedef long long int Money;//RUB


typedef int Time;
    Time year = 2024;
    Time month = 9;

    Money deposite = 1000000;
bool cat, car;

struct Person{
    Money food;
    Money clothes;
    Money other_expenses;
    Money payment;
    Money salary;
    Money account;};


struct Animal{
    Money feed;
    Money vet;
    Time age;};


struct Car{
    Money fuel;
    Money maintenance;
    Money tax;
    Time age;};


struct Car Audi ={
    .fuel = 12 * 1000,
    .maintenance = 12 * 1000,
    .tax = 2 * 1000,
    .age = 0};


struct Animal Cat ={
    .feed = 7 * 1000,
    .vet = 5 * 1000,
    .age = 0};


struct Person Bob ={
    .food = 20 * 1000 ,
    .clothes = 20 * 1000 ,
    .other_expenses = 30 * 1000 ,
    .payment = 30 * 1000,
    .salary = 300 * 1000 ,
    .account = 0};


struct Person Alice =
    {
    .food = 20 * 1000 ,
    .clothes = 20 * 1000 ,
    .other_expenses = 30 * 1000,
    .payment = 186 * 1000 ,
    .salary = 300 * 1000,
    .account = 0};


void simulation(){
    while (year != 2054 || month != 9){
            Alice_salary(year, month);
            Alice_clothes(year, month);
            Alice_food(year, month);
            Alice_other_expenses(year, month);
            Alice_payment();
            Alice_cat(year, month);


            Bob_salary(year, month);
            Bob_clothes(year, month);
            Bob_food(year, month);
            Bob_other_expenses(year, month);
            Bob_deposite();
            Bob_car(year, month);

            month++;


            if (month == 13) {month = 1; year ++;}
    }
}


void Alice_cat(Time const year, Time const month){

    if (year == 2030 && month == 1){
        cat = true;}

    while (cat == true){
        Alice.account -= Cat.feed;
        Alice.account -= Cat.vet;
        Cat.age ++;
        if(Cat.age == 15) {cat = false;}
        }
}





void Alice_salary(Time const year, Time const month){
    Alice.account = Alice.account + Alice.salary;
    if(month == 10){
    Alice.salary = Alice.salary * 1.2;}
}


void Alice_clothes(Time const year, Time const month){
    Alice.account = Alice.account - Alice.clothes;
    if (month % 12 == 0){
    Alice.clothes *= 1.2;}
}


void Alice_food(Time const year, Time const month){
    Alice.account = Alice.account - Alice.food;
    if (month == 12){
    Alice.food *= 1.2;}
}


void Alice_other_expenses(Time const year, Time const month){
    Alice.account = Alice.account - Alice.other_expenses;
    if (month % 12 == 0){
    Alice.other_expenses *= 1.2;}
}


void Alice_payment(){
    Alice.account -= Alice.payment;
}


void Bob_salary(Time const year, Time const month){
    Bob.account = Bob.account + Bob.salary;
    if (month == 12){
    Bob.salary *= 1.2;}
}


void Bob_clothes(Time const year, Time const month){
    Bob.account = Bob.account - Bob.clothes;
    if (month == 12){
    Bob.clothes *= 1.2;}
}


void Bob_food(Time const year, Time const month){
    Bob.account = Bob.account - Bob.food;
    if (month == 12){
    Bob.food *= 1.2;}
}


void Bob_other_expenses(Time const year, const month){
    Bob.account = Bob.account - Bob.other_expenses;
    if (month == 12){
    Bob.other_expenses *= 1.2;}
}


void Bob_car(Time const year, Time const month){

    if (year == 2031 && month == 1){
        car = true;}

    while (car == true){
            int a=0;
        Bob.account = Bob.account - Audi.fuel;
        Bob.account = Bob.account - Audi.maintenance;
        Bob.account = Bob.account - Audi.tax;
        Audi.age ++;
        if(Audi.age == 7) {car = false;}}
}


void Bob_deposite(){
    if (month == 12){
    deposite *= 1.05;}
}


void print(){
    setlocale(LC_ALL, "Russian");
    if(Alice.account + 14000000 > Bob.account + deposite){

    printf("%lld  на столько больше денег у Alice \n ",(Alice.account + 14000000) - (Bob.account + deposite));
    }

    else
        {
         printf("%lld  на столько больше денег у Bob \n ",(Bob.account + deposite) - (Alice.account + 14000000) );}
}
int main()
    {
    simulation();
    print();
return 0;
   }
