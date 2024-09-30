#include<stdio.h>
#include<math.h>
#include<iostream>

double home_month1;
long long int home = 14000000;
double alice_ostatok;
double sum_pay;
int procent = 16;
int sum_start;
int trata = 100000;
int salary = 200000;
int near_full_ostatok_bob;
int money = 1000000;
int sum_pay_all;

void home_month_pay() {
	int year1 = 30;
	int month1 = 12;
	int pay1 = 1000000;
	int procent1 = 17;
	home_month1 = (home * procent1 / 100 * year1 - pay1) / year1 / month1;
}

void alice_ostatok1() {
	int alice_fullsalary = 300000;
	int alice_trata = 50000;
	alice_ostatok = alice_fullsalary - alice_trata - home_month1;
}

void pay_bob2() {
	sum_pay = (salary - trata) * procent / 100 / 12;
}

void sum_pay_bob1() {
	int money = 1000000;
	sum_start = money * procent / 100 / 12;
}

void simulation() {
	int month = 9;
	int year = 2024;
	int n = 0;
	while (!((month == 9) && (year == 2024 + 30) &&(n==29*12+3))) {
		month++;
		n++;
		sum_pay_all = sum_pay * n;
		sum_pay_all += sum_pay_all;

	
		 
		sum_start += sum_start;
		near_full_ostatok_bob = salary - trata + salary - trata;
		alice_ostatok += alice_ostatok;
		sum_start += sum_start;
	}

	if (month == 13) {
		month = 1;
		year++;
	}
}

 void  end()
{
	double full_money_bob = near_full_ostatok_bob + sum_pay_all + sum_start + money;
	double full_money_alice = alice_ostatok + home;
	if (full_money_bob > full_money_alice)
	{
		printf("Bob richer Alice");
	}
	else if (full_money_bob < full_money_alice)
	{
		printf("Alice richer bob");

	}

}

 int main() {
	home_month_pay();
	alice_ostatok1();
	pay_bob2();
	sum_pay_bob1();
	simulation();
	end();

	
	
}
	



















