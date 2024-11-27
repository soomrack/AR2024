#include <stdio.h>
#include <windows.h>
#include <locale.h>  // Подключаем для использования setlocale()

typedef long long Money;
int month = 9;
int year = 2024;

struct Person {
    Money salary;
    Money money_for_living;
    Money spendings;
    Money mortgage;
    Money account;
    Money house;
    Money house_rent;
};

struct Person Alice = { 300 * 1000, 100 * 1000, 0, 180 * 1000, 0, 14000 * 1000, 400 * 100 };
struct Person Bob = { 300 * 1000, 100 * 1000, 0, 180 * 1000, 0, 14000 * 1000, 400 * 100 };

void bob_salary(const int month, const int year) {
    if (month == 12) {
        Bob.salary *= 1.07; // Индексация зарплаты Боба в декабре
    }
    Bob.account += Bob.salary; // Прибавляем зарплату к счёту Боба
}

void bob_spendings(const int month, const int year) {
    if (month == 12) {
        Bob.money_for_living *= 1.08; // Индексация расходов на жизнь Боба в декабре
        Bob.house_rent *= 1.08;        // Индексация аренды Боба в декабре
    }
    Bob.spendings = Bob.money_for_living + Bob.house_rent; // Суммируем все расходы Боба
    Bob.account -= Bob.spendings; // Вычитаем расходы из счёта Боба
}

void alice_salary(const int month, const int year) {
    static Money better_salary = Alice.salary * 1.5; // Для использования улучшенной зарплаты в будущем
    if (month == 12) {
        Alice.salary *= 1.07; // Индексация зарплаты Алисы в декабре
        Alice.house *= 1.08;  // Удорожание дома Алисы в декабре
    }
    Alice.account += Alice.salary; // Прибавляем зарплату к счёту Алисы
    if (month == 9 && year == 2054) {
        Alice.account += Alice.house; // В сентябре 2054 года Алиса получает стоимость дома
    }
    if (year == 2028 && month == 3) {
        Alice.salary = 0; // В марте 2028 года Алиса остаётся без зарплаты
    }
    if (year == 2028 && month == 4) {
        Alice.salary = 0; // В апреле 2028 года Алиса остаётся без зарплаты
    }
    if (year == 2028 && month == 5) {
        Alice.salary = better_salary; // В мае 2028 года Алиса получает улучшенную зарплату
    }
}

void alice_spendings(const int month, const int year) {
    if (month == 12) {
        Alice.money_for_living *= 1.08; // Индексация расходов на жизнь Алисы в декабре
    }
    Alice.spendings = Alice.money_for_living + Alice.mortgage; // Суммируем все расходы Алисы (включая ипотеку)
    Alice.account -= Alice.spendings; // Вычитаем расходы из счёта Алисы
}

void simulation() {
    while (!(year == 2054 && month == 10)) {
        alice_salary(month, year);   // Рассчитываем зарплату Алисы
        alice_spendings(month, year); // Рассчитываем расходы Алисы
        bob_salary(month, year);     // Рассчитываем зарплату Боба
        bob_spendings(month, year);  // Рассчитываем расходы Боба
        month++;
        if (month == 13) {
            year = year + 1;
            month = 1;
        }
    }
}

void result() {
    // Выводим результаты на экран
    if (Alice.account > Bob.account) {
        printf("Алиса богаче на: %lld\n", Alice.account - Bob.account);
    }
    else {
        printf("Боб богаче на: %lld\n", Bob.account - Alice.account);
    }
}

int main() {
    // Устанавливаем локаль для корректной работы с русскими символами
    setlocale(LC_ALL, "Russian_Russia.1251"); // Устанавливаем локаль для работы с русскими символами в Windows

    simulation(); // Запуск симуляции
    result();     // Вывод результатов на экран

    return 0;
}
