#include <stdio.h>

typedef long long int Money; //RUR

long double inflation = 0.10;
Money alice_flat_cost = 10 * 1000 * 1000;
Money bob_yacht_cost = 5 * 1000 * 1000;
Money yacht_trip_cost = 500 * 1000;


struct Deposit{
    Money deposit_account;
    double rate;
    Money month_pay;
};


struct Mortgage{
    double rate;
    Money credit;
    Money platez; 
    Money month_pay;
};


struct Person{
    Money salary;
    Money account;
    Money food;
    Money expences;
    Money rent;

    struct Mortgage mortgage;
    struct Deposit deposit;
};

struct Person alice;
struct Person bob;

void alice_init()
{
    alice.account = 1000 * 1000;
    alice.salary = 200 * 1000;
    alice.food = 17 * 1000;
    alice.expences = 40 * 1000;

    alice.mortgage.rate = 0.19;
    alice.mortgage.credit = 10 * 1000 * 1000;
    alice.mortgage.platez = 1000 * 1000;
    alice.mortgage.month_pay = 143 * 1000;
    alice.account -= alice.mortgage.platez;

    alice.deposit.deposit_account;
    alice.deposit.rate = 0.20;
}


void alice_expences(const int month)
{
    alice.account -= alice.expences;
    if (month == 1){
       alice.expences += alice.expences * inflation;
    }
}

void alice_food(const int month)
{
    alice.account -= alice.food;
    if (month == 1){
       alice.food += alice.food * inflation;
    }
}

void alice_salary(const int month)
{
    alice.account += alice.salary;
    if (month == 1){
       alice.salary += alice.salary * inflation;
    }
}

void alice_mortgage()
{
    alice.account -= alice.mortgage.month_pay;
}

void alice_deposit()
{
    alice.deposit.deposit_account += alice.deposit.deposit_account * alice.deposit.rate / 12;
    alice.deposit.deposit_account += alice.salary - alice.food - alice.expences - alice.mortgage.month_pay;
}

void alice_flat_cost_height(const int month)
{
    if (month == 1){
       alice_flat_cost += alice_flat_cost * inflation;
    }
}

void alice_print()
{
    printf("Alice account = %lld \n", alice_flat_cost + alice.account + alice.deposit.deposit_account);
}


void bob_init()
{
    bob.account == 1000 * 1000;
    bob.salary = 200 * 1000;
    bob.food = 17 * 1000;
    bob.expences = 40 * 1000;

    bob.deposit.deposit_account += bob.account;
    bob.account = 0;
    bob.deposit.rate = 0.20;

    bob.rent = 30 * 1000;
}

void bob_expences(const int month)
{
    bob.account -= bob.expences;
    if (month == 1){
       bob.expences += bob.expences * inflation;
    }
}


void bob_food(const int month)
{
    bob.account -= bob.food;
    if (month == 1){
       bob.food += bob.food * inflation;
    }
}

void bob_salary(const int month, const int year)
{
    if (!((year >= 2024 + 3) && (month == 8))){  // взял отпуск за свой счет
       bob.account += bob.salary;
       }
    if (month == 1){
        bob.salary += bob.salary * inflation;
    }
}

void bob_rent(const int month)
{
    bob.account -= bob.rent;
    if (month == 1){
       bob.rent += bob.rent * inflation;
    }
}

void bob_deposit()
{
    bob.deposit.deposit_account += bob.deposit.deposit_account * alice.deposit.rate / 12;
    bob.deposit.deposit_account += bob.account;
    bob.account = 0;
}

void bob_yacht(const int month, const int year)
{
    if (year >= 2024 + 3){
       if ((year == 2024 + 3) && (month == 6)){  // покупка яхты
          bob.account -= bob_yacht_cost;
       }
       bob.account -= bob_yacht_cost / 12 / 10;  // затраты на содержание яхты(годовая стоимость содержания яхты приблизительно равно 10% её стоимости)
       if (month == 1){
          bob_yacht_cost += bob_yacht_cost * inflation;
          yacht_trip_cost += yacht_trip_cost * inflation;
       }
       if (month == 8){
          bob.account -= yacht_trip_cost;
          yacht_trip_cost += yacht_trip_cost * inflation;
       }
    }
}

void bob_print()
{
    printf("Bob account = %lld \n", bob.account + bob.deposit.deposit_account + bob_yacht_cost);
}


void simulation()
{
    int month = 10;
    int year = 2024;
    while (!((month == 10) && (year == 2024 + 30))) {
       alice_flat_cost_height(month);
       alice_salary(month);
       alice_mortgage();
       alice_food(month);
       alice_expences(month);
       alice_deposit();
 
       bob_salary(month,year);
       bob_food(month);
       bob_expences(month);
       bob_yacht(month, year);
       bob_deposit();
 
 
       month++;
       if (month == 13){
          month = 1;
          year++;
       }
    }
}


void result()
{
    if (alice_flat_cost + alice.account + alice.deposit.deposit_account >= bob.account + bob.deposit.deposit_account + bob_yacht_cost)
    {
       printf("Alice won\n");
    }
    else{
       printf("Bob won\n");
    }
}


int main()
{
    bob_init();
    alice_init();
    
    simulation();
 
    alice_print();
    bob_print();
    result();
    return 1;
}
