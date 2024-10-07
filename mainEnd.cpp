#include<stdio.h>
#include<math.h>

double x, y;
typedef long long int money; // ���������� ������������ long long

struct Deposits
{
    double pct; // ������� ������
    money capital;
    money deposits_month_refill;
};

struct Hypothec {  // �������
    double protsent;
    money credit;
    money platez;
    money month_pay;
};

struct Robotics {   // �����
    money courses;
    int is_interesting;
};

struct Basketball {  // �����
    money lesson;
    int is_interesting;
};

struct Car
{
    money petrol;  // ������
    money insurance; // ���������
    money maintenance; // ���. ������������
};


struct Human {
    money salary;
    money account;
    money food;
    money other; // ������ ����������
    struct Hypothec hypothec;
    struct Basketball basketball;
    struct Robotics robotics;
    struct Car car;
    struct Deposits deposits;
};

struct Human alice;
struct Human bob;


void alice_hypothec()
{
    alice.account -= alice.hypothec.month_pay;

}


void alice_food(const int month)
{
    if (month == 1) {
        alice.food *= 1.08;
    }
    alice.account -= alice.food;
}

void alice_other(const int month)
{
    if (month == 1) {
        alice.account -= 6750;
    }
    alice.account -= alice.other;
}

void alice_init()
{
    alice.account = 1000 * 1000;
    alice.salary = 350 * 1000;
    alice.food = 10 * 1000;
    alice.other = 70 * 1000;

    alice.hypothec.platez = 500 * 1000;
    alice.hypothec.credit = 14000 * 1000;
    alice.hypothec.protsent = 0.14;
    alice.hypothec.month_pay = alice.hypothec.credit * ((x) / (y));
    alice.account -= alice.hypothec.platez;
    alice.hypothec.credit -= alice.hypothec.month_pay;

    x = alice.hypothec.protsent * pow(1 + alice.hypothec.protsent, 360);
    y = pow(1 + alice.hypothec.protsent, 360) - 1;

    alice.robotics.courses = 5000;
    alice.robotics.is_interesting = 0;

    alice.basketball.lesson = 2500;
    alice.robotics.is_interesting = 0;
}

void alice_robotics(const int month, const int year)
{
    if ((month == 12) && (year == 2025))
    {
        alice.account -= 45000;
        alice.robotics.is_interesting = 1;
    }
    if ((year == 2032) && (month == 9))
    {
        alice.robotics.is_interesting = 0;
    }
    if (month == 1)
    {
        alice.robotics.courses *= 1.09;
    }
    if (alice.robotics.is_interesting == 1)
    {
        alice.account -= alice.robotics.courses;
    }
}

void alice_basketball(const int month, const int year)
{
    if ((month == 2) && (year == 2033))
    {
        alice.account -= 27500;
        alice.basketball.is_interesting = 1;
    }
    if ((year == 2040) && (month == 6))
    {
        alice.basketball.is_interesting = 0;
    }
    if (month == 1)
    {
        alice.basketball.lesson *= 1.09;
    }
    if (alice.basketball.is_interesting == 1)
    {
        alice.account -= alice.basketball.lesson;
    }
}

void alice_salary(int month) // ��������� �������� � ���� � ���������
{
    if (month == 12) {
        alice.account += alice.salary;
    }
    if (month == 1)
    {
        alice.salary *= 1.09;
    }
    alice.account += alice.salary;
}

void bob_other(const int month)
{
    if (month == 1)
    {
        bob.account -= 6750;
    }
    bob.account -= bob.other;
}

void bob_food(const int month)
{
    if (month == 1)
    {
        bob.food *= 1.08;
    }
    bob.account -= bob.food;
}

void bob_deposits()
{
    bob.account += bob.deposits.deposits_month_refill;

}

void bob_init()
{
    bob.account = 1000 * 1000;
    bob.salary = 200 * 1000;
    bob.food = 10 * 1000;
    bob.other = 70 * 1000;

    bob.deposits.pct = 0.12;
    bob.deposits.capital = 100 * 1000 + bob.deposits.deposits_month_refill;
    bob.deposits.deposits_month_refill = (bob.deposits.capital * pow(1 + (bob.deposits.pct), 1)) - bob.deposits.capital;

    bob.robotics.courses = 5000;
    bob.robotics.is_interesting = 0;

    bob.car.petrol = 8000;
    bob.car.insurance = 3339;
    bob.car.maintenance = 6000;

}

void bob_car(const int month, const int year)
{
    if ((month == 12) && (year == 2030))
    {
        bob.account -= 500 * 1000;
        bob.account -= bob.car.petrol;
        bob.account -= bob.car.insurance;
        bob.account -= bob.car.maintenance;
    }
    if (month == 1)
    {
        bob.car.petrol *= 1.09;
        bob.account -= bob.car.insurance;
        bob.account -= bob.car.maintenance;
    }
    bob.account -= bob.car.petrol;
}

void bob_robotics(const int month, const int year)
{
    if ((month == 12) && (year == 2025))
    {
        bob.account -= 45000;
        bob.robotics.is_interesting == 1;
    }
    if ((year == 2032) && (month == 9))
    {
        bob.robotics.is_interesting == 0;
    }
    if (month == 1)
    {
        bob.robotics.courses *= 1.09;
    }
    if (bob.robotics.is_interesting == 1)
        bob.account -= bob.robotics.courses;
}


void bob_salary(int month) // ��������� �������� � ���� � ���������
{
    if (month == 12) {
        alice.account += alice.salary;
    }
    if (month == 1)
    {
        alice.salary *= 1.09;
    }
    alice.account += alice.salary;
}

void simulation() // ������� ���(�����) � � ���������� �������� ���� � ����
{
    int month = 9;
    int year = 2024;

    while (!((month == 9) && (year == 2024 + 30))) {
        alice_init();
        alice_salary(month);
        alice_food(month);
        alice_other(month);
        alice_basketball(month, year);
        alice_robotics(month, year);
        alice_hypothec();
        bob_init();
        bob_salary(month);
        bob_food(month);
        bob_other(month);
        bob_robotics(month, year);
        bob_car(month, year);

        month++;
        if (month == 13)
        {
            month = 1;
            year++;
        }
    }
}

void alice_print()
{
    printf("Alice account = %lld \n", alice.account); // kapital
}

void bob_print()
{
    printf("Bob account = %lld \n", bob.account); // kapital
}

int main()
{
    alice_init();

    simulation();

    alice_print();
    return 1;
}