#include <stdio.h>


typedef long long int Money;


int month = 9;
int year = 2024;


struct Human {
  Money salary;
  Money account;
  Money house;
  Money rent;
  Money deposit;
  double deposit_procent;
};


struct Expenses {
  Money food;
  Money utilities;
  double other;
};


struct Mortgage {
  double procent;
  Money summa_credita;
  Money platez_month;
  Money first_platez;
  int yers;
};


struct Mortgage ALice = {
    .procent = 1.04,
    .platez_month = 141745,
    .yers = 10
};


struct Expenses alice = {
  .food = 30000,
  .utilities = 40000,
  .other = 30000
};


struct Human Alice = {
  .salary = 300*1000,
  .house = 14 * 1000 * 1000,
  .account = 0,
  .deposit = 0,
  .deposit_procent = 1.05
};


struct Expenses bob = {
  .food = 40000,
  .utilities = 40000,
  .other = 100000
};


struct Human Bob = {
  .salary=300*1000,
  .account=0,
  .rent = 40*1000,
  .deposit = 1000000,
  .deposit_procent = 1.05
};


void alice_salary(const int month, const int year) {
  if (month == 12) {
      Alice.salary *= 1.07;
  }

  Alice.account += Alice.salary;
}


void alice_expenses(const int month, const int year) {
  if (month == 12) {
      alice.food *= 1.07;
      alice.other *= 1.07;
      alice.utilities *= 1.07;
  }

  Alice.account -= (alice.food + alice.other + alice.utilities);
}


void alice_mortgage(const int month, const int year) {
	Alice.account -= ALice.platez_month;
}; 


void alice_deposite(const int month, const int year) {
  Alice.deposit += Alice.account;
  Alice.account = 0;
  Alice.deposit *= Alice.deposit_procent;
}


void alice_cost_house(const int month, const int year) {
    if (month == 12) {
        Alice.house *= 1.07;
    }
    if (month == 9 && year == 2024 + ALice.yers) {
        Alice.deposit += Alice.house;
    }
}


void bob_salary(const int month, const int year) {
  if (month == 12) {
      Bob.salary *= 1.07;
  }

  Bob.account += Bob.salary;
}


void bob_expenses(const int month, const int year) {
  if (month == 12) {
      Bob.rent *= 1.07;
      bob.food *= 1.07;
      bob.other *= 1.07;
      bob.utilities *= 1.07;
  }

  Bob.account -= (bob.food + bob.other + bob.utilities + Bob.rent);
}


void bob_deposit(const int month, const int year) { 
  Bob.deposit += Bob.account;
  Bob.account = 0;
  Bob.deposit *= Bob.deposit_procent;
}



void simulation() {
  while (!(year == 2024 + ALice.yers && month == 10)) {
    alice_salary(month, year); // зп
    alice_expenses(month, year); // расходы
    alice_mortgage(month, year); // платёж по ипотеке
    alice_deposite(month, year); // вклад под проценты
    alice_cost_house(month, year); // индексация стоимости дома

    bob_salary(month, year); // зп
    bob_expenses(month, year); // расходы
    bob_deposit(month, year); // вклад под проценты
    
    month++;
    if (month == 13) {
        year++;
        month = 1;
    }
  }
}


void result() {
  if (Alice.deposit > Bob.deposit) {
    printf("Alice is richer on %lld\n", Alice.deposit - Bob.deposit);
  }
  else {
    printf("Bob is richer on %lld\n", Bob.deposit - Alice.deposit);
  }
}


int main() 
{
  simulation();
  result();
  return 0;
}