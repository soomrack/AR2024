#include <iarduino_DHT.h>   // подключаем библиотеку для работы с датчиком DHT


iarduino_DHT vlazh(13); // датчик температуры и влажности воздуха
#define svet A0 // датчик освещенности
#define humid  A1   // датчик влажности почвы
#define vent 7 // вентилятор
#define lamp 6  // лампа
#define pump 5  // помпа
#define heat 4  // электронагреватель

bool OTLADKA =1;
float light, humo, temp, ground_hum;



void setup() 
{
Serial.begin(9600);
pinMode(svet, INPUT); 
pinMode(humid, INPUT); 
pinMode(vent, OUTPUT); 
pinMode(lamp, OUTPUT); 
pinMode(pump, OUTPUT); 
pinMode(heat, OUTPUT); 
}


void loop() 
{
  sensors_read();
  if (OTLADKA == 1) otladka();
  else {

    if (light > 500) digitalWrite(lamp, HIGH);
    else digitalWrite(lamp, LOW);

    if (ground_hum > 700) digitalWrite(pump, HIGH);
    else digitalWrite(pump, LOW);

    if (humo > 50) digitalWrite(vent, HIGH);
    else digitalWrite(vent, LOW);

    if (temp < 30) digitalWrite(heat, HIGH);
    else digitalWrite(heat, LOW);

    }
    delay(100);
  }