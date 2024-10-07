#include <math.h>
#include <stdio.h>

long int years = 30;
long int month = years * 12;

struct person {
	int initial_capital;
    int salary;
	bool sadden_waste;
};

int initilize_person()
{
	struct person alice = {1000000,200000,false};
	struct person bob = {1000000,200000, true};
	linking_to_months(alice.initial_capital , alice.salary, bob.initial_capital,bob.salary);
}

long int alice_month_pay = 30000;
long int bob_month_pay = 15000;

double calculate_loan_payment(const double loan_payment, const double loan_rate, int loan_years)
{ 
	double month_rate = loan_rate / 12 / 100;
	return loan_years * (month_rate * pow(1 + month_rate, month)) / (pow(1 + month_rate, month) - 1);
}

void linking_to_months(int alice_initial_capital, int alice_salary, int bob_initial_capital, int bob_salary)
{
	long int flat_price = 10000000;
	int bob_buy_car = 1000000;
	alice_initial_capital = 0;
	for (int i = 1; i <= month; i++) {
		bob_initial_capital *= 1+(20/100);
		bob_initial_capital += bob_salary;
		bob_initial_capital -= bob_month_pay;
		
		if (month == 52) {
			bob_initial_capital -= bob_buy_car;
		} 
		
		alice_initial_capital += alice_salary;
		alice_initial_capital -= alice_month_pay;
		alice_initial_capital -= calculate_loan_payment((flat_price-alice_initial_capital), 18 , years);
		
		if (month % 12 == 0) {
			printf("Year = %d\n", month / 12);
			printf("Alice would have %lld\t", alice_initial_capital);
			printf("Bob would have %lld\n", bob_initial_capital);
		}
	}
}

int main()
{
	initilize_person();
}
