#include <stdio.h>
#include <cmath>
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))
float infliation = 1.09,index_salary = 1.03, deposit_percents = 1.16,
loan_percents = 18;
long long int bob_end_simulation, alice_end_simulation,
price_apartment = 95*100*1000;
int years = 30;

struct person
{
int salary;
int food_expenses;
long long int money;
int pay_for_flat_loan;
int credit_pay;
};
int loan_payment_calculation(struct person user){
    // Преобразование годовой процентной ставки в месячную и в десятичный формат
    double monthlyRate = loan_percents / (12*100);
    // Общее количество платежей
    int totalPayments = years * 12;
    int monthlyPayment = ((price_apartment - user.money) * monthlyRate * pow(1 + monthlyRate, totalPayments))/(pow(1 + monthlyRate, totalPayments) - 1);
    //printf("\n %i",monthlyPayment);
    return(monthlyPayment);
    }

int alice_simulation(struct person user){
    if(user.salary<user.credit_pay+user.food_expenses)
    {
        printf("\n Alice salary is too low"); 
        return(0); 
    }
    
    for(int year=0; year<years; year++)
    {
        user.money = user.money+(12*((user.salary*index_salary)-user.food_expenses*infliation - user.credit_pay));
    }
    user.money = user.money + price_apartment * pow(infliation,years);
    printf("\nAlice ""%lli ", user.money );
}

int bob_simulation(struct person user)
{
    if(user.salary<user.pay_for_flat_loan+user.food_expenses)
    {
        printf("\n Bob salary is too low"); 
        return(0); 
    }
    float networth;
    for(int year=0; year<years; year++)
    {
            user.money = user.money*deposit_percents;
            networth = 12*((user.salary*index_salary)-((user.food_expenses+user.pay_for_flat_loan)*infliation));
            user.money = user.money + networth;
            networth = 0;
        }
    printf("\nBob ""%lli ", user.money);
}

int main() 
{
person bob;
bob.salary = 200*1000;
bob.money = 1000*1000;
bob.food_expenses = 50*1000;
bob.pay_for_flat_loan = 30*1000;

person alice;
alice.salary = 200*1000;
alice.money = 1000*1000;
alice.food_expenses = 50*1000;
alice.credit_pay = loan_payment_calculation(person(alice));


alice_simulation(person(alice));
bob_simulation(person(bob));


//костыль для оценки стратегий
// float b0b = bob_end_simulation;
// float all = alice_end_simulation;
// if (__min(all,b0b)/__max(all,b0b)>0.95) printf("\nboth of these strategics are good");
// else
// {
// if (all>b0b) printf("\nAlice strategic is better");
// else printf("\nBob strategic is better");
// }
}