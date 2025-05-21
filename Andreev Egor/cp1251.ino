#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <RTClib.h>

// ������������ �����
#define DHTPIN 2          // ��� ��� ������� DHT
#define DHTTYPE DHT22     // ��� ������� DHT22
#define SOIL_MOISTURE_PIN A0 // ��� ��� ������� ��������� �����
#define WATER_PUMP_PIN 3  // ��� ��� ������ ������
#define LIGHT_RELAY_PIN 4 // ��� ��� ���� ���������
#define FAN_PIN 5         // ��� ��� �����������
#define HEATER_PIN 6      // ��� ��� ������������
#define LIGHT_SENSOR_PIN A1 // ��� ��� ������� ������������

// ��������� ��������
#define SOIL_MOISTURE_THRESHOLD 40   // ����� ��������� ����� (%)
#define TEMP_LOW_THRESHOLD 18        // ����������� ����������� (�C)
#define TEMP_HIGH_THRESHOLD 28       // ������������ ����������� (�C)
#define HUMIDITY_THRESHOLD 70        // ����� ��������� ������� (%)
#define LIGHT_THRESHOLD 500          // ����� ������������ (����)

// ������������� ��������
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // ����� LCD 0x27, 16 ��������, 2 ������
RTC_DS3231 rtc;

// ���������� ��� �������� ������
float temperature = 0;
float humidity = 0;
int soilMoisture = 0;
int lightLevel = 0;
DateTime now;

void setup() {
  Serial.begin(9600);
  
  // ������������� ���������
  dht.begin();
  lcd.begin();
  lcd.backlight();
  
  // ������������� RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  // ��������� �����
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(LIGHT_RELAY_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  
  // ��������� ��� ���������� ��� ������
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
  // ��������� �������� �������
  now = rtc.now();
  
  // ���������� ������ � ��������
  readSensors();
  
  // ���������� ���������
  controlSystems();
  
  // ����������� ����������
  displayData();
  
  // ����������� ������
  logData();
  
  delay(5000); // �������� ����� ����������� (5 ������)
}

void readSensors() {
  // ������ ����������� � ��������� �������
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  
  // ������ ��������� ����� (0-1023, ����������� � %)
  soilMoisture = map(analogRead(SOIL_MOISTURE_PIN), 0, 1023, 100, 0);
  
  // ������ ������ ������������
  lightLevel = analogRead(LIGHT_SENSOR_PIN);
  
  // �������� �� ������ ������
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}

void controlSystems() {
  // ���������� �������
  if (soilMoisture < SOIL_MOISTURE_THRESHOLD) {
    digitalWrite(WATER_PUMP_PIN, HIGH);
    // delay(2000); // ����� � ������� 2 ������
    digitalWrite(WATER_PUMP_PIN, LOW);
  }
  
  // ���������� ������������
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
  
  // ���������� ���������� (�� ������� � ������ ������������)
  if ((now.hour() >= 18 || now.hour() < 6) || lightLevel < LIGHT_THRESHOLD) {
    digitalWrite(LIGHT_RELAY_PIN, HIGH);
  } else {
    digitalWrite(LIGHT_RELAY_PIN, LOW);
  }
  
  // �������������� ���������� ����������� ��� ������� ���������
  if (humidity > HUMIDITY_THRESHOLD) {
    digitalWrite(FAN_PIN, HIGH);
  }
}

void displayData() {
  lcd.clear();
  
  // ������ ������: ����������� � ��������� �������
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C H:");
  lcd.print(humidity, 0);
  lcd.print("%");
  
  // ������ ������: ��������� ����� � ������������
  lcd.setCursor(0, 1);
  lcd.print("S:");
  lcd.print(soilMoisture);
  lcd.print("% L:");
  lcd.print(lightLevel);
}

void logData() {
  // ����� ������ � Serial Monitor
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
  Serial.print(" �C\t");
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
