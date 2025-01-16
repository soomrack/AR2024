#include <stdio.h>


typedef long long int Rub;



double INFLIATION = 1.09;



struct Mortgage {
double rate;
Rub credit;
Rub month_pay;
};


struct Bank {
double rate;
Rub deposit;
};


struct Person {
double index_s;
Rub salary;
Rub status;
Rub expenses;

Rub apartment;
Rub loan_apartment_pay;

struct Mortgage mortgage;
struct Bank bank;
};


Person bob;
Person alice;


void alice_init()
{
    alice.salary = 200 * 1000;
    alice.status = 1000 * 1000;
    alice.expenses = 50 * 1000;
    alice.apartment = 9500 * 1000;
    alice.index_s = 1.09;

    alice.mortgage.rate  = 17;
    alice.mortgage.credit =  alice.apartment - alice.status;
    alice.status = 0;
    alice.mortgage.month_pay = 150 * 1000;
}

void alice_mortgage(int const month)
{
alice.status -= alice.mortgage.month_pay;
if (month == 12) {
alice.apartment *= INFLIATION;
}
}


void alice_expenses(int year, int const month)
{
    alice.status -= alice.expenses;

}


void alice_salary(int const month)
{
    if (month == 12) {
        alice.salary *= alice.index_s;
    }
    alice.status += alice.salary;
}


void bob_init()
{
bob.salary = 150 * 1000;
bob.status = 1000 * 1000;
bob.expenses = 50 * 1000;
bob.bank.rate = 1.01245;
bob.index_s = 1.09;
bob.loan_apartment_pay = 50 * 1000;
bob.bank.deposit = 0;
}


void bob_bank()
{
    bob.bank.deposit *= bob.bank.rate;
    bob.bank.deposit += bob.status;
    bob.status = 0;
}


void bob_kvartira(int start_year, int year, int const month)
{
    bob.status -= bob.loan_apartment_pay;
    if (((year - start_year)%5 == 0) and (month == 9)) {
        bob.loan_apartment_pay += 5000;
    }
}


void bob_expenses(int const year, int const month)
{
    bob.status -= bob.expenses;

}


void bob_salary(int const month)
{
    if (month == 12) {
        bob.salary *= bob.index_s; 
        }
    
    bob.status += bob.salary;

    if (month == 11) {
        bob.status += bob.salary;
    }
}


void simulation()
{
    int years_simulation = 30;
    int start_year = 2024;
    int month = 10;
    int year = start_year;
    int end_year = start_year + years_simulation;

    while( not(((month == 10) and (year == end_year))) ) {

        alice_salary(month);
        alice_expenses(year, month);
        alice_mortgage(month);
        
        bob_salary(month);
        bob_expenses(year, month);
        bob_apartments(start_year, year, month);
        bob_bank();
        
        month++;
        if(month == 13) {
            month = 1;
            year ++;
        }
    }
    alice.status += alice.apartment;
}


void strategic_evaluation()
{
    printf("\n Bob  %i", bob.bank.deposit );
    printf("\n Alice  %i", alice.status );
    
    if (alice.status > bob.bank.deposit) {
        printf("\n Alice strategic is better");
    }
    else {
        printf("\n Bob strategic is better");
    }

}


int main()
{
    alice_init();

    bob_init();

    simulation();

    strategic_evaluation();

    return 1;
}


