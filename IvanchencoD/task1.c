#include <stdio.h>


typedef long long int Money;


struct Mortgage 
{
    double rate;          
    Money credit;         
    Money pay;            
    Money month_pay;      
};


struct Bank 
{
    Money contribution;   
    Money month_pay;      
};


struct Individual 
{
    Money salary;                   
    Money monthly_expenses;         
    Money status;                   
    Money apartment;                 
    Money free_money;               
    struct Mortgage mortgage;
    struct Bank bank;
};


struct Individual Alice;
struct Individual Bob;


void initialize_Alice() 
{
    Alice.status = 0;
    Alice.salary = 230 * 1000;
    Alice.monthly_expenses = 70 * 1000;
    Alice.free_money = 0;

    Alice.mortgage.rate = 0.17;
    Alice.mortgage.credit = 13 * 1000 * 1000;
    Alice.mortgage.month_pay = 150 * 1000;
} 


void Alice_pay_mortgage()
{
    Alice.status -= Alice.mortgage.month_pay;
}


void Alice_update_salary(int month) 
{
    if (month == 12) {
        Alice.status += Alice.salary;
    }
    if (month == 1) {
        Alice.salary *= 1.09; 
    }
    Alice.status += Alice.salary;
}


void Alice_print() 
{
    if (Alice.status > Bob.status) {
        printf ("Alice has more money than Bob on %lld\n", Alice.status - Bob.status);
    }

    printf("Alice's capital: %lld \n", Alice.status);
}


void initialize_Bob()
{
    Bob.status = 0;
    Bob.salary = 230 * 1000;
    Bob.monthly_expenses = 70 * 1000;
    Bob.apartment = 30 * 1000; 
    Bob.free_money = 0;
    Bob.bank.month_pay = 130 * 1000;
}


void Bob_update_salary(int month) 
{
    if (month == 12) {
        Bob.status += Bob.salary;
    }
    if (month == 1) {
        Bob.salary *= 1.09; 
    }
    Bob.status += Bob.salary;
}


void Bob_bank(int deposit)
{
    int month = 9;
    int year = 2024;

    while( !((month == 9) && (year == 2054)) ) {

    deposit = 20; 
    Bob.status -= Bob.bank.month_pay;
    Bob.bank.contribution = ((deposit/12)*0.01+1);
    Bob.free_money += (Bob.salary -Bob.bank.month_pay - Bob.monthly_expenses - Bob.apartment);
    Bob.status += (Bob.bank.contribution + Bob.free_money);
    }
}



void Bob_print() 
{
    if (Alice.status < Bob.status) {
        printf ("Bob has more money than Alice on %lld\n", Bob.status - Alice.status);
    }

    printf("Bob's capital: %lld \n", Bob.status);
}



void simulation() 
{
    int month = 9;
    int year = 2024;

    while (!(month == 9 && year == 2054)) {
    
        Alice_update_salary(month);
        Alice_pay_mortgage();

        Bob_update_salary(month);

        month++;
        if (month == 13) {
            month = 1;
            year++;
        }
    }
}


int main() 
{
    initialize_Alice();
    initialize_Bob();

    simulation();

    Alice_print();
    Bob_print();

    return 0;
}