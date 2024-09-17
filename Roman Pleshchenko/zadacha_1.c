#include <stdio.h> 
int main(){
    float A_house=14000000.0;
    float A_capital = 0;
    float B_bank = 1000000.0;
    float B_capital = 0;
    float A_credit=185337.79; // ануитетный платеж 
    float A_savemoney = 0; //Сумма, которую может отложить Alice после всех трат
    float B_savemoney = 0; // Сумма, которую может отложить Bob после всех трат 

    float A_zp = 300000.0;
    float B_zp=300000.0;
    float A_costs = 60000.0;
    float B_costs = 85000.0;
    int year = 2024;
    int month = 9 ;
    float infl = 9.0;
    float dep = 20.0;
    while( year != 2054) {
        month ++;
        if (year == 2054 && month == 10){
            break;
        }
        if (month == 13){
            month = 1; 
            year ++;
            A_zp= A_zp*(1+0.01*infl);
            B_zp= B_zp*(1+0.01*infl);
            A_costs= A_costs*(1+0.01*infl);
            B_costs= B_costs*(1+0.01*infl);
            A_house = A_house*(1+0.01*infl);
        }
        //Аlice
        A_savemoney = A_savemoney + (A_zp - A_credit - A_costs);
        A_capital = A_house + A_savemoney;
        // Bob
        B_savemoney =B_savemoney + (B_zp - B_costs);
        B_bank= B_bank * ((dep/12)*0.01+1);
        B_capital = B_bank + B_savemoney;
    }
    if (B_capital>A_capital){
        printf("Bob richer  = %f \n ", B_capital - A_capital);
    }
    if (B_capital < A_capital){
        printf("Alice richer =  %f \n ", A_capital - B_capital);
    }
    if (B_capital == A_capital){
        printf("Bob and Alice have the same capital");
    }
    printf("Bob's capital = %f \n", B_capital);
    printf("Alice's capital = %f \n", A_capital);
    return 0;
    
}
