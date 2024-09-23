#include <stdio.h>

typedef long long int Money; // В рублях

struct Cat
{
	Money food;
	int is_alive;
};

struct Mortgage
{
	double rate; // процентная ставка
	Money credit; // размер кредита
	Money platez; // размер платежа
	Money month_pay; // ежемесячный платеж

};


struct Car
{
	Money petrol;
	Money insurance;
	Money maintenance;
};


struct Person
{
	Money salary; // зарплата
	Money account; // капитал
	Money food; // еда
	Money expences; // прочие расходы
	struct Mortgage mortgage;
	struct Cat cat;
	struct Car car;
};


struct Person alice;
struct Person bob;

void alice_mortgage()
{
	alice.account -= alice.mortgage.month_pay;

}

void alice_food(const int month)
{
	if (month == 1) {
		alice.food *= 1.1;
	}
	alice.account -= alice.food;
}

void alice_expences(const int month)
{
	if (month == 1) {
		alice.account -= 5000;
	}
	alice.account -= alice.expences;
}


void alice_init()
{
	alice.account = 1000 * 1000;
	alice.salary = 200 * 1000;
	alice.food = 10 * 1000;
	alice.expences = 70 * 1000;

	alice.mortgage.platez = 1000 * 1000;
	alice.mortgage.credit = 14000 * 1000;
	alice.mortgage.rate = 0.17;
	alice.mortgage.month_pay = 100 * 1000;
	alice.account -= alice.mortgage.platez;

	alice.cat.food = 5000;
	alice.cat.is_alive = 0;

	alice.car.petrol = 5000;
	alice.car.insurance = 7000;
	alice.car.maintenance = 9000;
}


void alice_cat(const int month, const int year)
{
	if ((month == 12) && (year == 2026))
	{
		alice.account -= 30000;
		alice.cat.is_alive = 1;
	}
	if ((year == 2043) && (month == 3))
	{
		alice.cat.is_alive = 0;
		alice.account -= 3000;
	}
	if (month == 1)
	{
		alice.cat.food *= 1.1;
	}
	if (alice.cat.is_alive == 1)
	{
		alice.account -= alice.cat.food;
	}
}


void alice_car(const int month, const int year)
{
	if ((month == 3) && (year == 2032))
	{
		alice.account -= 1500 * 1000; // покупка бу машины
		alice.account -= alice.car.petrol;
		alice.account -= alice.car.insurance;
		alice.account -= alice.car.maintenance;
	}
	if (month == 1)
	{
		alice.car.petrol *= 1.1;
		alice.account -= alice.car.insurance;
		alice.account -= alice.car.maintenance;
	}
	alice.account -= alice.car.petrol;
	
}


void alice_print()
{
	printf("Alice account = %lld \n", alice.account);
}


void alice_salary(const int month, const int year)
{
	if (month == 12)
	{
		alice.account += alice.salary;
	}
	if (month == 1)
	{
		alice.salary *= 1.07;
	}
	alice.account += alice.salary;
}




void bob_expences(const int month)
{

}

void bob_food(const int month)
{
	if (month == 1)
	{
		bob.food *= 1.1;
	}
	bob.account -= bob.food;
}

void bob_init()
{
	bob.account = 1000 * 1000;
	bob.salary = 200 * 1000;
	bob.food = 10 * 1000;
	bob.expences = 30 * 1000;
}

void simulation()
{
	int month = 9;
	int year = 2024;

	while ( !((month == 9) && (year == 2024 + 30)) )
	{
		alice_salary(month, year);
		alice_mortgage();
		alice_food(month);
		alice_expences(month);
		alice_cat(month, year);
		alice_car(month, year);
		// alice_vacation();

		month++;
		if (month == 13)
		{
			month = 1;
			year++;
		}
	}
}


int main()
{
	alice_init();

	simulation();

	alice_print();
	return 1;
}