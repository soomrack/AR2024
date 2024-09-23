#include <stdio.h>

typedef long long int Money;
struct Depasit{
    Money account;
    double interest;
};

Money expenditure = 399 + 22500 + 5000 + 4500;
long double inflation = 0.0742;
Money rent = 30000;
Money monthly_payment = 226312;
Money salary = 300000;
Money alice_credit = 11687000;
Money apartment_price = 13000000;
int month_counter = 1;
struct Depasit alice_depasite;
struct Depasit bob_depasite;

void alice_init(){
	alice_depasite.account = 0;
	alice_depasite.interest = 0,19;
}

void bob_init(){
	bob_depasite.account = 1313000;
	bob_depasite.interest = 0,19;
}

void alice_expense_counting(){
	alice_depasite.account += alice_depasite.account * alice_depasite.interest / 12;
	alice_depasite.account += salary - expenditure - monthly_payment;
	alice_credit -= monthly_payment;
};

void bob_expense_counting(){
	bob_depasite.account += bob_depasite.account * bob_depasite.interest / 12;
	bob_depasite.account += salary - expenditure - rent;
};

void print(){
    if (bob_depasite.account >= apartment_price){
		printf("Боб купил квартиру быстрее.\nСчёт Боба: %lld.\nСчёт Алисы: %lld.\n", bob_depasite.account, alice_depasite.account);
	};
	if (alice_credit <= 0){
		printf("Алиса купила квартиру быстрее.\nСчёт Алисы: %lld.\nСчёт Боба: %lld.\n", alice_depasite.account, bob_depasite.account);
	};
};

void inflation_changes(){
    month_counter ++;
	if (month_counter == 13) {
		expenditure += expenditure * inflation;
		rent += rent * inflation;
		salary += salary * inflation;
		apartment_price += apartment_price * inflation;
        month_counter = 1;
	};
};

int main(){
	while (bob_depasite.account < apartment_price && alice_credit > 0){

		alice_init();		

		bob_init();		

        alice_expense_counting();

        bob_expense_counting();

        inflation_changes();

		print();
	};
    return 1;
}
