#include <stdio.h>

typedef long long int Money;
struct Depasit{
    Money account;
    double interest;
};
struct Person{
    Money expenditure;
    Money salary;
    Money rent;
    Money credit;
    Money monthly_payment;
};


long double inflation = 0.0742;
Money monthly_payment = 226312;
Money apartment_price = 13000000;
int month_counter = 1;
struct Depasit alice_depasite;
struct Depasit bob_depasite;
struct Person alice;
struct Person bob;


void alice_init()
{
	alice_depasite.account = 0;
	alice_depasite.interest = 0.19;
    alice.expenditure = 399 + 22500 + 5000 + 4500;
    alice.salary = 300000;
    alice.credit = 11687000;
    alice.monthly_payment = 226312;
}


void bob_init()
{
	bob_depasite.account = 1313000;
	bob_depasite.interest = 0.19;
    bob.expenditure = 399 + 22500 + 5000 + 4500;
    bob.salary = 300000;
    bob.rent = 30000;
}


void alice_expense_counting()
{
	alice_depasite.account += alice_depasite.account * alice_depasite.interest / 12;
	alice_depasite.account += alice.salary - alice.expenditure - alice.monthly_payment;
	alice.credit -= alice.monthly_payment;
};


void bob_expense_counting()
{
	bob_depasite.account += bob_depasite.account * bob_depasite.interest / 12;
	bob_depasite.account += bob.salary - bob.expenditure - bob.rent;
};


void print()
{
    if (bob_depasite.account >= apartment_price){
		printf("Боб купил квартиру быстрее.\nСчёт Боба: %lld.\nСчёт Алисы: %lld.\n", bob_depasite.account, alice_depasite.account);
	};
	if (alice.credit <= 0){
		printf("Алиса купила квартиру быстрее.\nСчёт Алисы: %lld.\nСчёт Боба: %lld.\n", alice_depasite.account, bob_depasite.account);
	};
};


void inflation_changes()
{
    month_counter++;
	if (month_counter == 13) {
		alice.expenditure += alice.expenditure * inflation;
		alice.salary += alice.salary * inflation;
		bob.expenditure += bob.expenditure * inflation;
		bob.rent += bob.rent * inflation;
		bob.salary += bob.salary * inflation;
		apartment_price += apartment_price * inflation;
        month_counter = 1;
	};
};


int main()
{
    alice_init();		

	bob_init();

	while (bob_depasite.account < apartment_price && alice.credit > 0){		

        alice_expense_counting();

        bob_expense_counting();

        inflation_changes();

		print();
	};
    return 1;
}
