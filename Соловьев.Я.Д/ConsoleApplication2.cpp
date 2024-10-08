#include<stdio.h>
#include<math.h>

typedef long long int Money;

struct Mortgage {
	double rate=0.17;
	Money credit;
	Money platez;
	Money month_pay;
	int year = 30;
	Money payment;
	int month = 12;
};

struct Person {
	Money salary;
	Money ostatok;
	Money expences;
	struct Mortgage mortgage;
	Money flat_cost;
	Money savings;
	double bank_rate;
	Money profit;
	Money profit_savings;
	Money all_money;
	
};

struct Person alice;  // mortgage
struct Person bob;

void home_month_pay() {
	alice.mortgage.year = 30;
	alice.flat_cost = 14000000;
	 alice.mortgage.payment = 1000000;
	 alice.mortgage.month_pay = (alice.flat_cost - alice.mortgage.payment) * alice.mortgage.rate / 12 / (1 - pow(1 + alice.mortgage.rate / 12, -alice.mortgage.year * alice.mortgage.month));
}
void alice_ostatok() {
	 alice.salary = 300000;
	 alice.expences = 50000;
	alice.ostatok += alice.salary - alice.expences - alice.mortgage.month_pay;
}
void bob_ostatok_month() {
	bob.salary = 250000;
	bob.expences = 50000;
	bob.ostatok += (bob.salary - bob.expences);

}
void bob_savings_bank() {
	bob.bank_rate = 0, 16;
	bob.ostatok = bob.profit + bob.ostatok;
	bob.profit = bob.ostatok * bob.bank_rate;
	
}
void bob_first_capitall_bank() {
	bob.savings = 1000000;
	bob.profit_savings += bob.savings * bob.bank_rate;
	bob.savings += bob.savings * bob.bank_rate;
	

}

void simulation() {
	int month = 9;
	int year = 2024;
	while (!((month == 9) && (year == 2024 + 30))) {
		bob_ostatok_month();
		bob_first_capitall_bank();
		bob_savings_bank();
		home_month_pay();
		alice_ostatok();
		month++;


		if (month == 13) {
			month = 1;
			year++;
		}
	}
}
	 
	void bob_all_money() {
		bob.all_money = bob.ostatok + bob.savings + bob.savings;
}
	void alice_all_money() {
		alice.all_money = alice.flat_cost + alice.ostatok;
	}

 
void  end()
{
	if (bob.all_money > alice.all_money)
	{
		printf("Bob richer Alice");
	}
	else 
	{
		printf("Alice richer bob");

	}

}

 int main() {
	 home_month_pay();
	 alice_ostatok();
	 bob_ostatok_month();
	 bob_savings_bank();
	 bob_first_capitall_bank();
	 simulation();
	 bob_all_money();
	 alice_all_money();
	 end();
	 
}

















