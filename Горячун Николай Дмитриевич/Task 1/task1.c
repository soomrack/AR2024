#include <stdio.h>
void main(){
    typedef long long int Money;
	Money expenditure = 399 + 22500 + 5000 + 4500;
	long double inflation = 0.0742;
    Money rent = 30000;
	Money monthly_payment = 226312;
	Money salary = 300000;
	Money alice_credit = 11687000;
	Money apartment_price = 13000000;
	int month_counter = 1;
	int end_loop = 0;
    struct Depasit{
        Money account;
        double interest;
    };
    struct Depasit alice_depasite;
        alice_depasite.account = 0;
        alice_depasite.interest = 0,19;
    struct Depasit bob_depasite;
        bob_depasite.account = 1313000;
        bob_depasite.interest = 0,19;
	while (end_loop != 1){
		month_counter ++;
		if (month_counter == 13) {
			expenditure += expenditure * inflation;
			rent += rent * inflation;
			salary += salary * inflation;
			apartment_price += apartment_price * inflation;
		};
		alice_depasite.account += alice_depasite.account * alice_depasite.interest / 12;
		bob_depasite.account += bob_depasite.account * bob_depasite.interest / 12;
		alice_depasite.account += salary - expenditure - monthly_payment;
		alice_credit -= monthly_payment;
		bob_depasite.account += salary - expenditure - rent;
		if (bob_depasite.account >= apartment_price){
			printf("Боб купил квартиру быстрее.\nСчёт Боба: %lld.\nСчёт Алисы: %lld.\n", bob_depasite.account, alice_depasite.account);
			end_loop = 1;
		};
		if (alice_credit <= 0){
			printf("Алиса купила квартиру быстрее.\nСчёт Алисы: %lld.\nСчёт Боба: %lld.", alice_depasite.account, bob_depasite.account);
			end_loop = 1;
		};
	};
}
