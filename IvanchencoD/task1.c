#include <stdio.h>


// Определение типа для денег
typedef long long int Money;


// Структура для ипотеки
struct Mortgage 
{
    double rate;          // Процентная ставка
    Money credit;         // Размер кредита
    Money pay;            // Текущий долг
    Money month_pay;      // Ежемесячный платеж
};


// Структура для банка
struct Bank 
{
    Money contribution;   // Вклад
    Money month_pay;      // Ежемесячный вклад
};


// Структура для индивида
struct Individual 
{
    Money salary;                   // Зарплата
    Money monthly_expenses;         // Ежемесячные расходы
    Money status;                   // Текущий капитал
    Money apartment;                 // Стоимость квартиры
    Money free_money;               // Рубли на руках
    struct Mortgage mortgage;
    struct Bank bank;
};


// Объявляем глобальные структуры
struct Individual Alice;
struct Individual Bob;


// Инициализация данных для Алисы
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


// Алиса платит ипотеку
void Alice_pay_mortgage()
{
    Alice.status -= Alice.mortgage.month_pay;
}


// Зарплата Алисы
void Alice_update_salary(int month) 
{
    if (month == 12) {
        Alice.status += Alice.salary;
    }
    if (month == 1) {
        Alice.salary *= 1.09; // Индексация зарплаты
    }
    Alice.status += Alice.salary;
}


// Печать о капитале Алисы
void Alice_print() 
{
    if (Alice.status > Bob.status) {
        printf ("Alice has more money than Bob on %lld\n", Alice.status - Bob.status);
    }

    printf("Alice's capital: %lld \n", Alice.status);
}


// Инициализация данных для Боба
void initialize_Bob()
{
    Bob.status = 0;
    Bob.salary = 230 * 1000;
    Bob.monthly_expenses = 70 * 1000;
    Bob.apartment = 30 * 1000; 
    Bob.free_money = 0;
    Bob.bank.month_pay = 130 * 1000;
}


// Зарплата Боба
void Bob_update_salary(int month) 
{
    if (month == 12) {
        Bob.status += Bob.salary;
    }
    if (month == 1) {
        Bob.salary *= 1.09; // Индексация зарплаты
    }
    Bob.status += Bob.salary;
}

// Депозит Боба
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


// Печать о капитале Боба
void Bob_print() 
{
    if (Alice.status < Bob.status) {
        printf ("Bob has more money than Alice on %lld\n", Bob.status - Alice.status);
    }

    printf("Bob's capital: %lld \n", Bob.status);
}


// Симуляция работы программы
void simulation() 
{
    int month = 9;
    int year = 2024;

    while (!(month == 9 && year == 2054)) {
        // Обновление зарплаты и других данных Алисы
        Alice_update_salary(month);
        Alice_pay_mortgage();

        // Обновление зарплаты Боба
        Bob_update_salary(month);

        // Переход к следующему месяцу
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