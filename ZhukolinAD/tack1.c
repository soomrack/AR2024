#include <stdio.h>


int month = 9;
int year = 2024;
double summ1 = 0;
double summ2 = 0;

struct human{
  struct expenses{
    double food;
    double utilities;
    double other;
  };
  double salary;
  double account;
  double house;
  double rent;
  double mortgage;
  double deposit;
  double living;
};


struct expenses alice = {
  .food = 30000,
  .utilities = 12000,
  .other = 30000
};


struct human Alice = {
  .salary=300*1000,
  .living=100*1000,
  .account=0,
  .house=14000*1000,
  .rent=0,
  .mortgage=150*1000,
  .deposit=1.15
};


struct expenses bob = {
  .food = 30000,
  .utilities = 12000,
  .other = 50000
};

struct human Bob = {
  .salary=300*1000,
  .living=100*1000,
  .account=0,
  .house=0,
  .rent=40*1000,
  .mortgage=0,
  .deposit=1.15
};


void alice_house(int month, int year) {
  if (month == 12) {
    Alice.house *= 1.07;
  }
  if (month == 9 && year == 2054) {
    Alice.account += Alice.house;
  }
}


void alice_salary(int month, int year) {
  if (month == 12) {
      Alice.salary *= 1.07;
      Alice.account *= Alice.deposit;
  }

  Alice.account += Alice.salary;
}


void alice_expenses(int month, int year) {
  if (month == 12) {
      Alice.living *= 1.07;
      summ1 = (alice.food + alice.other + alice.utilities) * 1.07;
  }

  Alice.account += Alice.living - summ1 - Alice.mortgage;
}


void bob_salary(int month, int year) {
  if (month == 12)
  {
      Bob.salary *= 1.07;
      Bob.account *= Bob.deposit;
  }

  Bob.account += Bob.salary;
}

void bob_expenses(int month, int year) {
  if (month == 12)
  {
      Bob.living *= 1.07;
      Bob.rent *= 1.07;
      summ2 = (bob.food + bob.other + bob.utilities) * 1.07;
  }

  Bob.account += Bob.living - summ2 - Bob.rent;
}


void simulation() {
  while (!(year == 2054 && month == 10)) {
    alice_house(month, year);
    alice_salary(month, year);
    alice_expenses(month, year);
    bob_salary(month,year);
    bob_expenses(month, year);
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
