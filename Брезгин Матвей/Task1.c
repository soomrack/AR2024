#include <stdio.h>
int main() {
    typedef long long int Money;
    Money zp2 = 200000;
    Money zp1 = 200000;
    int god1=0; //cчётчик лет для Bob
    int god2=0;//cчётчик лет для Alice
    Money bank = 1000000; // вклад боба
    Money food = 35000; // месячные расходы
    Money kv = 90000; //квартира
    Money k = 1;
    //BOB
    while (god1!=29){
        
        bank= bank + (zp1 - (kv + food))*12;
        god1+=1;
        zp1 = zp1*1.09; // индексация
        food = food*1.14; // инфляция
        kv=kv*1.14;  // инфляция
        bank=bank*1.19; // проценты ыклада 
        k+=1;
        printf("%lld\n", bank);
    }
    //Alice
    //while (god1!=31){



    
    printf("%lld\n", bank);
    printf("%lld\n", k);
    return 0;
}


