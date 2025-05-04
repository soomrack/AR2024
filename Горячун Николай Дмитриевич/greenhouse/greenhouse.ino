#include "DHT.h"
#define PIN_DHT 12
#define PIN_SOILHUMIDITY A1
#define PIN_PHOTO_SENSOR A0
#define RELAY_HEATER 4
#define RELAY_PUMP 5
#define RELAY_LIGHT 6
#define RELAY_FAN 7


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
int pause_time = 1000;


void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(RELAY_HEATER, OUTPUT);
  pinMode(RELAY_PUMP, OUTPUT);
  pinMode(RELAY_LIGHT, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
}


void init_parameters()
{
  Parameters.humidity = dht.readHumidity();
  Parameters.temperature = dht.readTemperature();
  Parameters.soilhumidity = analogRead(PIN_SOILHUMIDITY);
  Parameters.illumination = analogRead(PIN_PHOTO_SENSOR);
}


void thermoregulation()
{
  if (Parameters.temperature >= 30.) {
    digitalWrite(RELAY_HEATER, LOW);
    digitalWrite(RELAY_FAN, HIGH);
    flag_temperature = 1;
  } else {
    if (Parameters.temperature <= 15.) {
      digitalWrite(RELAY_HEATER, HIGH);
      digitalWrite(RELAY_FAN, HIGH);
      flag_temperature = 1;
    } else {
      if (flag_humidity == 0) {
        digitalWrite(RELAY_HEATER, LOW);
        digitalWrite(RELAY_FAN, LOW);
        flag_temperature = 0;
      };
    };
  };
}


void humidity_regulation()
{
  if (Parameters.humidity >= 60.) {
    digitalWrite(RELAY_FAN, HIGH);
    flag_humidity = 1;
  } else {
    if (flag_temperature == 0) {
      digitalWrite(RELAY_FAN, LOW);
      flag_humidity = 0;
    };
  };
}


void soil_humidity_regulation()
{
  if (Parameters.soilhumidity <= 200) {
    digitalWrite(RELAY_PUMP, HIGH);
  } else {
    digitalWrite(RELAY_PUMP, LOW);
  };
}


void illumination_regulation()
{
  if (Parameters.illumination <= 300) {
    digitalWrite(RELAY_LIGHT, HIGH);
  } else {
    digitalWrite(RELAY_LIGHT, LOW);
  };
}


void pause()
{
  delay(pause_time);
}


void loop()
{
  init_parameters();

  thermoregulation();

  humidity_regulation();

  soil_humidity_regulation();

  illumination_regulation();

  pause();
}
