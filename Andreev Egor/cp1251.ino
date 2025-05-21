#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <RTClib.h>

// Конфигурация пинов
#define DHTPIN 2          // Пин для датчика DHT
#define DHTTYPE DHT22     // Тип датчика DHT22
#define SOIL_MOISTURE_PIN A0 // Пин для датчика влажности почвы
#define WATER_PUMP_PIN 3  // Пин для насоса полива
#define LIGHT_RELAY_PIN 4 // Пин для реле освещения
#define FAN_PIN 5         // Пин для вентилятора
#define HEATER_PIN 6      // Пин для обогревателя
#define LIGHT_SENSOR_PIN A1 // Пин для датчика освещенности

// Пороговые значения
#define SOIL_MOISTURE_THRESHOLD 40   // Порог влажности почвы (%)
#define TEMP_LOW_THRESHOLD 18        // Минимальная температура (°C)
#define TEMP_HIGH_THRESHOLD 28       // Максимальная температура (°C)
#define HUMIDITY_THRESHOLD 70        // Порог влажности воздуха (%)
#define LIGHT_THRESHOLD 500          // Порог освещенности (люкс)

// Инициализация объектов
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Адрес LCD 0x27, 16 символов, 2 строки
RTC_DS3231 rtc;

// Переменные для хранения данных
float temperature = 0;
float humidity = 0;
int soilMoisture = 0;
int lightLevel = 0;
DateTime now;

void setup() {
  Serial.begin(9600);
  
  // Инициализация устройств
  dht.begin();
  lcd.begin();
  lcd.backlight();
  
  // Инициализация RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  // Настройка пинов
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(LIGHT_RELAY_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  
  // Выключить все устройства при старте
  digitalWrite(WATER_PUMP_PIN, LOW);
  digitalWrite(LIGHT_RELAY_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(HEATER_PIN, LOW);
  
  lcd.print("OmegaGrow System");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Получение текущего времени
  now = rtc.now();
  
  // Считывание данных с датчиков
  readSensors();
  
  // Управление системами
  controlSystems();
  
  // Отображение информации
  displayData();
  
  // Логирование данных
  logData();
  
  delay(5000); // Задержка между измерениями (5 секунд)
}

void readSensors() {
  // Чтение температуры и влажности воздуха
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  
  // Чтение влажности почвы (0-1023, преобразуем в %)
  soilMoisture = map(analogRead(SOIL_MOISTURE_PIN), 0, 1023, 100, 0);
  
  // Чтение уровня освещенности
  lightLevel = analogRead(LIGHT_SENSOR_PIN);
  
  // Проверка на ошибки чтения
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}

void controlSystems() {
  // Управление поливом
  if (soilMoisture < SOIL_MOISTURE_THRESHOLD) {
    digitalWrite(WATER_PUMP_PIN, HIGH);
    // delay(2000); // Полив в течение 2 секунд
    digitalWrite(WATER_PUMP_PIN, LOW);
  }
  
  // Управление температурой
  if (temperature > TEMP_HIGH_THRESHOLD) {
    digitalWrite(FAN_PIN, HIGH);
    digitalWrite(HEATER_PIN, LOW);
  } else if (temperature < TEMP_LOW_THRESHOLD) {
    digitalWrite(FAN_PIN, LOW);
    digitalWrite(HEATER_PIN, HIGH);
  } else {
    digitalWrite(FAN_PIN, LOW);
    digitalWrite(HEATER_PIN, LOW);
  }
  
  // Управление освещением (по времени и уровню освещенности)
  if ((now.hour() >= 18 || now.hour() < 6) || lightLevel < LIGHT_THRESHOLD) {
    digitalWrite(LIGHT_RELAY_PIN, HIGH);
  } else {
    digitalWrite(LIGHT_RELAY_PIN, LOW);
  }
  
  // Дополнительное управление вентиляцией при высокой влажности
  if (humidity > HUMIDITY_THRESHOLD) {
    digitalWrite(FAN_PIN, HIGH);
  }
}

void displayData() {
  lcd.clear();
  
  // Первая строка: Температура и влажность воздуха
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C H:");
  lcd.print(humidity, 0);
  lcd.print("%");
  
  // Вторая строка: Влажность почвы и освещенность
  lcd.setCursor(0, 1);
  lcd.print("S:");
  lcd.print(soilMoisture);
  lcd.print("% L:");
  lcd.print(lightLevel);
}

void logData() {
  // Вывод данных в Serial Monitor
  Serial.print("Date: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" Time: ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Soil Moisture: ");
  Serial.print(soilMoisture);
  Serial.print(" %\t");
  Serial.print("Light: ");
  Serial.print(lightLevel);
  Serial.println(" lx");
  // Serial.println("----------------------------------");
}
