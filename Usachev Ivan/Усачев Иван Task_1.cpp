#include <iostream>
using namespace std;
int main ()
    {
    long int Alice, Bob;
    printf ("Let's work with Bob \n");          //начало работы с Бобом
    long int salb, wastb, s1, s2, sum1, sum2;                                //зарплата, траты, сумма зп, сумма трат
    printf ("Give Bob's salary \n");
    cin >> salb; s1 = 12 * salb; sum1 = 0;                              //зарплата, годовая зп
    printf ("Give Bob's wastes per month \n");
    cin >> wastb; s2 = 12 * wastb; sum2 = 0;                             //траты, годовые траты
    for (int n = 0; n < 30; n++)                  // количество лет
    {
        s1 = s1 * 1.08;
        sum1 = sum1 + s1;
        s2 = s2 * 1.08;
        sum2 = sum2 + s2;
    }
    Bob = sum1 - sum2;

    printf ("Now let's work with Alice \n");        //начало работы с Алисой
    long int sala, wasta, mortg, s3, s4, sum3, sum4, house, h; h = 14000000; house = 0;     //зарплата, траты, ипотека, год зп, год трат
    printf ("Give Alice's salary \n");
    cin >> sala; s3 = 12 * sala; sum3 = 0;                              //введение годовой зп
    printf ("Give Alice's wastes per month \n");
    cin >> wasta; s4 = 12 * wasta; sum4 = 0;                                //введение годовых трат
    printf ("Give Alice's mortgage payment per month \n");
    cin >> mortg;                                                  //аннуитетный платеж
    long int mortgall; mortgall = mortg * 360;
    for (int w = 0; w < 30; w++)
    {
        s3 = s3 * 1.08;
        sum3 = sum3 + s3;
        s4 = s4 * 1.08;
        sum4 = sum4 + s4;

    }
    for (int a = 0; a < 30; a++) //увеличение стоимости квартиры
    {
        h = h * 1.08;
        house = house + h;
    }
    Alice = sum3 - sum4 - mortgall + house;


    if( Alice > Bob )                               //логические операции
    {
        printf ("Alice will be richer on ");
        cout << Alice - Bob << endl;
    }
    if( Alice < Bob )
    {
        printf ("Bob will be richer on ");
        cout << Bob - Alice << endl;
    }

    return (0);
}

