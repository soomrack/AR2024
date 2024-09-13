#include <math.h>
#include <stdio.h>
#include <stdbool.h>

// consts
const long start_alice_capital = 1000000, start_bob_capital = 1000000;
const int salary_alice = 200000, salary_bob = 200000;
const long flat_cost = 21000000, flat_rent_month_pay = 40000;
const int hcs_month_pay = 6000, eat_month_pay = 10000, other_month_pay = 3000;
const bool deposit_bool = true;
const float percent_deposit_year = 16;
const short num_deposit_year = 30;
const short num_mortgage_years = 30;
const float percent_rate_year = 6;
const long first_mortgage_pay = 1000000;

// func
double mortgage() {
    float percent_rate_month = percent_rate_year / 12 / 100;
    float general_rate = pow((1 + percent_rate_month), num_mortgage_years * 12);
    return (flat_cost - first_mortgage_pay) * percent_rate_month * general_rate / (general_rate - 1);
}

double deposit(double month_pay_bob) {
    double percent_month = percent_deposit_year / 12 / 100;
    double new_sum_deposit = start_bob_capital;

    for (int i = 1; i <= num_deposit_year * 12; i++) {
        if (deposit_bool) {
            new_sum_deposit += percent_month * new_sum_deposit + salary_bob - month_pay_bob;
        } else {
            new_sum_deposit += salary_bob - month_pay_bob;
        }
    }

    return new_sum_deposit;
}

void sum_month_pay(double month_pay[2]) {
    double mortgage_month_pay = mortgage();
    month_pay[0] = hcs_month_pay + eat_month_pay + other_month_pay + mortgage_month_pay;
    month_pay[1] = hcs_month_pay + eat_month_pay + other_month_pay + flat_rent_month_pay;
}

int main() {
    double month_pay[2];
    double new_alice_capital = start_alice_capital, total_bob_capital = start_bob_capital;
    sum_month_pay(month_pay);

    for (int i = 1; i <= num_deposit_year * 12; i++) {
        new_alice_capital += salary_alice - month_pay[0];
    }

    double total_alice_capital = flat_cost + new_alice_capital;
    total_bob_capital += deposit(month_pay[1]);

    int alice = round(total_alice_capital);
    int bob = round(total_bob_capital);

    if (alice > bob) {
        printf("alice is richer than bob by %d\n", alice - bob);
    } else {
        printf("bob is richer than alice by %d\n", bob - alice);
    }

    printf("alice capital = %d, bob capital = %d\n", alice, bob);

    return 0;
}