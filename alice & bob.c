#include <stdio.h>

typedef long long int Money;

struct Ipoteka {
	Money credit;
	Money monthpay;
};
	
struct Bank {
	Money vk;
	Money monthpay;
	Money dep;
};
	
struct Person {
	Money zp;
	Money acc;
	Money food;
	Money r;
	Money monthpay;
	struct Bank bank;
	struct Ipoteka ipoteka;
};

struct Person Alice;
struct Person Bob;

void Alice_money ()
 {
	Alice.acc = 0;
	Alice.zp = 200000;
	Alice.r = 50000;
	Alice.monthpay = 100000;
}
void Alice_zp (const int month, const int year) {
	
	if (month == 1) {
		Alice.zp *= 1.1;
	}
	if (month == 9) {
		Alice.acc += Alice.zp;
	}
}

void Bob_money () {
	Bob.acc = 0;
	Bob.zp = 200000;
	Bob.r = 40000;
	Bob.monthpay = 80000;
	Bob.bank.dep = 200000 - 40000-80000;
	Bob.bank.vk = 1000000;
}

void Bob_bank (int dep)
{
	int month = 9;
	int year = 2024;
	
	while (!((month == 9) && (year == 2054)) )
	{
	dep = 20;
	Bob.acc = Bob.zp - Bob.monthpay - Bob.bank.vk; 
	Bob.bank.vk = ((dep/12)*0.01 +1);
	}
}
	
void Alice_monthpay (int year)
{
	year = 2024;
	if (year == 2034 || year == 2044 || year == 2054)
	{
		Alice.monthpay += 5000;
	}
}
	
void Bob_zp (const int month, const int year) {
	if (month == 1) {
		Bob.zp *= 1.1;
	}
	if (month == 9) {
		Bob.acc += Bob.zp;
	}
}

void Bob_monthpay (int year)
{
	year = 2024;
	if (year == 2034 || year == 2044 || year == 2054)
	{
		Bob.monthpay += 5000;
	}
}

void Bob_print( )
{
	printf ("bob capital = %lld \n", Bob.acc);
}

void Alice_print( )
{
	printf ("alice capital = %lld \n", Alice.acc);
}

void simulation( )
{
	int month = 9;
	int year = 2024;
	while ( !((month == 9) && (year == 2024 + 30)) ) {
		
		Alice_zp (month, year);
		Alice_r  (month);
		Alice_monthpay (month);
		
		month++;
		if (month == 13) {
			month = 1;
			year++;
		}
	}
	while ( !((month == 9) && (year == 2024 + 30)) ) {
		
		Bob_zp (month, year);
		Bob_r  (month);
		Bob_monthpay (month);
		
		month++;
		if (month == 13) {
			month = 1;
			year++;
		}
	}
}
		
int main()
{
    Alice_money();
    
	Bob_money();
	
    simulation();

    Alice_print();
    
    Bob_print();
    return 0;
}





