#include<stdio.h>

typedef long long int Money;  // RUB

struct Person {
	Money salary;
	Money account;
	Money food;
	Money expence;
	Money renta;
	Money cost_house;
	Money deposit;
	double deposit_procent;
};

struct Mortgage {
	double procent;
	Money summa_credita;
	Money platez_month;
	Money perviy_platez;
	int tern;
};


struct Person alice;
struct Mortgage alice__mortgage;
struct Person bob;


void alice_init()
{
	alice.salary = 200 * 1000;
	alice.account = 1000 * 1000;
	alice.food = 30 * 1000;
	alice.expence = 30 * 1000;
	alice.cost_house = 14 * 1000 * 1000;

	alice.deposit = 0;
	alice.deposit_procent = 1.005;

	alice__mortgage.summa_credita = 14 * 1000 * 1000;
	alice__mortgage.perviy_platez = 14 * 100 * 10;
	alice__mortgage.procent = 9.2;
	alice__mortgage.tern = 30;
	alice__mortgage.platez_month = 106762;  //https://www.banki.ru/services/calculators/hypothec/
	alice.account -= alice__mortgage.perviy_platez;
}

void alice_salary(const int month)
{
	if (month == 1) {
		alice.salary *= 1.03;
	}
	alice.account += alice.salary;
}

void alice_food(const int month)
{
	if (month == 1) {
		alice.food *= 1.07;
	}
	alice.account -= alice.food;
}

void alice_expence(const int month)
{
	if (month == 1) {
		alice.account -= 10 * 1000;
	}
	alice.account -= alice.expence;
}

void alice_mortgage()
{
	alice.account -= alice__mortgage.platez_month;
}

void alice_cost_house(const int month)
{
	if (month == 1) {
		alice.cost_house *= 1.06;
	}
}
void alise_deposite()
{
	alice.deposit += alice.salary;
	alice.deposit -= alice.food;
	alice.deposit -= alice.expence;
	alice.deposit -= alice__mortgage.platez_month;
	alice.deposit *= alice.deposit_procent;
}


void bob_init()
{
	bob.salary = 200 * 1000;
	bob.account = 1000 * 1000;
	bob.food = 30 * 1000;
	bob.expence = 30 * 1000;
	bob.renta = 30 * 1000;

	bob.deposit = bob.account;
	bob.deposit_procent = 1.005;
}

void bob_salary(const int month)
{
	if (month == 1) {
		bob.salary *= 1.03;
	}
	bob.account += bob.salary;
}

void bob_food(const int month)
{
	if (month == 1) {
		bob.food *= 1.07;
	}
	bob.account -= bob.food;
}

void bob_expence(const int month)
{
	if (month == 1) {
		bob.account -= 10 * 1000;
	}
	bob.account -= bob.expence;
}

void bob_renta()
{
	bob.account -= bob.renta;
}

void bob_deposite()
{
	bob.deposit += bob.salary;
	bob.deposit -= bob.food;
	bob.deposit -= bob.expence;
	bob.deposit -= bob.renta;
	bob.deposit *= bob.deposit_procent;
}


void simulation()
{
	int month = 9;
	int year = 2020;
	while (!((month == 9) && (year == 2020 + 30)))
	{
		alice_salary(month);
		alice_food(month);
		alice_expence(month);
		alice_cost_house(month);
		alice_mortgage();
		alise_deposite();
		bob_salary(month);
		bob_food(month);
		bob_expence(month);
		bob_renta();
		bob_deposite();

		month += 1;
		if (month == 13) {
			month = 1;
			year += 1;
		}
	}
	alice.account += alice.cost_house;
	alice.account += alice.deposit;
	bob.account += bob.deposit;

}

void alice_print()
{
	printf("Alice account = %lld \n", alice.account);
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