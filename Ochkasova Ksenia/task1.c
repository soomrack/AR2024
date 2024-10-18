#include <stdio.h>

typedef long long int Money;

struct Ipoteka {
    Money credit;
    Money monthpay;
    double rate;
};
	
struct Bank {
    Money vklad;
    Money monthpay;
    Money deposite;
};
	
struct Person {
    Money zarplata;
    Money account;
    Money food;
    Money rashod;
    Money monthpay;
    struct Bank bank;
    struct Ipoteka ipoteka;
};

struct Person Alice;
struct Person Bob;

void Alice_money ()
 {
    Alice.account = 0;
    Alice.zarplata = 200000;
    Alice.rashod = 50000;
    Alice.monthpay = 100000;
}
void Alice_zarplata (const int month, const int year) {
	
    if (month == 1) {
        Alice.zarplata *= 1.1;
    }
	Alice.account += Alice.zarplata;
}

void Alice_monthpay (int year)
{
    year = 2024;
    if (year == 2034 || year == 2044 || year == 2054)
  {
	Alice.monthpay += 5000;
        Alice.account -= Alice.monthpay;
  }
}

void Alice_ipoteka ()
{
      Alice.account -= Alice.ipoteka.monthpay;
}

void Alice_rashod(const int month)
{
    Alice.account -= Alice.rashod;
    
    if (month == 1) {
        Alice.rashod *= 1.1;
    }
}
	
void Bob_money () {
    Bob.account = 0;
    Bob.zarplata = 200000;
    Bob.rashod = 40000;
    Bob.monthpay = 80000;
    Bob.bank.vklad = Bob.account - Bob.rashod - Bob.monthpay;
    Bob.bank.vklad = 1000000;
}

void Bob_bank (int dep)
{
    int month = 9;
    int year = 2024;
	
    while (!((month == 9) && (year == 2054)) )
    {
        Bob.account = Bob.zarplata - Bob.monthpay - Bob.bank.vklad; 
	    Bob.bank.vklad = ((dep/12)*0.01 +1);
    }
}
	
void Bob_zarplata (const int month, const int year) {
    if (month == 1) {
	Bob.zarplata *= 1.1;
    }
	Bob.account += Bob.zarplata;
}

void Bob_monthpay (int year)
{
    year = 2024;
    if (year == 2034 || year == 2044 || year == 2054)
    {
        Bob.monthpay += 5000;
    }
}

void Bob_rashod(const int month)
{
    Bob.account -= Bob.rashod;
    
    if (month == 1) {
        Bob.rashod *= 1.1;
    }
}

void Bob_print( )
{
    printf ("bob capital = %lld\n", Bob.account);
}

void Alice_print( )
{
    if (Alice.account > Bob.account) {
        printf ("Alice has more money on \n");
    }	
    if (Bob.account > Alice.account) {
	printf ("Bob has more money on \n");
    }
    printf ("alice capital = %lld \n", Alice.account);
}
	


void simulation( )
{
    int month = 9;
    int year = 2024;
    while ( !((month == 9) && (year == 2024 + 30)) ) {
		
        Alice_zarplata (month, year);
		
	Alice_monthpay (month);

	Alice_rashod (month);

	Bob_zarplata (month, year);
		
	Bob_monthpay (month);

	Bob_rashod (month);
		
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

