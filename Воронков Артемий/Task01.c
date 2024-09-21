#include <stdio.h>
#include <locale.h>



    typedef long long int Money;
    typedef int Time;
    typedef int Percent;
    Time year = 2024;
    Time month = 9;
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
void count_Alice()
{
    Time year = 2024;
    Time month = 9;
  for (year=2024; year <= 2054; month++) {
    Alice.account = Alice.account + Alice.salary - Alice.clothes - Alice.food - Alice.other_expenses - Alice.payment;
    if(month % 12 == 0){
           // printf("%lld  %lld\n ",Alice.account, year);
        month = 1;
        year++;
        Alice.salary *= 1.2;
        Alice.clothes *= 1.2;
        Alice.food *= 1.2;
        Alice.other_expenses *= 1.2;



        }
    }
}

void count_Bob()
{
    Time year = 2024;
    Time month = 9;
    for (year=2024; year <= 2054; month++) {
    Bob.account += Bob.salary - Bob.clothes - Bob.food - Bob.other_expenses - Bob.payment;
    if(month % 12 == 0){
            // printf("%lld  %lld\n ",Bob.account, year);
        month =1;
        year++;
        Bob.salary *= 1.2;
        Bob.clothes *= 1.2;
        Bob.food *= 1.2;
        Bob.other_expenses *= 1.2;
        }
}}
void print()
{
    setlocale(LC_ALL, "Russian");
    if(Alice.account + 14000000 > Bob.account)
        {
    printf("%lld al на столько больше денег у Alice \n ",(Alice.account + 14000000) - Bob.account );
        }
    else
        {
         printf("%lld  на столько больше денег у Bob \n ",Bob.account - (Alice.account + 14000000) );
    }
}
    int main()
    {
    count_Alice();
    count_Bob();
    print();
return 0;
   }
