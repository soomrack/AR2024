#include <stdio.h>
#include <cmath>
#include <algorithm>
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))

//start networth = 1000000 price of apartment = 13000000

int stratAlice(float networth, float infliation,float pay,float salary,float index_salary,float food,float n, float price)
{
    networth = 0;
    for(int i=0; i<n; i++)
    {
        
        networth = networth + (12*((salary*index_salary)-food*infliation - pay));
        

    }
    networth = networth + pow(price,n);    return(networth);

}
int stratBOB(float bank, float bank_percents, float infliation,float pay,float salary,float index_salary,float food,float n)
{
float networth;
for(int i=0; i<n; i++)
    {
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

int bob,al;


al = stratAlice(0,1.09,150000,200000,1.09,50000,30,13e6);


bob = stratBOB(1e6, 1.2, 1.09,30000,200000,1.09,50000,30);
printf("\nAlice ""%i ", al );
printf("\nBob ""%i ", bob );
//костыль для оценки стратегий
float s = bob/al;
float b0b = bob;
float all = al;
if (__min(all,b0b)/__max(all,b0b)>0.95) printf("\nboth of these strategics are good");

}

