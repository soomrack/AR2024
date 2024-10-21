#include <stdio.h>
#include <cmath>

typedef long long int rub;


int YEARS_SIMULATION = 30,
START_YEAR = 2024;
double INFLIATION = 1.09;



struct Mortgage{
double rate;
rub credit;
rub month_pay;
};


struct Bank{
double rate;
rub credit;
};


struct Person{
double index_s;
rub salary;
rub status;
rub expenses;

rub apartment;
rub loan_kvartira_pay;

struct Mortgage mortgage;
struct Bank bank;
};


Person bob;
Person alice;


void alice_money()
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

void alice_mortgage(int month)
{
alice.status -= alice.mortgage.month_pay;
alice.status -= alice.expenses;
if (month == 12)
{
alice.apartment *= INFLIATION;
}

}


void bob_money()
{
bob.salary = 200 * 1000;
bob.status = 1000 * 1000;
bob.expenses = 50 * 1000;
bob.bank.rate = 1.01245;
bob.index_s = 1.09;
bob.loan_kvartira_pay = 50*1000;
}


void bob_bank()
{
bob.status -= bob.expenses;
bob.status *= bob.bank.rate;
}


void bob_kvartira(int year,int month)
{
bob.status -= bob.loan_kvartira_pay;
if (((year - START_YEAR)%5 == 0) and (month == 9))
{
    bob.loan_kvartira_pay += 5000;
}
}


void bob_salary(int month)
{
    if (month==12)
    {
        bob.salary *= bob.index_s;
    }
    bob.status += bob.salary;
}

void alice_salary(int month)
{
    if (month==12)
    {
        alice.salary *= alice.index_s;
    }
    alice.status += alice.salary;
}


void simulation()
{
    int month = 10;
    int year = START_YEAR;
    int end_year = START_YEAR + YEARS_SIMULATION;

    while( not(((month == 10) and (year == end_year))) ) 
    {
        
        alice_salary(month);
        alice_mortgage(month);
        
        bob_salary(month);
        bob_bank();
        bob_kvartira(year,month);

        month++;
        if(month == 13) 
        {
            month = 1;
            year++;
        }
        //debug
        printf("\n %i", alice.mortgage.month_pay);
        printf("\n %i", alice.status);
    }
    alice.status += alice.apartment;
}


void strategic_evaluation()
{
    printf("\n Bob  %i", bob.status );
    printf("\n Alice  %i", alice.status );
    
    if (alice.status > bob.status)
    {
        printf("\n Alice strategic is better");
    }
    else
    {
        printf("\n Bob strategic is better");
    }

}


int main()
{
    alice_money();

    bob_money();

    simulation();

    strategic_evaluation();
    return 1;
}



