#include <dht.h>

dht DHT;

// Определение пинов
#define DHT_SENSOR_PIN 8
#define LIGHT_SENSOR_PIN A0
#define WATER_SENSOR_PIN A1

#define LIGHT_PIN 6
#define WATER_PUMP_PIN 5 
#define HEATER_PIN 3 
#define COOLER_PIN 7

// Нормальные параметры
#define NORMAL_HUMIDITY 50
#define NORMAL_TEMPERATURE 25
#define NORMAL_WATER 400    // Зависит от типа датчика
#define NORMAL_LIGHT 500
#define LIGHT_HYSTERESIS 20 // Гистерезис для предотвращения мерцания

// Время безопасной работы (секунды)
#define SAFETIME_WATER_PUMP 30
#define SAFETIME_HEATER 60
#define SAFETIME_COOLER 120

// Глобальные переменные
int temperature;
int humidity;
int water_level;
int light_level;

// Таймеры
uint32_t light_timer = 0;
uint32_t water_pump_timer = 0;
uint32_t heater_timer = 0;
uint32_t cooler_timer = 0;

// Состояния устройств
bool light_state = false;
bool water_pump_state = false;
bool heater_state = false;
bool cooler_state = false;

void setup() {
  Serial.begin(115200);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(COOLER_PIN, OUTPUT);
  
  // Инициализация выключенным состоянием
  digitalWrite(LIGHT_PIN, LOW);
  digitalWrite(WATER_PUMP_PIN, HIGH); // Предполагаем активное реле
  digitalWrite(HEATER_PIN, LOW);
  digitalWrite(COOLER_PIN, LOW);
}

void readSensors() {
  int chk = DHT.read11(DHT_SENSOR_PIN);
  if (chk != DHTLIB_OK) {
    Serial.println("Ошибка DHT!");
    return;
  }
  humidity = DHT.humidity;
  temperature = DHT.temperature;
  light_level = analogRead(LIGHT_SENSOR_PIN);
  water_level = analogRead(WATER_SENSOR_PIN);
}

void controlLight() {
  if (light_level > NORMAL_LIGHT + LIGHT_HYSTERESIS/2) {
    if (!light_state) {
      digitalWrite(LIGHT_PIN, HIGH);
      light_state = true;
    }
  } 
  else if (light_level < NORMAL_LIGHT - LIGHT_HYSTERESIS/2) {
    if (light_state) {
      digitalWrite(LIGHT_PIN, LOW);
      light_state = false;
    }
  }
}

void controlWaterPump() {
  if (water_level > NORMAL_WATER) { // Нужен полив
    if (!water_pump_state) {
      digitalWrite(WATER_PUMP_PIN, LOW); // Включаем помпу
      water_pump_state = true;
      water_pump_timer = millis();
    }
    else if (millis() - water_pump_timer > SAFETIME_WATER_PUMP*1000) {
      digitalWrite(WATER_PUMP_PIN, HIGH); // Выключаем по таймауту
      water_pump_state = false;
    }
  } 
  else {
    digitalWrite(WATER_PUMP_PIN, HIGH); // Выключаем помпу
    water_pump_state = false;
  }
}

void controlHeater() {
  if (temperature < NORMAL_TEMPERATURE - 1) {
    digitalWrite(HEATER_PIN, HIGH);
    heater_state = true;
    heater_timer = millis();
  } 
  else if (temperature > NORMAL_TEMPERATURE || 
          (heater_state && (millis() - heater_timer > SAFETIME_HEATER*1000))) {
    digitalWrite(HEATER_PIN, LOW);
    heater_state = false;
  }
}

void controlCooler() {
  bool need_cooling = humidity > NORMAL_HUMIDITY || 
                    temperature > NORMAL_TEMPERATURE + 1 ||
                    heater_state;

  if (need_cooling) {
    digitalWrite(COOLER_PIN, HIGH);
    cooler_state = true;
    cooler_timer = millis();
  } 
  else if (millis() - cooler_timer > SAFETIME_COOLER*1000) {
    digitalWrite(COOLER_PIN, LOW);
    cooler_state = false;
  }
}

void printStatus() {
  Serial.print("Влажность: ");
  Serial.print(humidity);
  Serial.print("%\tТемпература: ");
  Serial.print(temperature);
  Serial.print("°C\tСвет: ");
  Serial.print(light_level);
  Serial.print("\tВода: ");
  Serial.print(water_level);
  Serial.print("\tУстройства [L:");
  Serial.print(light_state);
  Serial.print(" W:");
  Serial.print(water_pump_state);
  Serial.print(" H:");
  Serial.print(heater_state);
  Serial.print(" C:");
  Serial.print(cooler_state);
  Serial.println("]");
}

void loop() {
  readSensors();
  
  controlLight();
  controlWaterPump();
  controlHeater();
  controlCooler();
  
  printStatus();
  
  delay(1000); // Задержка для стабильности измерений
}