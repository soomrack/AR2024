#include<stdio.h>
#include<math.h>

typedef long long int Money;

struct Mortgage {
	Money credit;
	Money platez;
	Money month_pay;
	int year = 30;
	Money payment;
	int month = 12;
};

struct Person {
	Money salary;
	Money account;
	Money expences;
	struct Mortgage mortgage;
	Money flat_cost;
	Money savings;
	double bank_rate;
	Money profit;
	Money profit_savings;
	Money all_money;
	Money deposit_account = 1000000;

};

struct Person alice;  // mortgage
struct Person bob;

void home_month_pay() {
	double rate = 0.17;
	alice.mortgage.year = 30;
	alice.flat_cost = 14000000;
	alice.mortgage.payment = 1000000;
	alice.mortgage.month_pay = (alice.flat_cost - alice.mortgage.payment) * rate / 12 / (1 - pow(1 + rate / 12, -alice.mortgage.year * alice.mortgage.month));
}


void alice_account_month() {
	alice.salary = 300000;
	alice.expences = 50000;
	alice.account += alice.salary - alice.expences - alice.mortgage.month_pay;
}


void bob_account_month() {
	bob.salary = 250000;
	bob.expences = 50000;
	bob.account += (bob.salary - bob.expences);

}


void bob_savings_bank() {
	double bank_rate = 0.16;
	bob.deposit_account *= bank_rate;
	bob.deposit_account += bob.account;

}



void simulation() {
	int month = 9;
	int year = 2024;
	while (!((month == 9) && (year == 2024 + 30))) {
		bob_account_month();
		bob_savings_bank();
		home_month_pay();
		alice_account_month();

		month++;
		if (month == 13) {
			month = 1;
			year++;
		}
	}
}


void bob_all_money() {
	bob.all_money = bob.deposit_account;
}


void alice_all_money() {
	alice.all_money = alice.flat_cost + alice.account;
}


void  print_result()
{
	if (bob.all_money > alice.all_money)
	{
		printf("Bob richer than Alice");
	}
	else
	{
		printf("Alice richer than bob");

	}

}

int main() {
	home_month_pay();
	alice_account_month();
	bob_account_month();
	bob_savings_bank();
	simulation();
	bob_all_money();
	alice_all_money();
	print_result();

}

















