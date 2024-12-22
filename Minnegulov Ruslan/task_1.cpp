#include <stdio.h>

typedef long long int Money;  // RUB

struct Person {
	Money salary;
	Money account;
	Money food;
	Money expence;
	Money rent;
	Money cost_house;
};

struct Deposite {
	Money deposite_account;
	double deposit_procent;
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
	int is_car;
};


struct Person alice;
struct Car alice__car;
struct Mortgage alice__mortgage;
struct Person bob;
struct Deposite alice__deposite;
struct Deposite bob__deposite;


void alice_init()
{
	alice.salary = 2000 * 1000;
	alice.account = 1000 * 1000;
	alice.food = 30 * 1000;
	alice.expence = 30 * 1000;
	alice.cost_house = 14 * 1000 * 1000;

	alice__car.petrol = 5000;
	alice__car.insurance = 7000;
	alice__car.maintenance = 9000;
	alice__car.is_car = 0;

	alice__deposite.deposite_account = 0;
	alice__deposite.deposit_procent = 1.01;

	alice__mortgage.summa_credita = 14 * 1000 * 1000;
	alice__mortgage.first_platez = 14 * 100 * 10;
	alice__mortgage.procent = 9.2;
	alice__mortgage.tern = 30;
	alice__mortgage.platez_month = 106762;  // https://www.banki.ru/services/calculators/hypothec/
	alice.account -= alice__mortgage.first_platez;
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


void alice_car(const int month, const int year)
{
	if ((month == 3) && (year == 2032)) {
		alice__car.is_car == 1;
		alice.account -= 1500 * 1000;
		alice.account -= alice__car.insurance;
		alice.account -= alice__car.maintenance;
	}
	if (month == 1) {
		alice__car.petrol *= 1.01;
		alice.account -= alice__car.insurance;
		alice.account -= alice__car.maintenance;
	}
	if (alice__car.is_car == 1) {
		alice.account -= alice__car.petrol;
	}
}


void alice_deposite()
{
	alice__deposite.deposite_account += alice.account;
	alice__deposite.deposite_account *= alice__deposite.deposit_procent;
	alice.account = 0;
}


void bob_init()
{
	bob.salary = 200 * 1000;
	bob.account = 1000 * 1000;
	bob.food = 30 * 1000;
	bob.expence = 30 * 1000;
	bob.rent = 30 * 1000;

	bob__deposite.deposite_account = 0;
	bob__deposite.deposit_procent = 1.01;
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


void bob_rent()
{
	bob.account -= bob.rent;
}


void bob_deposite()
{
	bob__deposite.deposite_account += bob.account;
	bob__deposite.deposite_account *= bob__deposite.deposit_procent;
	bob.account = 0;
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
		alice_mortgage();
		alice_car(month, year);
		alice_deposite();
		bob_salary(month);
		bob_food(month);
		bob_expence(month);
		bob_rent();
		bob_deposite();

		month += 1;
		if (month == 13) {
			month = 1;
			year += 1;
		}
	}
	alice.account += alice.cost_house;
	alice.account += alice__deposite.deposite_account;
	bob.account += bob__deposite.deposite_account;
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
