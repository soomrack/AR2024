#include <stdio.h>
#include <cmath>
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))
float infliation = 1.09,index_salary = 1.09;
int bob_end,alice_end;
struct person{
int salary;
int name;
int bank;
};

int stratAlice(float infliation,float pay,int salary,float index_salary,
float food,float n, float price)
{
    float networth = 0;
    for(int i=0; i<n; i++){
        networth = networth+(12*((salary*index_salary)-food*infliation - pay));
    }
    networth = networth + pow(price,n);
    return(networth);

}
int stratBOB(int bank, float bank_percents, float infliation,float pay,
int salary,float index_salary,float food,float n)
{
    float networth;
    for(int i=0; i<n; i++){
            bank = bank*bank_percents;
            networth = 12*((salary*index_salary)-food*infliation - pay);
            bank = bank + networth;
            networth = 0;
        }
        return(networth+bank);

    
}

int main() 
{
printf("hello");
person bob;
bob.salary = 200e3;
bob.bank = 1e6;
person alice;
alice.salary = 200e3;

alice_end = stratAlice(infliation,150e3,alice.salary,index_salary,50000,30,13e6);
bob_end = stratBOB(bob.bank, 1.2, infliation,30000,bob.salary,index_salary,50000,30);
printf("\nAlice ""%i ", alice_end );
printf("\nBob ""%i ", bob_end );

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



