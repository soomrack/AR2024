#include <iarduino_DHT.h> 
iarduino_DHT dhtSensor(13);
#define LIGHT_SENSOR_PIN A0 // датчик освещенности
#define SOIL_MOISTURE_PIN A1 // датчик влажности почвы
#define LED_PIN 13 // порт для подключения светодиода
#define FAN_PIN 7 // порт для подключения вентилятора
#define GROW_LIGHT_PIN 6 // порт для освещения растений
#define WATER_PUMP_PIN 5 // порт для помпы
#define HEATER_PIN 4 // порт для нагревателя (работает только с вентилятором)
#define DHT_PIN 9 // датчик температуры и влажности (не используется, так как датчик подключен к пину 13)


struct GreenhouseParameters { 
  int minSoilMoisture = 770; // минимальный порог влажности почвы
  int minLightLevel = 300; // минимальный порог освещенности
  int soilMoisture; // текущая влажность почвы
  int lightLevel; // текущий уровень освещенности
  unsigned long pumpTimer = 0; // таймер для работы помпы
  bool isPumpActive = false; // флаг активности помпы
  bool isPumpOnPhase = false; // флаг фазы работы помпы (включена/выключена)
}; 
 
 
struct GreenhouseParameters parameters; 
int temperatureFlag = 0; // флаг состояния температуры
int humidityFlag = 0; // флаг состояния влажности воздуха
int delayTime = 1000; // время задержки между измерениями 
 
 
void setup() 
{ 
  Serial.begin(9600); 
  pinMode(HEATER_PIN, OUTPUT); 
  pinMode(WATER_PUMP_PIN, OUTPUT); 
  pinMode(GROW_LIGHT_PIN, OUTPUT); 
  pinMode(FAN_PIN, OUTPUT);
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
} 


void readParameters()
{
  parameters.soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  parameters.lightLevel = analogRead(LIGHT_SENSOR_PIN);
}

void printSensorData(){
  Serial.print("Датчик в комнате: ");
  switch(dhtSensor.read()){ // Читаем показания датчика температуры и влажности
    case DHT_OK:             Serial.println((String) dhtSensor.hum + "% - " + dhtSensor.tem + "*C"); break;
    case DHT_ERROR_CHECKSUM: Serial.println("Ошибка контрольной суммы"); break;
    case DHT_ERROR_DATA:     Serial.println("Ответ не соответствует датчику 'DHT'"); break;
    case DHT_ERROR_NO_REPLY: Serial.println("Нет ответа от датчика"); break;
    default:                 Serial.println("Ошибка"); break;
  } 
  Serial.print("Влажность почвы: ");
  Serial.println(analogRead(SOIL_MOISTURE_PIN));
  Serial.print("Освещенность: ");
  Serial.println(analogRead(LIGHT_SENSOR_PIN));    
}
 

void regulateTemperature() 
{ 
  if (dhtSensor.tem >= 30.0) { 
    digitalWrite(HEATER_PIN, LOW); 
    digitalWrite(FAN_PIN, HIGH); 
    temperatureFlag = 1; 
  } else { 
    if (dhtSensor.tem <= 15.0) { 
      digitalWrite(HEATER_PIN, HIGH); 
      digitalWrite(FAN_PIN, HIGH); 
      temperatureFlag = 1; 
    } else { 
      if (humidityFlag == 0) { 
        digitalWrite(HEATER_PIN, LOW); 
        digitalWrite(FAN_PIN, LOW); 
        temperatureFlag = 0; 
      } 
    } 
  } 
} 
 
 
void regulateAirHumidity() 
{ 
  if (dhtSensor.hum >= 70.0) { 
    digitalWrite(FAN_PIN, HIGH); 
    humidityFlag = 1; 
  } else { 
    if (temperatureFlag == 0) { 
      digitalWrite(FAN_PIN, LOW); 
      humidityFlag = 0; 
    } 
  } 
} 
 
void regulateSoilMoisture() {
  if (parameters.soilMoisture >= parameters.minSoilMoisture) {
    unsigned long currentTime = millis();

    if (!parameters.isPumpActive) {
      digitalWrite(WATER_PUMP_PIN, HIGH);
      parameters.pumpTimer = currentTime;
      parameters.isPumpActive = true;
      parameters.isPumpOnPhase = true;
    } else {
      if (parameters.isPumpOnPhase && currentTime - parameters.pumpTimer >= 7000) {
        digitalWrite(WATER_PUMP_PIN, LOW);
        parameters.pumpTimer = currentTime;
        parameters.isPumpOnPhase = false;
      }
    }
  } else {
    digitalWrite(WATER_PUMP_PIN, LOW);
    parameters.isPumpActive = false;
    parameters.isPumpOnPhase = false;
  }
}

void regulateLighting() 
{ 
  if (parameters.lightLevel >= parameters.minLightLevel) { 
    digitalWrite(GROW_LIGHT_PIN, HIGH); 
  } else { 
    digitalWrite(GROW_LIGHT_PIN, LOW); 
  } 
} 
 
 
void pauseBetweenReadings() 
{ 
  delay(delayTime); 
} 
 
 
void loop() 
{ 
  printSensorData();
  readParameters();
  regulateTemperature(); 
  regulateAirHumidity(); 
  regulateSoilMoisture(); 
  regulateLighting(); 
  pauseBetweenReadings();
}