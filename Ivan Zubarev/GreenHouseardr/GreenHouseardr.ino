#include <iarduino_DHT.h>

// Конфигурация пинов
const int SOIL_MOISTURE_PIN = A1;    // Датчик влажности почвы
const int LIGHT_SENSOR_PIN = A0;      // Датчик освещенности
const int FAN_PIN = 7;               // Вентилятор
const int GROW_LIGHT_PIN = 6;        // Досветка растений
const int WATER_PUMP_PIN = 5;        // Водяная помпа
const int HEATER_PIN = 4;            // Нагревательный элемент
const int DHT_PIN = 13;              // Датчик температуры и влажности

// Пороговые значения
const int DRY_SOIL_THRESHOLD = 770;  // Порог сухой почвы
const int LOW_LIGHT_THRESHOLD = 300; // Порог низкой освещенности
const float MAX_TEMPERATURE = 30.0;  // Максимальная допустимая температура
const float MIN_TEMPERATURE = 15.0;  // Минимальная допустимая температура
const float MAX_HUMIDITY = 70.0;     // Максимальная допустимая влажность

// Время работы насоса (мс)
const unsigned long PUMP_DURATION = 7000;

// Инициализация датчика DHT
iarduino_DHT dhtSensor(DHT_PIN);

struct GreenhouseState {
  int soilMoisture;          // Влажность почвы
  int lightLevel;            // Уровень освещенности
  float temperature;         // Температура воздуха
  float humidity;            // Влажность воздуха
  unsigned long pumpStartTime; // Время начала полива
  bool isPumpActive;         // Флаг активности помпы
  bool fanStatus;            // Состояние вентилятора
  bool heaterStatus;         // Состояние нагревателя
  bool lightStatus;          // Состояние досветки
};

GreenhouseState greenhouse;

void setup() {
  Serial.begin(9600);
  
  // Настройка пинов
  pinMode(FAN_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(GROW_LIGHT_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  
  // Инициализация выходов
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(WATER_PUMP_PIN, LOW);
  digitalWrite(GROW_LIGHT_PIN, LOW);
  digitalWrite(HEATER_PIN, LOW);
  
  Serial.println("Система управления теплицей инициализирована");
}

void readSensorData() {
  // Чтение данных с датчика DHT
  if(dhtSensor.read() == DHT_OK) {
    greenhouse.temperature = dhtSensor.tem;
    greenhouse.humidity = dhtSensor.hum;
  }
  
  // Чтение аналоговых датчиков
  greenhouse.soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  greenhouse.lightLevel = analogRead(LIGHT_SENSOR_PIN);
}

void printSensorData() {
  Serial.println("\n=== Текущие показания датчиков ===");
  
  // Вывод данных DHT датчика
  switch(dhtSensor.read()) {
    case DHT_OK:
      Serial.print("Температура: ");
      Serial.print(greenhouse.temperature);
      Serial.print("°C, Влажность: ");
      Serial.print(greenhouse.humidity);
      Serial.println("%");
      break;
    case DHT_ERROR_CHECKSUM:
      Serial.println("Ошибка контрольной суммы DHT датчика");
      break;
    case DHT_ERROR_DATA:
      Serial.println("Ошибка данных DHT датчика");
      break;
    case DHT_ERROR_NO_REPLY:
      Serial.println("DHT датчик не отвечает");
      break;
    default:
      Serial.println("Неизвестная ошибка DHT датчика");
  }
  
  Serial.print("Влажность почвы: ");
  Serial.println(greenhouse.soilMoisture);
  
  Serial.print("Освещенность: ");
  Serial.println(greenhouse.lightLevel);
}

void controlTemperature() {
  // Охлаждение при высокой температуре
  if(greenhouse.temperature >= MAX_TEMPERATURE) {
    digitalWrite(HEATER_PIN, LOW);
    digitalWrite(FAN_PIN, HIGH);
    greenhouse.heaterStatus = false;
    greenhouse.fanStatus = true;
  } 
  // Нагрев при низкой температуре
  else if(greenhouse.temperature <= MIN_TEMPERATURE) {
    digitalWrite(HEATER_PIN, HIGH);
    digitalWrite(FAN_PIN, HIGH);
    greenhouse.heaterStatus = true;
    greenhouse.fanStatus = true;
  }
  // Нормальный режим
  else {
    digitalWrite(HEATER_PIN, LOW);
    greenhouse.heaterStatus = false;
    
    // Вентилятор выключаем только если не нужен для осушения
    if(greenhouse.humidity < MAX_HUMIDITY) {
      digitalWrite(FAN_PIN, LOW);
      greenhouse.fanStatus = false;
    }
  }
}

void controlHumidity() {
  // Включение вентилятора при высокой влажности
  if(greenhouse.humidity >= MAX_HUMIDITY) {
    digitalWrite(FAN_PIN, HIGH);
    greenhouse.fanStatus = true;
  } 
  // Выключение только если не требуется для температурного режима
  else if(!(greenhouse.temperature >= MAX_TEMPERATURE || greenhouse.temperature <= MIN_TEMPERATURE)) {
    digitalWrite(FAN_PIN, LOW);
    greenhouse.fanStatus = false;
  }
}

void controlWatering() {
  // Проверка необходимости полива
  if(greenhouse.soilMoisture >= DRY_SOIL_THRESHOLD) {
    if(!greenhouse.isPumpActive) {
      // Начало цикла полива
      digitalWrite(WATER_PUMP_PIN, HIGH);
      greenhouse.pumpStartTime = millis();
      greenhouse.isPumpActive = true;
      Serial.println("Полив начат");
    }
    else if(millis() - greenhouse.pumpStartTime >= PUMP_DURATION) {
      // Завершение цикла полива
      digitalWrite(WATER_PUMP_PIN, LOW);
      greenhouse.isPumpActive = false;
      Serial.println("Полив завершен");
    }
  }
  else {
    // Почва достаточно влажная - выключаем помпу если была активна
    if(greenhouse.isPumpActive) {
      digitalWrite(WATER_PUMP_PIN, LOW);
      greenhouse.isPumpActive = false;
    }
  }
}

void controlLighting() {
  // Включение досветки при недостатке освещения
  if(greenhouse.lightLevel < LOW_LIGHT_THRESHOLD) {
    digitalWrite(GROW_LIGHT_PIN, HIGH);
    greenhouse.lightStatus = true;
  }
  else {
    digitalWrite(GROW_LIGHT_PIN, LOW);
    greenhouse.lightStatus = false;
  }
}

void loop() {
  // Основной цикл управления
  readSensorData();
  printSensorData();
  
  controlTemperature();
  controlHumidity();
  controlWatering();
  controlLighting();
  
  delay(1000); // Пауза между измерениями
}