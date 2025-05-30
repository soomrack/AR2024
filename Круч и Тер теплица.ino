#include <DHT.h>   // подключаем библиотеку для работы с датчиком DHT


DHT vlazh(13, DHT11); // датчик температуры и влажности воздуха
#define svet A0 // датчик освещенности
#define humid  A1   // датчик влажности почвы
#define vent 7 // вентилятор
#define lamp 6  // лампа
#define pump 5  // помпа
#define heat 4  // электронагреватель

bool OTLADKA = 0;
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


void sensors_read() 
{
light = analogRead(svet);
ground_hum = analogRead(humid);
vlazh.read();
humo = vlazh.readHumidity();
temp = vlazh.readTemperature();
}


void otladka() 
{
Serial.println("svet ");
Serial.print(light);
Serial.print(" ground hum ");
Serial.print(ground_hum);
Serial.print(" temp ");
Serial.print(temp);
Serial.print(" hum ");
Serial.print(humo);
Serial.println(" ");
}


void loop() 
{
  sensors_read();
  if (OTLADKA == 1) otladka();
  else {

    if (light > 550) digitalWrite(lamp, HIGH);
    else digitalWrite(lamp, LOW);

    if (ground_hum > 800) digitalWrite(pump, HIGH);
    else digitalWrite(pump, LOW);

    if (humo > 50) digitalWrite(vent, HIGH);
    else digitalWrite(vent, LOW);

    if (temp < 30) digitalWrite(heat, HIGH);
    else digitalWrite(heat, LOW);

    }
    delay(100);
  }
