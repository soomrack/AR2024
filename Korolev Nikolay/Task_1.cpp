#include <math.h>
#include <stdio.h>

long long int bob_initial_capital = 1000000;
long long int alice_initial_capital = 1000000;
long int alice_salary = 200000;
long int bob_salary = 200000;
long int loan_percent = 18;
long int deposit_percent = 20;
long int years = 30;
long int flat_price = 10000000;
long int month = years * 12;
long int alice_month_pay = 30000;
long int bob_month_pay = 15000;


double calculateLoanPayment(const double loan_payment, const double loan_rate, int loan_years)
{ 
	double month_rate = loan_rate / 12 / 100;

	return loan_years * (month_rate * pow(1 + month_rate, month)) / (pow(1 + month_rate, month) - 1);
}

void linking_to_months()
{
	alice_initial_capital = 0;

	
	for (int i = 1; i <= month; i++) 
	{
		bob_initial_capital *= 1+(deposit_percent/100);
		bob_initial_capital += bob_salary;
		bob_initial_capital -= bob_month_pay;

		alice_initial_capital += alice_salary;
		alice_initial_capital -= alice_month_pay;
		alice_initial_capital -= calculateLoanPayment((flat_price-alice_initial_capital), loan_percent , years);
		


		if (i % 12 == 0) 
		{
			printf("Year = %d\n", i / 12);
			printf("Alice would have %lld\t", alice_initial_capital);
			printf("Bob would have %lld\n", bob_initial_capital);
		}
	}
	
}


int main()
{
	
	linking_to_months();
	
}