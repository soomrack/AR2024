#include <stdio.h>

// 定义表示金额的类型别名，这里假设为美元（USD）
typedef long long int Money;

// 结构体表示宠物相关信息
struct Pet {
    Money food;
    int is_healthy;
};

// 结构体表示贷款相关信息
struct Loan {
    double interest_rate;
    Money loan_amount;
    Money down_payment;
    Money monthly_payment;
};

// 结构体表示人物的财务及生活相关情况
struct Person {
    Money salary;
    Money account;
    Money grocery;
    Money other_expenses;
    struct Loan loan;
    struct Pet pet;
};

// 全局变量声明，代表人物Tom
struct Person tom;

// 处理每月的贷款还款操作
void tom_loan_payment() {
    tom.account -= tom.loan.monthly_payment;
}

// 根据月份处理食品杂货费用
void tom_grocery(const int month) {
    if (month == 1) {
        tom.grocery *= 1.05;  // 每年1月食品杂货费用上涨5%
    }
    tom.account -= tom.grocery;
}

// 根据月份处理其他费用支出
void tom_other_expenses(const int month) {
    if (month == 2) {
        tom.account -= 3000;  // 2月有额外的一笔其他费用支出
    }
    tom.account -= tom.other_expenses;
}

// 初始化Tom的各项财务及生活相关数据
void tom_init() {
    tom.account = 800 * 1000;
    tom.salary = 180 * 1000;
    tom.grocery = 8 * 1000;
    tom.other_expenses = 60 * 1000;

    tom.loan.interest_rate = 0.15;
    tom.loan.loan_amount = 12000 * 1000;
    tom.loan.down_payment = 800 * 1000;
    tom.loan.monthly_payment = 90 * 1000;
    tom.account -= tom.loan.down_payment;

    tom.pet.food = 4000;
    tom.pet.is_healthy = 1;
}

// 根据月份和年份处理宠物相关的财务操作
void tom_pet(const int month, const int year) {
    if ((month == 10) && (year == 2025)) {
        tom.account -= 25000;  // 带宠物看病等大额支出
        tom.pet.is_healthy = 0;
    }
    if ((year == 2040) && (month == 6)) {
        tom.pet.is_healthy = 1;
        tom.account -= 2000;  // 宠物健康相关费用
    }
    if (month == 1) {
        tom.pet.food *= 1.08;  // 1月宠物食品费用上涨8%
    }
    if (tom.pet.is_healthy == 1) {
        tom.account -= tom.pet.food;
    }
}

// 处理工资相关操作
void tom_salary(const int month, const int year) {
    if (month == 12) {
        tom.account += tom.salary;
    }
    if (month == 1) {
        tom.salary *= 1.05;  // 1月工资上涨5%
    }
    tom.account += tom.salary;
}

// 模拟函数，模拟一定时间范围内Tom的财务状况变化
void simulation() {
    int month = 7;
    int year = 2024;

    while (!((month == 7) && (year == 2024 + 30))) {
        tom_salary(month, year);
        tom_loan_payment();
        tom_grocery(month);
        tom_other_expenses(month);
        tom_pet(month, year);

        month++;
        if (month == 13) {
            month = 1;
            year++;
        }
    }
}

// 输出Tom的账户余额情况
void tom_print() {
    printf("Tom account = %lld \n", tom.account);
}

int main() {
    tom_init();
    simulation();
    tom_print();
    return 0;
}