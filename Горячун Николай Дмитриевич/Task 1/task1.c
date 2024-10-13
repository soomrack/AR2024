#include <stdio.h>

typedef long long int Money; // RUR


struct Deposit {
    Money account;
    double interest;
};


struct Person {
    Money expenditure;
    Money salary;
    Money apartment_price;
    Money rent;
    Money credit_monthly_payment;
    int year_of_raising;
    Money car_price;
	int buy_car;
    struct Deposit deposite;
};


long double inflation = 0.0742;
int month_counter = 1;
int year_counter = 0;
int new_year = 0;

struct Person alice;
struct Person bob;


void alice_init()
{
	alice.deposite.account = 0;
	alice.deposite.interest = 0.19;
    alice.expenditure = 399 + 22500 + 5000 + 4500; // Расходы за месяй (Цена подписки СберПрайм + еда + одежда + комуналка)
    alice.salary = 300000;
    alice.credit_monthly_payment = 226312;
}


void bob_init()
{
	bob.deposite.account = 1313000;
	bob.deposite.interest = 0.19;
    bob.expenditure = 399 + 22500 + 5000 + 4500; // Расходы за месяй (Цена подписки СберПрайм + еда + одежда + комуналка)
    bob.salary = 300000;
    bob.rent = 30000;
    bob.apartment_price = 13000000;
    bob.year_of_raising = 3;
    bob.car_price = 4000000;
    bob.buy_car = 0;
}


void alice_expense_counting()
{
	alice.deposite.account += alice.deposite.account * alice.deposite.interest / 12;
	alice.deposite.account += alice.salary - alice.expenditure - alice.credit_monthly_payment;
};


void bob_expense_counting()
{
	bob.deposite.account += bob.deposite.account * bob.deposite.interest / 12;
	bob.deposite.account += bob.salary - bob.expenditure - bob.rent;
};


void alice_inflation()
{
    alice.expenditure += alice.expenditure * inflation;
    alice.salary += alice.salary * inflation;
};


void bob_inflation()
{
    bob.expenditure += bob.expenditure * inflation;
    bob.rent += bob.rent * inflation;
    bob.salary += bob.salary * inflation;
    bob.apartment_price += bob.apartment_price * inflation;
    bob.car_price += bob.car_price * inflation;
};



void inflation_changes()
{
	if (new_year == 1) {
        alice_inflation();
        bob_inflation();
        new_year = 0;
    }
};


void month_and_year_counter()
{
    month_counter++;
	if (month_counter == 13) {
		year_counter++;
        month_counter = 1;
		new_year = 1;
	};
};


void bob_raising()
{
    if (year_counter == bob.year_of_raising) {
        bob.salary += 50000;
    };
};


void bob_buy_car()
{
    if (bob.buy_car == 0 && bob.deposite.account >= bob.car_price) {
        bob.deposite.account -= bob.car_price;
		bob.buy_car = 1;
    };
};


void cycle_body()
{
    bob_raising();
    alice_expense_counting();
    bob_expense_counting();
    bob_buy_car();
    month_and_year_counter();
    inflation_changes();
};


void print()
{
    if (bob.buy_car == 1) {
        printf("Боб купил машину.\nЦена квартиры: %lld.\nСчёт Боба: %lld.\nСчёт Алисы: %lld.\n", bob.apartment_price, bob.deposite.account, alice.deposite.account);
    } else {
        printf("Боб не купил машину.\nЦена квартиры: %lld.\nСчёт Боба: %lld.\nСчёт Алисы: %lld.\n", bob.apartment_price, bob.deposite.account, alice.deposite.account);
    };
};


int main()
{
    alice_init();		

	bob_init();

	while (year_counter != 30) {		
        cycle_body();
	};
    print();
    return 0;
}
