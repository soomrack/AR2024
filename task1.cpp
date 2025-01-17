#include <stdio.h>

typedef long long int Money;

// 猫的结构体
struct Cat {
    Money catfood;
    int life_cat;
};

// 抵押贷款结构体
struct Mortgage {
    Money mortgage;
    Money month_mortgage;
};

// 人员结构体
struct Person {
    Money salary;
    Money expenses;
    Money flat;
    Money rent_flat;
    Money account;
    struct Cat person_cat;
    struct Mortgage person_mortgage;
};

struct Person Bob;
struct Person Alice;

// 初始化 Bob 的信息
void Bob_init()
{
    // 初始化 Bob 的账户余额、工资、日常开销和租房费用
    Bob.account = 1200000;
    Bob.salary = 300000;
    Bob.expenses = 40000;
    Bob.rent_flat = 35000;
    // 为了避免未定义行为，将未使用的成员初始化为 0
    Bob.flat = 0;
    Bob.person_cat.catfood = 0;
    Bob.person_cat.life_cat = 0;
    Bob.person_mortgage.mortgage = 0;
    Bob.person_mortgage.month_mortgage = 0;
}


// 初始化 Alice 的信息
void Alice_init()
{
    // 初始化 Alice 的账户余额、工资、日常开销、房产价值等
    Alice.account = 1200000;
    Alice.salary = 300000;
    Alice.expenses = 40000;
    Alice.flat = 13000000;
    Alice.person_cat.catfood = 7000;
    Alice.person_cat.life_cat = 15;

    // 计算抵押贷款金额和每月还款额
    Alice.person_mortgage.mortgage = Alice.flat;
    Alice.person_mortgage.mortgage -= Alice.account;
    Alice.person_mortgage.mortgage *= 1.2;
    Alice.account = 0;
    Alice.person_mortgage.month_mortgage = Alice.person_mortgage.mortgage / (30 * 12);
}


// 更新人员的工资
void Alice_salary(const int month, const int year) {
    if (month == 12) {
        Alice.account += Alice.salary; // 奖金，数额等于工资
    }
    if (month == 1) {
        Alice.salary *= 1.05;  // 1月工资上涨5%
    }
    Alice.account += Alice.salary;
}



// 更新人员的日常开销
void update_expenses(struct Person* person, const int month, const int year)
{
    person->account -= person->expenses;
    if (month == 1) {
        person->expenses *= 1.06;
    }
}


// 更新人员的租房费用
void update_rent_flat(struct Person* person, const int month, const int year)
{
    if (person->rent_flat != 0) {
        person->account -= person->rent_flat;
        if (month == 1) {
            person->rent_flat *= 1.06;
        }
    }
}


// 更新人员的存款
void update_deposit(struct Person* person, const int month, const int year)
{
    person->account *= 1 + (0.2 / 12);
}


// 更新 Alice 的房产价值
void update_flat(struct Person* person, const int month, const int year)
{
    if (month == 1) {
        person->flat *= 1.06;
    }
}


// 更新 Alice 的抵押贷款还款
void update_mortgage(struct Person* person)
{
    person->account -= person->person_mortgage.month_mortgage;
}


// 更新 Alice 的养猫费用
void update_cat(struct Person* person, const int month, const int year)
{
    if (month == 1) {
        person->person_cat.catfood *= 1.06;
    }
    if ((year >= 2027) && (year <= (2027 + person->person_cat.life_cat))) {
        person->account -= person->person_cat.catfood;
    }
}


// 模拟财务状况
void simulation()
{
    int month = 1;
    int year = 2024;
    // 从 2024 年 1 月开始模拟，直到 2054 年 1 月
    while (!(month == 1 && year == 2054)) {
        update_salary(&Bob, month, year);
        update_expenses(&Bob, month, year);
        update_rent_flat(&Bob, month, year);
        update_deposit(&Bob, month, year);

        update_salary(&Alice, month, year);
        update_expenses(&Alice, month, year);
        update_flat(&Alice, month, year);
        update_mortgage(&Alice);
        update_deposit(&Alice, month, year);
        update_cat(&Alice, month, year);

        month++;
        if (month == 13) {
            month = 1;
            year++;
        }
    }
}


// 打印比较结果
void print()
{
    if (Alice.account + Alice.flat < Bob.account) {
        printf("Bob will save up for a flat faster");
    }
    else {
        printf("Alice will pay off the mortgage faster");
    }
}


int main()
{
    Alice_init();
    Bob_init();

    simulation();

    print();
    return 0;
}