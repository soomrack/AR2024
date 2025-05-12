#include <DHT.h>
#include <Arduino.h>

// Пины подключения датчиков и устройств
#define DHT_PIN             8
#define LIGHT_SENSOR_PIN    A0
#define MOISTURE_SENSOR_PIN A1
#define LED_GROW_PIN        6
#define WATER_PUMP_PIN      5
#define HEATER_PIN          3
#define FAN_PIN             7

// Оптимальные параметры среды
#define OPT_TEMP        25.0    // Оптимальная температура (°C)
#define OPT_HUMIDITY    50.0    // Оптимальная влажность воздуха (%)
#define OPT_MOISTURE    400     // Оптимальная влажность почвы (0-1023)
#define OPT_LIGHT       500     // Оптимальная освещенность (0-1023)

// Допустимые отклонения
#define TEMP_TOLERANCE  2.0
#define HUMID_TOLERANCE 5.0
#define MOIST_TOLERANCE 50
#define LIGHT_TOLERANCE 50

// Настройки насоса
#define PUMP_RUN_DURATION    3000    // 3 секунды работы насоса
#define PUMP_PAUSE_DURATION  30000   // 30 секунд паузы
#define MOISTURE_SAMPLES     5       // Количество измерений для усреднения

DHT envSensor(DHT_PIN, DHT11);

// Состояние системы
struct SystemState {
  bool pumpIsOn = false;
  bool heaterIsOn = false;
  bool fanIsOn = false;
  bool lightIsOn = false;
  unsigned long pumpStartTime = 0;
  unsigned long pumpPauseTime = 0;
  float temperature = 0;
  float humidity = 0;
  int lightLevel = 0;
  int moistureLevel = 0;
};

SystemState state;

void setup() {
  Serial.begin(115200);
  
  // Инициализация пинов
  pinMode(LED_GROW_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  // Выключение всех устройств при старте
  digitalWrite(LED_GROW_PIN, LOW);
  digitalWrite(WATER_PUMP_PIN, HIGH);  // HIGH - насос выключен (для большинства реле)
  digitalWrite(HEATER_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);

  envSensor.begin();
  
  Serial.println("Plant Monitoring System Initialized");
  Serial.println("---------------------------------");
}

int readStableMoisture() {
  int sum = 0;
  for (int i = 0; i < MOISTURE_SAMPLES; i++) {
    sum += analogRead(MOISTURE_SENSOR_PIN);
    delay(10);
  }
  return sum / MOISTURE_SAMPLES;
}

void readSensors() {
  state.temperature = envSensor.readTemperature();
  state.humidity = envSensor.readHumidity();
  state.lightLevel = analogRead(LIGHT_SENSOR_PIN);
  state.moistureLevel = readStableMoisture();
}

void controlLight() {
  if (state.lightLevel < OPT_LIGHT - LIGHT_TOLERANCE) {
    digitalWrite(LED_GROW_PIN, HIGH);
    state.lightIsOn = true;
  } 
  else if (state.lightLevel > OPT_LIGHT + LIGHT_TOLERANCE) {
    digitalWrite(LED_GROW_PIN, LOW);
    state.lightIsOn = false;
  }
}

void controlWater() {
  // Если почва слишком сухая
  if (state.moistureLevel < OPT_MOISTURE - MOIST_TOLERANCE) {
    if (!state.pumpIsOn) {
      // Проверяем, можно ли включить насос после паузы
      if (millis() - state.pumpPauseTime >= PUMP_PAUSE_DURATION) {
        digitalWrite(WATER_PUMP_PIN, LOW);  // Включаем насос
        state.pumpIsOn = true;
        state.pumpStartTime = millis();
        Serial.println("Water pump: ON (soil too dry)");
      }
    } 
    else {
      // Проверяем, не пора ли выключить насос
      if (millis() - state.pumpStartTime >= PUMP_RUN_DURATION) {
        digitalWrite(WATER_PUMP_PIN, HIGH);  // Выключаем насос
        state.pumpIsOn = false;
        state.pumpPauseTime = millis();
        Serial.println("Water pump: OFF (watering cycle complete)");
      }
    }
  }
  else {
    // Если влажность в норме - выключаем насос
    if (state.pumpIsOn) {
      digitalWrite(WATER_PUMP_PIN, HIGH);
      state.pumpIsOn = false;
      state.pumpPauseTime = millis();
      Serial.println("Water pump: OFF (soil moisture OK)");
    }
  }
}

void controlTemperature() {
  if (state.temperature < OPT_TEMP - TEMP_TOLERANCE) {
    digitalWrite(HEATER_PIN, HIGH);
    state.heaterIsOn = true;
  } 
  else if (state.temperature > OPT_TEMP) {
    digitalWrite(HEATER_PIN, LOW);
    state.heaterIsOn = false;
  }
}

void controlVentilation() {
  bool needVentilation = (state.humidity > OPT_HUMIDITY + HUMID_TOLERANCE) ||
                         (state.temperature > OPT_TEMP + TEMP_TOLERANCE) ||
                         (state.heaterIsOn);

  if (needVentilation) {
    digitalWrite(FAN_PIN, HIGH);
    state.fanIsOn = true;
  } 
  else {
    digitalWrite(FAN_PIN, LOW);
    state.fanIsOn = false;
  }
}

void logSystemState() {
  Serial.println("\n===== System Status =====");
  Serial.print("Temperature: "); Serial.print(state.temperature); Serial.println(" °C");
  Serial.print("Humidity: "); Serial.print(state.humidity); Serial.println(" %");
  Serial.print("Light: "); Serial.print(state.lightLevel); Serial.println(" lx");
  Serial.print("Soil Moisture: "); Serial.print(state.moistureLevel); 
  Serial.print(" (Threshold: "); Serial.print(OPT_MOISTURE - MOIST_TOLERANCE); Serial.println(")");
  
  Serial.println("\nDevice States:");
  Serial.print("Grow Light: "); Serial.println(state.lightIsOn ? "ON" : "OFF");
  Serial.print("Water Pump: "); Serial.println(state.pumpIsOn ? "ON" : "OFF");
  Serial.print("Heater: "); Serial.println(state.heaterIsOn ? "ON" : "OFF");
  Serial.print("Fan: "); Serial.println(state.fanIsOn ? "ON" : "OFF");
  Serial.println("=======================\n");
}

void loop() {
  readSensors();
  
  controlLight();
  controlWater();
  controlTemperature();
  controlVentilation();
  
  logSystemState();
  
  delay(2000);  // Задержка между измерениями
}

int main() {
  init();
  setup();
  while (true) {
    loop();
  }
  return 0;
}
