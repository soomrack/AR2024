#include <dht.h>

dht DHT;

#define dht_sensor_pin 8
#define light_sensor_pin A0
#define water_sensor_pin A1

#define light_pin 6
#define water_pump_pin 5 
#define heater_pin 3 
#define cooler_pin 7

#define normal_humidity 50
#define normal_temperature 25
#define normal_water 400
#define normal_light 500
#define normal_light_day 7

#define safetime_water_pump 30
#define safetime_heater 60
#define safetime_cooler 120

int temperature;
int humidity;
int water;
int light;
int light_day;
uint32_t timer;

uint32_t light_timer;
uint32_t light_day_timer;
uint32_t water_pump_timer;
uint32_t heater_timer;
uint32_t cooler_timer;

bool light_work;
bool water_pump_work;
bool heater_work;
bool cooler_work;

bool water_delay;



void setup() 
{
  Serial.begin(115200);
  pin_init();
  water_delay = 0;
}

void pin_init()
{
  pinMode(light_pin, OUTPUT);
  pinMode(water_pump_pin, OUTPUT);
  pinMode(heater_pin, OUTPUT);
  pinMode(cooler_pin, OUTPUT);
  pinMode(dht_sensor_pin, INPUT);
  pinMode(light_sensor_pin, INPUT);
  pinMode(water_sensor_pin, INPUT);
}
void sensor_check() 
{
  humidity = DHT.humidity;
  temperature = DHT.temperature;
  light = analogRead(light_sensor_pin);
  water = analogRead(water_sensor_pin);
}

void light_control() 
{
  if (light >= normal_light + 2)
    if (light >= normal_light + 2 && millis() - light_timer >= 1500)
    {
      light_timer = millis();
      digitalWrite(light_pin, HIGH);
      light_work = 1;
    }
  if (light <= normal_light - 2)
    if (light <= normal_light - 2 && millis() - light_timer >= 1500)
    {
      light_timer = millis();
      digitalWrite(light_pin, LOW);
      light_work = 0;
    }
}

void water_control() 
{
  if (water >= normal_water + 2 )
  {  
    digitalWrite(water_pump_pin, LOW);
    water_pump_work = 1;
    if (millis() - water_pump_timer >= 5000)
    {
      water_pump_timer = millis();
      digitalWrite(water_pump_pin, HIGH);
      water_pump_work = 0;
    }
  }
  else if (water <= normal_water - 2)
  {
    digitalWrite(water_pump_pin, LOW);
    water_pump_work = 0;
  }
}

void heater_control() 
{
  if (temperature <= normal_temperature - 2)
  {
    digitalWrite(heater_pin, HIGH);
    heater_work = 1;
  }
  else if (temperature >= normal_temperature + 2)
  {
    digitalWrite(heater_pin, LOW);
    heater_work = 0;
  }
}

void cooler_control() 
{
    if (humidity >= normal_humidity + 2 || heater_work || temperature >= normal_temperature + 1)
    {
      digitalWrite(cooler_pin, HIGH);
      cooler_work = 1;
    }
  else if (humidity <= normal_humidity - 2 && !heater_work && temperature <= normal_temperature + 3)
    {
      digitalWrite(cooler_pin, LOW);
      cooler_work = 0;
    }
}



void loop() {
  
  DHT.read11(dht_sensor_pin);

  sensor_check();
  light_control();
  water_control();
  heater_control();
  cooler_control();

  Serial.print(humidity);
  Serial.print("% ");
  Serial.print(temperature);
  Serial.print("C ");
  Serial.print(light);
  Serial.print("ед. ");
  Serial.print(water);
  Serial.print("ед. ");
  Serial.println();
  timer += millis();
  delay(100);
  


}

