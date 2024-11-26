#include<stdio.h>
#include<math.h>
#include<stdbool.h>


typedef long long int Money;
typedef bool Logik;


struct Animal{
    Money nutrition_cost;
    Logik purchase_animal;
    Logik animal_alive;
};


struct Vehicle {
    Money fuel_cost;
    Money repair_cost;
};


struct Loan {
    double rate;
    Money total_credit;
    Money initial_payment;
    Money monthly_payment;
};


struct Rental {
    Money rental_price;
    Money monthly_payment;
};


struct Individual {
    Money income;
    Money balance;
    Money nutrition_cost;
    Money expenses;
    struct Animal cat;
    struct Loan mortgage;
    struct Rental arenda; 
    struct Vehicle car;
};


struct Individual Bob;
struct Individual Alice;


void Bob_mortgage()
{
    Bob.balance -= Bob.mortgage.monthly_payment;
}


int calculate_total_credit()
{
    Money year = 30;
    Money month = year * 12;
    return 30* (Bob.mortgage.rate * pow(1 + Bob.mortgage.rate, month))
        / (pow(1 + Bob.mortgage.rate, month) - 1);
}


void Bob_nutrition_cost(const int month)
{
    if (month == 1) {
        Bob.nutrition_cost *= 1.1;
    }
    Bob.balance -= Bob.nutrition_cost;
}


void Alice_nutrition_cost(const int month)
{
    if (month == 1) {
        Alice.nutrition_cost *= 1.1;
    }
    Alice.balance -= Bob.nutrition_cost;
}


void Bob_init()
{
    Bob.balance = 1000000;
    Bob.income = 200000;
    Bob.nutrition_cost = 10000;
    Bob.expenses = 70000;

    Bob.mortgage.initial_payment = 1000000;
    Bob.mortgage.total_credit = 14000000;
    Bob.mortgage.rate = 0.17;
    Bob.mortgage.monthly_payment = calculate_total_credit();
    Bob.balance -= Bob.mortgage.initial_payment;

    Bob.cat.nutrition_cost = 5000;
    Bob.cat.purchase_animal = false;
    Bob.cat.animal_alive = true;
}


void Alice_init()
{
    Alice.balance = 1000000;
    Alice.income  = 200000;
    Alice.nutrition_cost = 15000;
    Alice.expenses = 50000;

    Alice.arenda.rental_price = 30000;
    Alice.arenda.monthly_payment = 10000;

    Alice.car.fuel_cost = 100000;
}


void Bob_purchase_animal()
{   
    if (Bob.cat.purchase_animal == false){
    Bob.balance -= 30000;
    Bob.cat.purchase_animal = true;
    }
}


void Bob_cat(const int month, const int year)
{   
    if (Bob.cat.animal_alive){
    Bob.balance -= Bob.cat.nutrition_cost;
    
        if ((month == 12) && (year==2026)) {
        Bob.balance -= 30000;
        }
        if ((month == 3) && (year == 2035)) {
        Bob.balance -= 30000;
        }
        if ((month == 6) && (year == 2040)) {
        Bob.cat.animal_alive = false;
        }
    }
    
}



void Alice_car_obslug(const int month, const int year)
{
    if ((month == 11) && (year==2027)) {
        Alice.balance -= Alice.car.repair_cost;
    }
    if ((month == 3) && (year == 2035)) {
        Alice.balance -= Alice.car.repair_cost;
    }
     if ((month == 6) && (year == 2043)) {
        Alice.balance -= Alice.car.repair_cost;
    }
}


void Bob_income(const int month, const int year)
{
    Bob.balance += Bob.income;    
}


void Alice_income(const int month, const int year)
{
    Alice.balance += Alice.income;  
}


void apply_inflation(int const month, int const year)
{
    if (month ==1){
        Bob.expenses *= 1.07;
        Alice.expenses *= 1.07; 
    } 
}


void print_result()
{
    printf("Alice balance = %lld \t", Bob.balance);
    printf("Bob balance = %lld \n" , Alice.balance);
}


void run_simulation()
{
    int month = 9;
    int year = 2024;

    while( !((month == 9) && (year == 2024 + 30)) ) {

        Bob_income(month, year);
        Bob_mortgage();
        Bob_nutrition_cost(month);
        Bob_purchase_animal();
        Bob_cat(month, year);
        
        Alice_income(month, year);
        Alice_nutrition_cost(month);
        Alice_car_obslug(month, year);

        apply_inflation(month, year);

        month++;
        if(month == 13) {
            month = 1;
            year++;
            print_result();
        }
    }
}


int main()
{
    Bob_init();

    Alice_init();

    run_simulation();

    
    if (Bob.balance > Alice.balance) {
        printf("Bob has a higher balance: %lld\n", Bob.balance);
    } else if (Bob.balance < Alice.balance) {
        printf("Alice has a higher balance: %lld\n", Alice.balance);
    } else {
        printf("Both users have the same balance: %lld\n", Bob.balance);
    }
    return 0;
}
