#include "DHT.h"
#define PIN_DHT 13
#define PIN_SOILHUMIDITY A1
#define PIN_PHOTO_SENSOR A0
#define PIN_RELAY_HEATER 4
#define PIN_RELAY_PUMP 5
#define PIN_RELAY_LIGHT 6
#define PIN_RELAY_FAN 7


DHT dht(PIN_DHT, DHT11);
struct Data_parameters {
  float humidity;
  float temperature;
  int soilhumidity;
  int illumination;
};


struct Data_parameters Parameters;
int flag_temperature = 0;
int flag_humidity = 0;
int flag_pump = 0;
unsigned long pump_time = 0;
unsigned long pause_time = 1000;
unsigned long pump_pause = 5*60*100;
unsigned long pump_work = 3000;
unsigned long start_time = 0;


void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(PIN_RELAY_HEATER, OUTPUT);
  pinMode(PIN_RELAY_PUMP, OUTPUT);
  pinMode(PIN_RELAY_LIGHT, OUTPUT);
  pinMode(PIN_RELAY_FAN, OUTPUT);
}


void init_parameters()
{
  Parameters.humidity = dht.readHumidity();
  Parameters.temperature = dht.readTemperature();
  Parameters.soilhumidity = analogRead(PIN_SOILHUMIDITY);
  Parameters.illumination = 1023 - analogRead(PIN_PHOTO_SENSOR);
}


void thermoregulation()
{
  if (Parameters.temperature >= 30.) {
    digitalWrite(PIN_RELAY_HEATER, LOW);
    digitalWrite(PIN_RELAY_FAN, HIGH);
    flag_temperature = 1;
  } else {
    if (Parameters.temperature <= 15.) {
      digitalWrite(PIN_RELAY_HEATER, HIGH);
      digitalWrite(PIN_RELAY_FAN, HIGH);
      flag_temperature = 1;
    } else {
      if (flag_humidity == 0) {
        digitalWrite(PIN_RELAY_HEATER, LOW);
        digitalWrite(PIN_RELAY_FAN, LOW);
        flag_temperature = 0;
      };
    };
  };
}


void humidity_regulation()
{
  if (Parameters.humidity >= 60.) {
    digitalWrite(PIN_RELAY_FAN, HIGH);
    flag_humidity = 1;
  } else {
    if (flag_temperature == 0) {
      digitalWrite(PIN_RELAY_FAN, LOW);
      flag_humidity = 0;
    };
  };
}


void soil_humidity_regulation()
{
  if (millis() - pump_time >= pump_pause) {
    flag_pump = 0;
  };
  if (flag_pump == 0 && Parameters.soilhumidity >= 200) {
    digitalWrite(PIN_RELAY_PUMP, HIGH);
    pump_time = millis();
  } else {
    if (Parameters.soilhumidity < 200 || millis() - pump_time >= pump_work) {
      digitalWrite(PIN_RELAY_PUMP, LOW);
      flag_pump = 1;
      pump_time = millis();
    };
  };
}


void illumination_regulation()
{
  if (Parameters.illumination <= 300) {
    digitalWrite(PIN_RELAY_LIGHT, HIGH);
  } else {
    digitalWrite(PIN_RELAY_LIGHT, LOW);
  };
}


void loop()
{
  if (millis() - start_time >= pause_time) {
    init_parameters();

    thermoregulation();

    humidity_regulation();

    soil_humidity_regulation();

    illumination_regulation();

    start_time = millis();
  };
}