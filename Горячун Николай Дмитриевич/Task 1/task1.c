#include <stdio.h>

typedef long long int Money; // RUR

struct Deposit {
    Money account;
    double interest;
};

struct Credite {
    Money credit;
    Money monthly_payment;
};

struct Person {
    Money expenditure;
    Money salary;
    Money apartment_price;
    Money rent;
    struct Deposit deposite;
    struct Credite credit;
};


long double inflation = 0.0742;
int month_counter = 1;

struct Person alice;
struct Person bob;


void alice_init()
{
	alice.deposite.account = 0;
	alice.deposite.interest = 0.19;
    alice.expenditure = 399 + 22500 + 5000 + 4500;
    alice.salary = 300000;
    alice.credit.credit = 11687000;
    alice.credit.monthly_payment = 226312;
}


void bob_init()
{
	bob.deposite.account = 1313000;
	bob.deposite.interest = 0.19;
    bob.expenditure = 399 + 22500 + 5000 + 4500;
    bob.salary = 300000;
    bob.rent = 30000;
    bob.apartment_price = 13000000;
}


void alice_expense_counting()
{
	alice.deposite.account += alice.deposite.account * alice.deposite.interest / 12;
	alice.deposite.account += alice.salary - alice.expenditure - alice.credit.monthly_payment;
};

void alice_credite_counting()
{
	alice.credit.credit -= alice.credit.monthly_payment;
};


void bob_expense_counting()
{
	bob.deposite.account += bob.deposite.account * bob.deposite.interest / 12;
	bob.deposite.account += bob.salary - bob.expenditure - bob.rent;
};


void print()
{
    if (bob.deposite.account >= bob.apartment_price){
		printf("Боб купил квартиру быстрее.\nСчёт Боба: %lld.\nСчёт Алисы: %lld.\n", bob.deposite.account, alice.deposite.account);
	};
	if (alice.credit.credit <= 0){
		printf("Алиса купила квартиру быстрее.\nСчёт Алисы: %lld.\nСчёт Боба: %lld.\n", alice.deposite.account, bob.deposite.account);
	};
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
};



void inflation_changes()
{
    month_counter++;
	if (month_counter == 13) {
        alice_inflation();
        bob_inflation();
        month_counter = 1;
	};
};


int main()
{
    alice_init();		

	bob_init();

	while (bob.deposite.account < bob.apartment_price && alice.credit.credit > 0) {		

        alice_expense_counting();

        alice_credite_counting();

        bob_expense_counting();

        inflation_changes();

		print();
	};
    return 1;
}
