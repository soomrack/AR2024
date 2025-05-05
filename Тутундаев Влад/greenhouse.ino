#include <DHT11.h>

#define ANALOG_PIN_PHOTO_SENSOR A0
#define ANALOG_PIN_SOILHUMIDITY A1
#define PIN_HEATER 4
#define PIN_PUMP 5
#define PIN_LAMP 6
#define PIN_FAN 7

DHT11 PIN_DHT(12);

int temperature;
int humidity;
int soilhumidity;
int light;
int t1;
int t2;

bool heater;
bool pump;
bool lamp;
bool fan;

void init_data()
{
  t2 = 0;
  pinMode(ANALOG_PIN_PHOTO_SENSOR, INPUT);
  pinMode(ANALOG_PIN_SOILHUMIDITY, INPUT);
  pinMode(PIN_HEATER, OUTPUT);
  pinMode(PIN_PUMP, OUTPUT);
  pinMode(PIN_LAMP, OUTPUT);
  pinMode(PIN_FAN, OUTPUT);
}


void sensor_check() 
 {
   PIN_DHT.readTemperatureHumidity(temperature, humidity);
   light = analogRead(ANALOG_PIN_PHOTO_SENSOR);
   soilhumidity = analogRead(ANALOG_PIN_SOILHUMIDITY);
 }


void heater_control()
{
  if (temperature < 27 ) heater = true;
  else heater = false;
}


void pump_control()
{
  t2 = mills();
  
  if (t1 > t2){
    t1 -= 4 294 967 295;
  }

  if (soilhumidity < 70 && t2 - t1 >= 20000){
   pump = true;
   t1 = t2; 
  }
  else pump = false;
}


void lamp_control()
{
  if (light < 700) lamp = true;
  else lamp = false;
}


void fan_control()
{
  if (temperature > 30 || humidity > 90) fan = true;
  else fan = false;
}


void setup() 
{
  init_data();
  Serial.begin(9600);
}


void system_regulator()
{
  if (pump) digitalWrite(PIN_PUMP, HIGH);
  else digitalWrite(PIN_PUMP, LOW);
  if (heater) digitalWrite(PIN_HEATER, HIGH);
  else digitalWrite(PIN_HEATER, LOW);
  if (lamp) digitalWrite(PIN_LAMP, HIGH);
  else digitalWrite(PIN_LAMP, LOW);
  if (fan) digitalWrite(PIN_FAN, HIGH);
  else digitalWrite(PIN_FAN, LOW);
}


void print_sensor_indicators()
{
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C   Humidity: ");
  Serial.print(humidity);
  Serial.print(" %   Light: ");
  Serial.print(light);
  Serial.print("   Soilhumidity: ");
  Serial.println(soilhumidity);
}


void loop() {
  sensor_check();
  heater_control();
  pump_control();
  lamp_control();
  fan_control();
  print_sensor_indicators();
  system_regulator();
  delay(10000);
};
