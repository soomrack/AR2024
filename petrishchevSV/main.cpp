#include <stdio.h>
#include <cmath>
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))
float infliation = 1.09,index_salary = 1.03, deposit_percents = 1.16;
long long int bob_end_simulation, alice_end_simulation;
int years = 30,price_apartment = 95e5, loan_percents = 18;

struct person{
int salary;
int food_expenses;
long long int bank;
int pay_for_flat_loan;
int credit_pay;
};
int loan_payment_calculation(struct person user){
    // Преобразование годовой процентной ставки в месячную и в десятичный формат

    double monthlyRate = loan_percents / (12*100);
    // Общее количество платежей
    int totalPayments = years * 12;
    int monthlyPayment = ((price_apartment - user.bank) * monthlyRate * pow(1 + monthlyRate, totalPayments))/(pow(1 + monthlyRate, totalPayments) - 1);
    printf("\n %i",monthlyPayment);
    return(monthlyPayment);
    }
long long int alice_simulation(struct person user){
    if(user.salary<user.credit_pay+user.food_expenses){
        printf("\n Alice salary is too low"); 
        return(0); 
    }
    long long int networth = 0;
    for(int i=0; i<years; i++){
        networth = networth+(12*((user.salary*index_salary)-user.food_expenses*infliation - user.credit_pay));
    }
    networth = networth + price_apartment * pow(infliation,years);
    return(networth);
}

long long int bob_simulation(struct person user){
    if(user.salary<user.pay_for_flat_loan+user.food_expenses){
        printf("\n Bob salary is too low"); 
        return(0); 
    }
    float networth;
    for(int i=0; i<years; i++){
            user.bank = user.bank*deposit_percents;
            networth = 12*((user.salary*index_salary)-((user.food_expenses+user.pay_for_flat_loan)*infliation));
            user.bank = user.bank + networth;
            networth = 0;
        }
        return(user.bank);
}

int main() 
{
person bob;
bob.salary = 200e3;
bob.bank = 1e6;
bob.food_expenses = 50e3;
bob.pay_for_flat_loan = 30e3;

person alice;
alice.salary = 200e3;
alice.bank = 1e6;
alice.food_expenses = 50e3;

alice.credit_pay = loan_payment_calculation(person(alice));
alice_end_simulation = alice_simulation(person(alice));
bob_end_simulation = bob_simulation(person(bob));
printf("\nAlice ""%lli ", alice_end_simulation );
printf("\nBob ""%lli ", bob_end_simulation );

//костыль для оценки стратегий
float b0b = bob_end_simulation;
float all = alice_end_simulation;
if (__min(all,b0b)/__max(all,b0b)>0.95) printf("\nboth of these strategics are good");
else
{
if (all>b0b) printf("\nAlice strategic is better");
else printf("\nBob strategic is better");
}
}