#include <stdio.h>
#include <cmath>
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))
float infliation = 1.09,index_salary = 1.09, loan_percents = 0.18, 
deposit_percents = 1.16, pay_for_flat = 30e3;
long long int bob_end,alice_end, years = 30,price_apartment = 10e6;
struct person{
int salary;
int name;
long long int bank;
};
int pay_for_loan(int price_apartment, int years, float loan_percents){
    // Преобразование годовой процентной ставки в месячную и в десятичный формат
    double monthlyRate = loan_percents / 12;
    // Общее количество платежей
    int totalPayments = years * 12;
    int monthlyPayment = (price_apartment * monthlyRate * pow(1 + monthlyRate, totalPayments))/(pow(1 + monthlyRate, totalPayments) - 1);
    printf("\n %i",monthlyPayment);
    return(monthlyPayment);
    }
long long int stratAlice(float infliation,int pay,int salary,float index_salary,
float food,int number_of_years, int price_apartment){
    if(salary<pay+food){
        printf("\n Alice salary is too low"); 
        return(0); 
    }
    long long int networth = 0;
    for(int i=0; i<number_of_years; i++){
        networth = networth+(12*((salary*index_salary)-food*infliation - pay));
    }
    networth = networth + price_apartment * pow(infliation,number_of_years);
    return(networth);
}

long long int stratBOB(long long int bank, float bank_percents, float infliation,float pay,
int salary,float index_salary,float food,float number_of_years){
    if(salary<pay+food){
        printf("\n Bob salary is too low"); 
        return(0); 
    }
    float networth;
    for(int i=0; i<number_of_years; i++){
            bank = bank*bank_percents;
            networth = 12*((salary*index_salary)-food*infliation - pay);
            bank = bank + networth;
            networth = 0;
        }
        return(bank);
}

int main() 
{
person bob;
bob.salary = 200e3;
bob.bank = 1e6;

person alice;
alice.salary = 200e3;
alice.bank = 1e6;

int loan_price =  price_apartment - alice.bank;

alice_end = stratAlice(infliation,pay_for_loan(loan_price,years,loan_percents),alice.salary,index_salary,50000,years,price_apartment);
bob_end = stratBOB(bob.bank, deposit_percents, infliation,pay_for_flat,bob.salary,index_salary,50000,years);
printf("\nAlice ""%lli ", alice_end );
printf("\nBob ""%lli ", bob_end );

//костыль для оценки стратегий
float b0b = bob_end;
float all = alice_end;
if (__min(all,b0b)/__max(all,b0b)>0.95) printf("\nboth of these strategics are good");
else
{
if (all>b0b) printf("\nAlice strategic is better");
else printf("\nBob strategic is better");
}
}