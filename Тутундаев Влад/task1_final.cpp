#include <stdio.h>



typedef long long int  Money;
typedef size_t Percent; // 1% = 100
const size_t years = 30;


struct Bank {
    Money mortgage;
    Money deposit;
    Percent inflation;
    Percent deposit_percent;
    Percent mortgage_percent;
    Percent deposit_percent_month;
    Money mortgage_month;
};

struct Finance {
    Money capital;
    Money salary;
    Money apartment;
    Money rent;
    Money expenses;
    Bank bank_account;
};

struct Finance Bob;
struct Finance Alice;
struct Finance Changes[2][years*12]; // 0 - Alice, 1 - Bob

void init_Bob() {
    Bob.capital = 1000000;
    Bob.salary = 200000;
    Bob.rent = 30000;
    Bob.expenses = 30000;
    Bob.bank_account.deposit = 0;
    Bob.bank_account.deposit_percent = 2000;
    Bob.bank_account.inflation = 800;
    Bob.bank_account.deposit_percent_month = Bob.bank_account.deposit_percent / 12;
}

void init_Alice() {
    Alice.capital = 1000000;
    Alice.salary = 200000;
    Alice.expenses = 20000;
    Alice.apartment = 13000000;
    Alice.apartment -= Alice.capital;
    Alice.capital = 0;
    Alice.bank_account.deposit = 2000;
    Alice.bank_account.inflation = 800;
    Alice.bank_account.deposit_percent_month = Alice.bank_account.deposit_percent / 12;
    Alice.bank_account.mortgage_percent = 1100;
    Alice.bank_account.mortgage = Alice.apartment / 10000 * Alice.bank_account.mortgage_percent;
    Alice.bank_account.mortgage_month = Alice.bank_account.mortgage / (12 * years);
}

void init_Changes() {
    for ( int person = 0; person < 2; ++ person){
        for ( int month = 0; month < years * 12; ++month){
            Changes[person][month].capital = 0;
            Changes[person][month].salary = 0;
            Changes[person][month].apartment = 0;
            Changes[person][month].rent = 0;
            Changes[person][month].expenses = 0;
            Changes[person][month].bank_account.deposit = 0;
            Changes[person][month].bank_account.inflation = 0;
        }
    }
    
}

void Alice_month(int month){
    if(Changes[0][month].salary != 0) Alice.salary = Changes[0][month].salary;
    if(Changes[0][month].rent != 0) Alice.rent = Changes[0][month].rent;
    if(Changes[0][month].expenses != 0) Alice.expenses = Changes[0][month].expenses;
    if(Changes[0][month].bank_account.deposit_percent != 0) {
        Alice.bank_account.deposit_percent = Changes[0][month].bank_account.deposit_percent;
        Alice.bank_account.deposit_percent_month = Alice.bank_account.deposit_percent / 12;
    }
    if(Changes[0][month].bank_account.inflation != 0) Alice.bank_account.inflation = Changes[0][month].bank_account.inflation;
    Alice.capital += Alice.salary;
    Alice.capital -= Alice.bank_account.mortgage_month + Alice.expenses;
    Alice.bank_account.deposit += Alice.capital;
    Alice.capital = 0;
}


void Bob_month(int month){
    if(Changes[1][month].salary != 0) Bob.salary = Changes[1][month].salary;
    if(Changes[1][month].rent != 0) Bob.rent = Changes[1][month].rent;
    if(Changes[1][month].expenses != 0) Bob.expenses = Changes[1][month].expenses;
    if(Changes[1][month].bank_account.deposit_percent != 0) {
        Bob.bank_account.deposit_percent = Changes[1][month].bank_account.deposit_percent;
        Bob.bank_account.deposit_percent_month = Bob.bank_account.deposit_percent / 12;
    }
    if(Changes[1][month].bank_account.inflation != 0) Bob.bank_account.inflation = Changes[1][month].bank_account.inflation;
    Bob.capital += Bob.salary;
    Bob.capital -= Bob.rent + Bob.expenses;
    Bob.bank_account.deposit += Bob.capital;
    Bob.capital = 0;
}

void life_days() {
    for (int month = 0; month < years * 12; ++ month){
        if ((month + 1) % 12 == 0){
        
            Bob.bank_account.inflation += 800;
            Bob.salary = Bob.salary * Bob.bank_account.inflation / (Bob.bank_account.inflation - 800) / 100;
            Bob.rent = Bob.rent * Bob.bank_account.inflation / (Bob.bank_account.inflation - 800) / 100;
            Bob.rent = Bob.rent * Bob.bank_account.inflation / (Bob.bank_account.inflation - 800) / 100;

            Alice.bank_account.inflation += 800;
            Alice.salary = Alice.salary * Alice.bank_account.inflation / (Alice.bank_account.inflation - 800) / 100;
            Alice.apartment = Alice.apartment * Alice.bank_account.inflation / (Alice.bank_account.inflation - 800) / 100;
            Alice.expenses = Alice.expenses * Alice.bank_account.inflation / (Alice.bank_account.inflation - 800) / 100;
        }
        Alice_month(month);
        Bob_month(month);
    }
}
void insert_changes(){
    //Changes[name][month - 1].type;
    
}

void print_result(){
    if (Bob.bank_account.deposit > Alice.bank_account.deposit + Alice.apartment) printf("Bob");
    else printf ("Alice");
}










int main() {
    init_Alice();
    init_Bob();
    init_Changes();
    life_days();
    print_result();
}
