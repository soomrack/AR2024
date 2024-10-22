#include <stdio.h>


int month = 9;
int year = 2024;
double summ1 = 0;
double summ2 = 0;


struct human {
  struct expenses {
    double food;
    double utilities;
    double other;
  };
  struct mortgage {
    double procent;
    double summa_credita;
    double platez_month;
    double first_platez;
    int yers;
  };
  double salary;
  double account;
  double house;
  double rent;
  double deposit;
  double deposit_procent;
};


struct mortgage ALice = {
    .procent = 1.05,
    .summa_credita = 14000*1000,
    .platez_month = 74619,
    .first_platez = 100000,
    .yers = 30
};


struct expenses alice = {
  .food = 30000,
  .utilities = 40000,
  .other = 30000
};


struct human Alice = {
  .salary = 300*1000,
  .account = 0,
  .deposit = 0,
  .deposit_procent = 0
};


struct expenses bob = {
  .food = 30000,
  .utilities = 40000,
  .other = 30000
};


struct human Bob = {
  .salary=300*1000,
  .account=0,
  .rent = 40*1000,
  .deposit = 0,
  .deposit_procent = 1.05
};


void alice_salary(const int month, const int year) {
  if (month == 12) {
      Alice.salary *= 1.09;
  }

  Alice.account += Alice.salary;
}


void alice_expenses(const int month, const int year) {
  if (month == 12) {
      summ1 = (alice.food + alice.other + alice.utilities) * 1.09;
  }

  Alice.account -= (summ1 + ALice.platez_month);
}


void alice_house(const int month, const int year)
{
  Alice.house = ALice.summa_credita;
    if (month == 12) {
        Alice.house *= 1.09;
    }
    if (month == 9 && year == 2024 + ALice.yers) {
        Alice.account += Alice.house;
    }
}


void bob_salary(const int month, const int year) {
  if (month == 12) {
      Bob.salary *= 1.09;
  }

  Bob.account += Bob.salary;
}


void bob_expenses(const int month, const int year) {
  if (month == 12) {
      Bob.rent *= 1.09;
      summ2 = (bob.food + bob.other + bob.utilities) * 1.09;
  }

  Bob.account -= (summ2 + Bob.rent);
}


void bob_deposit(const int month, const int year) {
  if (month == 12) {
      Bob.deposit *= Bob.deposit_procent;
  }

  Bob.deposit += Bob.account; 
}


void simulation() {
  while (!(year == 2024 + ALice.yers && month == 10)) {
    alice_salary(month, year);
    alice_expenses(month, year);
    alice_house(month, year);
    bob_salary(month,year);
    bob_expenses(month, year);
    bob_deposit(month, year);
    month++;

    if (month == 13) {
        year++;
        month = 1;
    }
  }
}


void result() {
  if (Alice.account > Bob.account) {
    printf("Alice is richer on %.0lf\n", Alice.account - Bob.account);
  }
  else {
    printf("Bob is richer on %.0lf\n", Bob.account - Alice.account);
  }
}


int main() {
  simulation();
  result();
  return 0;
}
