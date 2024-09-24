#include <stdio.h>
#include <locale.h>


    typedef long long int Money;//RUB
    typedef int Time;
    Time year = 2024;
    Time month = 9;
    Money deposite = 1000000;
    struct Person{

         Money food;
         Money clothes;
         Money other_expenses;
         Money payment;
         Money salary;
         Money account;

    };

    struct Person Bob =
    {
    .food = 20 * 1000 ,
    .clothes = 20 * 1000 ,
    .other_expenses = 30 * 1000 ,
    .payment = 30 * 1000,
    .salary = 300 * 1000 ,
    .account = 0

       };

    struct Person Alice =
    {
    .food = 20 * 1000 ,
    .clothes = 20 * 1000 ,
    .other_expenses = 30 * 1000,
    .payment = 186 * 1000 ,
    .salary = 300 * 1000,
    .account = 0
       };


    void simulation()
       {
        year = 2024;
        month = 9;
        while (year != 2054 || month != 9)
        {
            month++;
            count_Alice();
            count_Bob();
            if(month % 12 == 0){
                    Alice_salary(year, month);
                    Alice_clothes(year, month);
                    Alice_food(year, month);
                    Alice_other_expenses(year, month);


                    Bob_salary(year, month);
                    Bob_clothes(year, month);
                    Bob_food(year, month);
                    Bob_other_expenses(year, month);
                    //printf("%lld %lld %lld\n ",Alice.account, Bob.account, year); // DEBUG
            }
            if(month % 12 == 0){
                    year ++;
                    month = 1;
                }
            }
       }
    void count_Alice()
{
    Alice.account =
    Alice.account + Alice.salary - Alice.clothes -
    Alice.food - Alice.other_expenses - Alice.payment;
}


    void Alice_salary(Time year, Time month)
{
    Alice.salary *= 1.2;
}


    void Alice_clothes(Time year, Time month)
{
    Alice.clothes *= 1.2;
}


    void Alice_food(Time year, Time month)
{
    Alice.food *= 1.2;
}


    void Alice_other_expenses(Time year, Time month)
{
    Alice.other_expenses *= 1.2;
}


    void count_Bob()
{

    Bob.account =
    Bob.account + Bob.salary - Bob.clothes -
    Bob.food - Bob.other_expenses - Bob.payment;
}


    void Bob_salary(Time year, Time month)
{
    Bob.salary *= 1.2;
}


    void Bob_clothes(Time year, Time month)
{
    Bob.clothes *= 1.2;
}


    void Bob_food(Time year, Time month)
{
    Bob.food *= 1.2;
}


    void Bob_other_expenses(Time year, Time month)
{
    Bob.other_expenses *= 1.2;
}


    void Bob_deposite()
{
    deposite *= 1.05;
}


    void print()
{
    setlocale(LC_ALL, "Russian");
    if(Alice.account + 14000000 > Bob.account + deposite)
        {
    printf("%lld  на столько больше денег у Alice \n ",(Alice.account + 14000000) - (Bob.account + deposite));
        }

    else
        {
         printf("%lld  на столько больше денег у Bob \n ",(Bob.account + deposite) - (Alice.account + 14000000) );
    }
}
    int main()
    {
    simulation();
    print();
return 0;
   }
