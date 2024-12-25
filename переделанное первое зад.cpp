#include <stdio.h>
#include <math.h>

long int startcap_Alice = 1000000;
long int vznos_ipoteka = 128518;
float stavka_ipoteka = 1.22;
long int another_trati_Alice = 35000;
long int kvartira_Alice = 8000000;
long int zp_Alice = 200000;
float account_Alice = 1000000;

float month_year = 9;
int year = 2024;
float inflation = 1.09;

long int kvartira_Bob = 25000;
long int another_trati_Bob = 30000;
long int zp_Bob = 200000;
long int vklad_Bob = 1000000;
float stavka_vklad = 1.20;
float account_Bob = 0;

void next_year()
{
	if (month_year == 13)
	{
		year++;
		month_year = 1;
	}
}

void first_pay_month_Alice()
{
	account_Alice -= startcap_Alice;
}

void pay_month_Alice()
{
	while (year <= 2054 && month_year <= 12)
	{
		account_Alice += zp_Alice;
		account_Alice -= another_trati_Alice + vznos_ipoteka;
		month_year++;
		next_year();
	}
}

void inflation_Alice()
{
	zp_Alice *= 1.07;
	another_trati_Alice *= 1.09;
	kvartira_Alice *= 1.08;
}

void pay_month_Bob()
{
	while (year <= 2054)
	{
		account_Bob += zp_Bob;
		account_Bob -= another_trati_Bob + kvartira_Bob;
		month_year++;
		next_year();
	}
	if (year == 2054)
	{
		account_Bob += stavka_vklad * 30;
	}
}

void inflation_Bob()
{
	zp_Bob *= 1.07;
	another_trati_Bob *= 1.09;
	kvartira_Bob *= 1.08;
}

void end()
{
	if (year == 2054 && month_year == 10)
	{
		printf("account_Bob = %ld\n", account_Bob);
		printf("account_Alice = %f\n", account_Alice);
		printf("kvartira_Alice = %ld\n", kvartira_Alice);
	}
}

int main(void)
{
	pay_month_Alice();
	inflation_Alice();
	pay_month_Bob();
	inflation_Bob();
	end();
}
