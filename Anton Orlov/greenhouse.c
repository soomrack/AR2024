#include <DHT.h>
#include <Arduino.h>

// Пины подключения (оставил вашу последнюю конфигурацию)
#define DHT_PIN             8
#define LIGHT_SENSOR_PIN    A0
#define MOISTURE_SENSOR_PIN A1
#define LED_GROW_PIN        5  // Свет на пине 5
#define WATER_PUMP_PIN      6  // Насос на пине 6
#define HEATER_PIN          3
#define FAN_PIN             7

// Оптимальные параметры
#define OPT_TEMP        25.0
#define OPT_HUMIDITY    50.0
#define OPT_MOISTURE    400
#define OPT_LIGHT       500

// Допуски
#define TEMP_TOLERANCE  2.0
#define HUMID_TOLERANCE 5.0
#define MOIST_TOLERANCE 50
#define LIGHT_TOLERANCE 50

// Настройки насоса
#define PUMP_RUN_DURATION    3000
#define PUMP_PAUSE_DURATION  30000
#define MOISTURE_SAMPLES     5

DHT envSensor(DHT_PIN, DHT11);

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
  
  // Инициализация пинов с защитой от одновременного включения
  pinMode(LED_GROW_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  // Инициализация в выключенном состоянии
  digitalWrite(LED_GROW_PIN, LOW);
  digitalWrite(WATER_PUMP_PIN, HIGH); // HIGH - насос выключен
  digitalWrite(HEATER_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);

  envSensor.begin();
  
  Serial.println("System initialized - Independent pump/light control");
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
  // Управление светом полностью независимо от других устройств
  bool lightShouldBeOn = (state.lightLevel < OPT_LIGHT - LIGHT_TOLERANCE);
  
  if (lightShouldBeOn && !state.lightIsOn) {
    digitalWrite(LED_GROW_PIN, HIGH);
    state.lightIsOn = true;
    Serial.println("Grow light: ON (by light level)");
  } 
  else if (!lightShouldBeOn && state.lightIsOn) {
    digitalWrite(LED_GROW_PIN, LOW);
    state.lightIsOn = false;
    Serial.println("Grow light: OFF (light level OK)");
  }
}

void controlWater() {
  // Управление насосом независимо от света
  bool pumpShouldBeOn = (state.moistureLevel < OPT_MOISTURE - MOIST_TOLERANCE);
  
  if (pumpShouldBeOn) {
    if (!state.pumpIsOn) {
      if (millis() - state.pumpPauseTime >= PUMP_PAUSE_DURATION) {
        digitalWrite(WATER_PUMP_PIN, LOW);
        state.pumpIsOn = true;
        state.pumpStartTime = millis();
        Serial.println("Water pump: ON (soil dry)");
      }
    } 
    else {
      if (millis() - state.pumpStartTime >= PUMP_RUN_DURATION) {
        digitalWrite(WATER_PUMP_PIN, HIGH);
        state.pumpIsOn = false;
        state.pumpPauseTime = millis();
        Serial.println("Water pump: OFF (cycle complete)");
      }
    }
  }
  else if (state.pumpIsOn) {
    digitalWrite(WATER_PUMP_PIN, HIGH);
    state.pumpIsOn = false;
    state.pumpPauseTime = millis();
    Serial.println("Water pump: OFF (soil moisture OK)");
  }
}

void controlTemperature() {
  // Стандартное управление нагревателем
  if (state.temperature < OPT_TEMP - TEMP_TOLERANCE && !state.heaterIsOn) {
    digitalWrite(HEATER_PIN, HIGH);
    state.heaterIsOn = true;
    Serial.println("Heater: ON");
  } 
  else if (state.temperature >= OPT_TEMP && state.heaterIsOn) {
    digitalWrite(HEATER_PIN, LOW);
    state.heaterIsOn = false;
    Serial.println("Heater: OFF");
  }
}

void controlVentilation() {
  bool needVentilation = (state.humidity > OPT_HUMIDITY + HUMID_TOLERANCE) ||
                         (state.temperature > OPT_TEMP + TEMP_TOLERANCE) ||
                         (state.heaterIsOn);

  if (needVentilation && !state.fanIsOn) {
    digitalWrite(FAN_PIN, HIGH);
    state.fanIsOn = true;
    Serial.println("Fan: ON");
  } 
  else if (!needVentilation && state.fanIsOn) {
    digitalWrite(FAN_PIN, LOW);
    state.fanIsOn = false;
    Serial.println("Fan: OFF");
  }
}

void logSystemState() {
  Serial.println("\n===== System Status =====");
  Serial.print("Temperature: "); Serial.print(state.temperature); Serial.println(" °C");
  Serial.print("Humidity: "); Serial.print(state.humidity); Serial.println(" %");
  Serial.print("Light: "); Serial.print(state.lightLevel); Serial.println(" lx");
  Serial.print("Soil Moisture: "); Serial.println(state.moistureLevel);
  
  Serial.println("\nDevices:");
  Serial.println("Grow light: " + String(state.lightIsOn ? "ON" : "OFF"));
  Serial.println("Water pump: " + String(state.pumpIsOn ? "ON" : "OFF"));
  Serial.println("Heater: " + String(state.heaterIsOn ? "ON" : "OFF"));
  Serial.println("Fan: " + String(state.fanIsOn ? "ON" : "OFF"));
  Serial.println("=======================");
}

void loop() {
  readSensors();
  
  // Независимое управление устройствами
  controlLight();
  controlWater(); 
  controlTemperature();
  controlVentilation();
  
  logSystemState();
  
  delay(2000);
}

int main() {
  init();
  setup();
  while (true) {
    loop();
  }
  return 0;
}
