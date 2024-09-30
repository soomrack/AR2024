#include <stdio.h>
#include <math.h>
int main()
{
    int count_of_years;
    printf("Count of years: ");
    scanf("%d", &count_of_years);
    int infl;
    printf("Inflation: ");
    scanf("%d", &infl);

    double deposit_percent;
    printf("Deposit percent: ");
    scanf("%lf", &deposit_percent);
    deposit_percent = pow(deposit_percent, 1/12);

    int ap_cost;
    int fee;
    int ip_percent;
    printf("Alices appartments cost: ");
    scanf("%d", &ap_cost);
    printf("Fee before months payments: ");
    scanf("%d", &fee);
    printf("Hypothec percent: ");
    scanf("%d", &ip_percent);

    int _months_left = 12 * count_of_years;
    
    int bobs_salary;
    printf("Bobs salary: ");
    scanf("%d", &bobs_salary);
    int alices_salary;
    printf("Alices salary: ");
    scanf("%d", &alices_salary);

    double eats_spendings;
    double utility_spendings;
    double ap_spendings;
    printf("Bobs spendings for appartments per month: ");
    scanf("%lf", &ap_spendings);
    printf("Spendings for food per month: ");
    scanf("%lf", &eats_spendings);
    printf("Alice`s utilities spendings: ");
    scanf("%lf", &utility_spendings);
    double B(double deposit, double kvartira, double eats, int mounth_left, double doxod){
        if (mounth_left == 0){
            return deposit;
        }
        deposit += doxod - (kvartira + eats);
        deposit *= (deposit_percent/100 + 1);
        if ((_months_left - mounth_left) % 12 == 0 && _months_left != mounth_left){
            return B(deposit, kvartira * (infl/100 + 1),eats * (infl/100 + 1), mounth_left - 1,
                doxod * (infl/100 + 1));
        }
        return B(deposit, kvartira, eats, mounth_left - 1, doxod);
    } 
    double A(double salary, double deposit, double ap_cost, double eats, double komunalka, int mounth_left, double credit_left){
        if (mounth_left == 0){
            return deposit + ap_cost;
        }
        double ip_spendings = credit_left / (mounth_left + credit_left * ip_percent / 12);
        deposit += salary - komunalka - eats - ip_spendings;
        deposit *= (deposit_percent/100 + 1);
        if ((_months_left - mounth_left) % 12 == 0 && _months_left != mounth_left){
            return A(salary * (infl/100 + 1), deposit, ap_cost * (infl/100 + 1), eats * (infl/100 + 1), 
            komunalka * (infl/100 + 1), mounth_left - 1, credit_left - ip_spendings);
        }
        return A(salary, deposit, ap_cost, eats, komunalka, mounth_left - 1, credit_left - ip_spendings);
    } 
    double bobs_savings = B(0, ap_spendings, eats_spendings, _months_left, bobs_salary);
    double alices_savings = A(alices_salary, 0, ap_cost, eats_spendings, utility_spendings, _months_left, (double)(ap_cost - fee));
    if (bobs_savings > alices_savings){
        printf("Bobs strategy better: %lf vs %lf", bobs_savings, alices_savings);
    }
    else{
        printf("Alices strategy better: %lf vs %lf", bobs_savings, alices_savings);
    }
    return 0;

    
    
    

}
