#include <stdio.h>
#include <math.h>

#define YEARS 30
#define MONTHSINYEAR 12

int main() {
    double inflation_rate = 0.09;  
    double salary_increase_rate = 0.09;  
    double mortgage_rate = 0.17;  
    double bank_rate = 0.20;  
    double initial_capital = 1000000;  
    double mortgage_amount = 13000000 - initial_capital;  
    double monthly_mortgage_payment;
    double bob_rent = 30000;  

    double alice_salary = 200000;  
    double bob_salary = 200000;    
    double alice_needs = 80000;    
    double bob_needs = 80000;      

    double monthly_interest = mortgage_rate / MONTHSINYEAR;
    int total_months = YEARS * MONTHSINYEAR;
    monthly_mortgage_payment = mortgage_amount * 
                               (monthly_interest * pow(1 + monthly_interest, total_months)) /
                               (pow(1 + monthly_interest, total_months) - 1);

    double alice_bank_balance = 0;
    double bob_bank_balance = initial_capital;

    double alice_total_expenses = 0;
    double bob_total_expenses = 0;

    for (int year = 0; year < YEARS; year++) {
        for (int month = 0; month < MONTHSINYEAR; month++) {
         
            alice_total_expenses += alice_needs + monthly_mortgage_payment;
            double alice_savings = alice_salary - alice_needs - monthly_mortgage_payment;
            if (alice_savings > 0) {
                alice_bank_balance += alice_savings;
                alice_bank_balance *= (1 + bank_rate / MONTHSINYEAR);
            }

            bob_total_expenses += bob_needs + bob_rent;
            double bob_savings = bob_salary - bob_needs - bob_rent;
            if (bob_savings > 0) {
                bob_bank_balance += bob_savings;
                bob_bank_balance *= (1 + bank_rate / MONTHSINYEAR);
            }
        }

        alice_salary *= (1 + salary_increase_rate);
        bob_salary *= (1 + salary_increase_rate);
        alice_needs *= (1 + inflation_rate);
        bob_needs *= (1 + inflation_rate);
    }

    printf("Итоговые расходы Алисы за 30 лет: %.2f рублей\n", alice_total_expenses);
    printf("Итоговые расходы Боба за 30 лет: %.2f рублей\n", bob_total_expenses);
    printf("Сбережения Алисы в банке: %.2f рублей\n", alice_bank_balance);
    printf("Сбережения Боба в банке: %.2f рублей\n", bob_bank_balance);

    return 0;
}
