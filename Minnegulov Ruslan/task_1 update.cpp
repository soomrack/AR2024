#include<stdio.h>

typedef long long int Money;  // RUB


struct Person {
    Money salary;
    Money account;
    Money food;
    Money expence;
    Money rent;
    Money cost_house;
    Money deposit;
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


struct Car alice_car;
struct Person alice;
struct Mortgage alice_mortgage;
struct Person bob;


void alice_init()
{
	alice.salary = 200 * 1000;
	alice.account = 1000 * 1000;
	alice.food = 30 * 1000;
	alice.expence = 25 * 1000;
	alice.cost_house = 14 * 1000 * 1000;
	alice_car.petrol = 5000;
	alice_car.insurance = 7000;
	alice_car.maintenance = 9000;
	alice_car.is_car = 0;
	
	alice.deposit = 0;
	alice.deposit_procent = 1.005;
	
	alice_mortgage.summa_credita = 14 * 1000 * 1000;
	alice_mortgage.first_platez = 20000;
	alice_mortgage.procent = 9.2;
	alice_mortgage.tern = 30;
	alice_mortgage.platez_month = 114504;  // (ссылка на ипотечный калькулятор) https://www.banki.ru/services/calculators/hypothec/
	
	alice.account -= alice_mortgage.first_platez;
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
	alice.account -= alice_mortgage.platez_month;
}

void alice_cost_house(const int month)
{
	if (month == 1) {
		alice.cost_house *= 1.01;
	}
}

void alice_car(const int month, const int year)
{
	if ((month == 3) && (year == 2032)) {
		alice_car.is_car == 1;
		alice.account -= 1500 * 1000;
		alice.account -= alice_car.petrol;
		alice.account -= alice_car.insurance;
		alice.account -= alice_car.maintenance;
	}
	if (month == 1) {
		aliceCar.petrol *= 1.01;
		alice.account -= alice_car.insurance;
		alice.account -= alice_car.maintenance;
	}
	if (alice_car.is_car == 1) {
		alice.account -= alice_car.petrol;
	}
}

void alise_deposite()
{
	alice.deposit += alice.salary;
	alice.deposit -= alice.food;
	alice.deposit -= alice.expence;
	alice.deposit -= alice_mortgage.platez_month;
	alice.deposit *= alice.deposit_procent;
}


void bob_init()
{
	bob.salary = 200 * 1000;
	bob.account = 1000 * 1000;
	bob.food = 30 * 1000;
	bob.expence = 25 * 1000;
	bob.rent = 30 * 1000;

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

void bob_rent()
{
	bob.account -= bob.rent;
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
	int year = 2024;
	while (!((month == 9) && (year == 2024 + 30)))
	{
		alice_salary(month);
		alice_food(month);
		alice_expence(month);
		alice_cost_house(month);
		alice_car(month, year);
		alice_mortgage();
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
	//alice.account += alice.cost_house;
}


void alice_print()
{
	printf("Alice account = %lld \n", alice.account += (alice.cost_house + alice.deposit));
}

void bob_print()
{
	printf("Bob account = %lld \n", bob.account += bob.deposit);
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
