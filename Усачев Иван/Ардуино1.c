// Определение пинов
#define TEMPERATURE_HUMIDITY_PIN 2 // Пин для DHT22 (температура и влажность)
#define LIGHT_SENSOR_PIN A0        // Аналоговый пин для фоторезистора
#define WINDOW_PIN 8              // Пин для управления открытием окна (реле)
#define PUMP_PIN 9                // Пин для управления насосом полива (реле)
#define LIGHT_PIN 10               // Пин для управления искусственным освещением (реле)

// Пороговые значения (настройте под свои нужды)
#define MAX_TEMPERATURE 30        // Максимальная температура (°C)
#define MIN_HUMIDITY 60           // Минимальная влажность (%)
#define MIN_LIGHT_LEVEL 300       // Минимальный уровень освещенности (значение аналогового датчика)

// Интервалы
#define MEASUREMENT_INTERVAL 5000 // Интервал между измерениями (мс)
#define DISPLAY_INTERVAL 1000 // Интервал для вывода информации на экран (мс)

// Библиотеки
#include <DHT.h>

// Объекты
DHT dht(TEMPERATURE_HUMIDITY_PIN, DHT22);

// Переменные
float temperature = 0.0;
float humidity = 0.0;
int lightLevel = 0;

unsigned long lastMeasurementTime = 0;
unsigned long lastDisplayTime = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(WINDOW_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);

  // Изначально все выключено
  digitalWrite(WINDOW_PIN, LOW); // Закрыто
  digitalWrite(PUMP_PIN, LOW);   // Выключено
  digitalWrite(LIGHT_PIN, LOW);  // Выключено

  Serial.println("Теплица готова к работе!");
}

void loop() {
  unsigned long currentTime = millis();

  // Измерение данных (каждые MEASUREMENT_INTERVAL мс)
  if (currentTime - lastMeasurementTime >= MEASUREMENT_INTERVAL) {
    getSensorData();
    controlSystems();
    lastMeasurementTime = currentTime;
  }

  // Вывод данных на экран (каждые DISPLAY_INTERVAL мс)
  if (currentTime - lastDisplayTime >= DISPLAY_INTERVAL) {
    displayData();
    lastDisplayTime = currentTime;
  }
}

void getSensorData() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  lightLevel = analogRead(LIGHT_SENSOR_PIN);

  // Проверка на ошибки чтения
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Ошибка чтения данных с DHT22!");
    return;
  }
}

void controlSystems() {
  // Управление окном
  if (temperature > MAX_TEMPERATURE) {
    Serial.println("Открываю окно...");
    digitalWrite(WINDOW_PIN, HIGH); // Открыть окно
  } else {
    Serial.println("Закрываю окно...");
    digitalWrite(WINDOW_PIN, LOW);  // Закрыть окно
  }

  // Управление поливом
  if (humidity < MIN_HUMIDITY) {
    Serial.println("Включаю полив...");
    digitalWrite(PUMP_PIN, HIGH);  // Включить насос
    delay(5000);                    // Поливаем 5 секунд (настройте)
    Serial.println("Выключаю полив...");
    digitalWrite(PUMP_PIN, LOW);   // Выключить насос
  }

  // Управление освещением
  if (lightLevel < MIN_LIGHT_LEVEL) {
    Serial.println("Включаю свет...");
    digitalWrite(LIGHT_PIN, HIGH); // Включить свет
  } else {
    Serial.println("Выключаю свет...");
    digitalWrite(LIGHT_PIN, LOW);  // Выключить свет
  }
}

void displayData() {
  Serial.print("Температура: ");
  Serial.print(temperature);
  Serial.print(" °C, Влажность: ");
  Serial.print(humidity);
  Serial.print(" %, Освещенность: ");
  Serial.println(lightLevel);
}
