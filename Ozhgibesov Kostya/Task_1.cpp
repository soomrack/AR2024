#include <iostream>
#include <stdio.h>

long int Ash_capital = 1000*1000;
long int Pin_capital = 1000*1000;
long int Ash_salary = 200*1000;
long int Pin_salary = 200*1000;
long int Ash_apartment = 6000*1000;
long int Pin_deposit = 1000*1000;
long int Ash_everymonthpays = 70000 + 85000; // Пожить + фиксированный платеж по ипотеке
long int Pin_everymonthpays = 70000; // Пожить + аренда квартиры

void Ash_lifetime()
{
	int month = 9;
	int year = 2024;
	while (year <= 2054)
	{
		Ash_capital += Ash_salary;
		Ash_capital -= Ash_everymonthpays;
		if (month == 13)
		{
			year++;
			month = 1;
		}
		if (month == 12)
		{
			Ash_salary *= 1.07;
			Ash_everymonthpays *= 1.08;
		}
		if (year == 2054 && month == 10) break;
	}
	Ash_capital += Ash_apartment;
}

void Pin_lifetime()
{
	int month = 9;
	int year = 2024;
	while (year <= 2054)
	{
		Pin_capital += Pin_salary;
		Pin_capital -= Pin_everymonthpays;
		if (month == 13)
		{
			year++;
			month = 1;
		}
		if (month == 12)
		{
			Pin_salary *= 1.07;
			Pin_everymonthpays *= 1.08;
		}
		if (year == 2054 && month == 10) break;
	}
}

void Pin_deposit_30()
{
	int month = 9;
	int year = 2024;
	while (year <= 2054)
	{
		Pin_deposit *= 1.13;
	}
	Pin_capital += Pin_deposit;
}

void the_end()
{
	if (Ash_capital > Pin_capital)
	{
		printf("Ash has bigger capital %llu\n", Ash_capital, Pin_capital);
	}
	else
	{
		printf("Pin has more money on %llu\n", Pin_capital, Pin_capital);
	}
}

int main()
{
	Ash_lifetime();
	Pin_deposit_30();
	Pin_lifetime();
	the_end();
	return(0);
}