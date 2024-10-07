#include<stdio.h>

typedef long long int Money;  // RUB

struct Person {
	Money salary;
	Money account;
	Money food;
	Money expence;
	Money rent;
	Money cost_house;
};

struct Mortgage {
	double procent;
	Money summa_credita;
	Money platez_month;
	Money first_platez;
	int tern;
};

struct Car {
	Money petrol;
	Money insurance;
	Money maintenance;
};

struct Car aliceCar;
struct Person alice;
struct Mortgage aliceMortgage;
struct Person bob;


void alice_init()
{
	alice.salary = 200 * 1000;
	alice.account = 1000 * 1000;
	alice.food = 30 * 1000;
	alice.expence = 25 * 1000;
	alice.cost_house = 14 * 1000 * 1000;
	aliceCar.petrol = 5000;
	aliceCar.insurance = 7000;
	aliceCar.maintenance = 9000;
	aliceMortgage.summa_credita = 14 * 1000 * 1000;
	aliceMortgage.first_platez = 20000;
	aliceMortgage.procent = 9.2;
	aliceMortgage.tern = 30;
	aliceMortgage.platez_month = 114504;  // (ссылка на ипотечный калькулятор) https://www.banki.ru/services/calculators/hypothec/
	alice.account -= aliceMortgage.first_platez;
}

void alice_salary (const int month)
{
	if (month == 1)
	{
		alice.salary *= 1.03;
	}
	alice.account += alice.salary;
}

void alice_food(const int month)
{
	if (month == 1)
	{
		alice.food *= 1.07;
	}
	alice.account -= alice.food;
}

void alice_expence (const int month)
{
	if (month == 1)
	{
		alice.account -= 10 * 1000;
	}
	alice.account -= alice.expence;
}

void alice_mortgage()
{
	alice.account -= aliceMortgage.platez_month;
}

void alice_cost_house(const int month)
{
	if (month == 1)
	{
		alice.cost_house *= 1.01;
	}
}

void alice_car (const int month, const int year)
{
	if ((month == 3) && (year == 2032))
	{
		alice.account -= 1500 * 1000;
		alice.account -= aliceCar.petrol;
		alice.account -= aliceCar.insurance;
		alice.account -= aliceCar.maintenance;
	}
	if (month == 1)
	{
		aliceCar.petrol *= 1.01;
		alice.account -= aliceCar.insurance;
		alice.account -= aliceCar.maintenance;
	}
	alice.account -= aliceCar.petrol;
}

void bob_init()
{
	bob.salary = 200 * 1000;
	bob.account = 1000 * 1000;
	bob.food = 30 * 1000;
	bob.expence = 25 * 1000;
	bob.rent = 30 * 1000;
}

void bob_salary(const int month)
{
	if (month == 1)
	{
		bob.salary *= 1.03;
	}
	bob.account += bob.salary;
}

void bob_food(const int month)
{
	if (month == 1)
	{
		bob.food *= 1.07;
	}
	bob.account -= bob.food;
}

void bob_expence(const int month)
{
	if (month == 1)
	{
		bob.account -= 10 * 1000;
	}
	bob.account -= bob.expence;
}

void bob_rent()
{
	bob.account -= bob.rent;
}


void simulation()
{
	int month = 9;
	int year = 2024;
	while (!((month == 9) && (year == 2024 + 30)))
	{
		alice_salary(month);
		alice_food(month);
		alice_expence(month);
		alice_cost_house(month);
		alice_car(month, year);
		alice_mortgage();
		bob_salary(month);
		bob_food(month);
		bob_expence(month);
		bob_rent();

		month += 1;
		if (month == 13)
		{
			month = 1;
			year += 1;
		}
	}
	alice.account += alice.cost_house;
}

void alice_print()
{
	printf("Alice account = %lld \n", alice.account);
	printf("Alice house = %lld \n", alice.cost_house);
}

void bob_print()
{
	printf("Bob account = %lld \n", bob.account);
}

int main()
{
	alice_init();
	bob_init();
	simulation();
	alice_print();
	bob_print();
	return 1;
}