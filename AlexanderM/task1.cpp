#include <stdio.h>

int A_salary = 200 * 1000;
int B_salary = 200 * 1000;
long flat = 1400 * 10000;
int A_mortgage = 50 * 1000;
int B_rent = 40 * 1000;
int A_expenses = 50 * 1000;
int B_expenses = 60 * 1000;
long A_account = 0;
int year; int month;
long B_account = 0;

void Alice()
{
    while (year <= 2024 + 30)
    {
        A_account += A_salary;
        A_account -= A_expenses - A_mortgage;

        month++;
        if (month == 13)
        {
            year++;
            month = 1;
        }

        if (month == 12)
        {
            A_salary *= 1.08;
            flat *= 1.08;  // индексация //
            A_expenses *= 1.08;
        }
        if (year == 2024 + 30 && month == 10) break;
    }
    A_account += flat;
}

void Bob()
{
    while (year <= 2024 + 30)
    {
        B_account += B_salary;
        B_account -= B_expenses -= B_rent;

        month++;
        if (month == 13)
        {
            year++;
            month = 1;
        }

        if (month == 12)
        {
            B_salary *= 1.08;
            B_expenses *= 1.08; // индексация //
            B_rent *= 1.08;
        }
        if (year == 2024 + 30 && month == 10) break;
    }
}

void result()
{
    if (B_account > A_account)
    {
        printf("Bob has more money than Alice!\n");
    }
    else
    {
        printf("Alice has more money then Bob!\n");
    }
}

int main()
{
    Alice();
    Bob();
    result();
    return 0;
}