#include <stdio.h>

int main ()
{
    long int Alice_account, Alice_salary_year = 3600000, mortgage = 64000000, house = 14000000, waste_Alice_year = 1200000, house_cost = 0;
    long int Bob_account, Bob_salary_year = 3600000, waste_Bob_year = 1200000, rent_year = 600000;
    long int sum_waste_Alice = 0, sum_waste_Bob = 0, sum_salary_ALice = 0, sum_salary_Bob = 0;
    int cat = 6000, sum_cat = 0;
    int year = 2024;
    int month = 9;

    while (month <= 12 && year <= 2054){
        month++;
        if (month == 12) {
            year = year + 1;
            month = 1;
        }
        if (year == 2040 && month == 6) {
            sum_cat = cat * 162;
        }
    }

    for (int n = 0; n < 30; n++)
    {
        waste_Alice_year = waste_Alice_year * 1.08; //Alice
        sum_waste_Alice = sum_waste_Alice + waste_Alice_year;
        Alice_salary_year = Alice_salary_year * 1.08;
        sum_salary_ALice = sum_salary_ALice + Alice_salary_year;
        house = house * 1.08;
        house_cost = house_cost + house;
        waste_Bob_year = waste_Bob_year * 1.08; //Bob
        rent_year = rent_year * 1.08;
        sum_waste_Bob = sum_waste_Bob + waste_Bob_year + rent_year;
        Bob_salary_year = Bob_salary_year * 1.08;
        sum_salary_Bob = sum_salary_Bob + Bob_salary_year;
    }

    Alice_account = sum_salary_ALice + house_cost - sum_waste_Alice - mortgage;
    Bob_account = sum_salary_Bob - sum_waste_Bob - sum_cat;

    if ( Alice_account >= Bob_account) {
        printf("Alice is richer on ");
        printf("%ld\n", Alice_account - Bob_account);
    }
    else {
        printf("Bob is richer on ");
        printf("%ld\n", Bob_account - Alice_account);
    }

    return 0;
}

