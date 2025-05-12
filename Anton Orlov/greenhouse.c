#include <DHT.h>
#include <Arduino.h>

#define DHT_PIN             8
DHT envSensor(DHT_PIN, DHT11);

#define LIGHT_SENSOR_PIN    A0
#define MOISTURE_SENSOR_PIN A1

#define LED_GROW_PIN        6
#define WATER_PUMP_PIN      5 
#define HEATER_PIN          3
#define FAN_PIN             7

// Оптимальные значения
#define OPT_TEMP        25
#define OPT_HUMIDITY    50
#define OPT_MOISTURE    400   // Ниже этого значения - почва сухая
#define OPT_LIGHT       500

// Допуски
#define TEMP_TOLERANCE  2
#define HUMID_TOLERANCE 2
#define MOIST_TOLERANCE 50    // Увеличенный допуск для влажности почвы
#define LIGHT_TOLERANCE 2

// Настройки насоса
#define PUMP_RUN_DURATION   5000    // 5 секунд работы
#define PUMP_PAUSE_DURATION 30000   // 30 секунд паузы
#define MOISTURE_SAMPLES    5       // Количество измерений для усреднения

bool pumpIsOn = false;
unsigned long pumpCycleStart = 0;
unsigned long pumpPauseStart = 0;

void setup(void) {
  Serial.begin(115200);
  
  pinMode(LED_GROW_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  // Инициализация в выключенном состоянии
  digitalWrite(LED_GROW_PIN, LOW);
  digitalWrite(WATER_PUMP_PIN, HIGH);  // HIGH - насос выключен (если используем реле)
  digitalWrite(HEATER_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);

  envSensor.begin();
  Serial.println("System initialized");
}

// Функция для стабильного чтения влажности почвы
int readMoisture() {
  int sum = 0;
  for (int i = 0; i < MOISTURE_SAMPLES; i++) {
    sum += analogRead(MOISTURE_SENSOR_PIN);
    delay(10);
  }
  return sum / MOISTURE_SAMPLES;
}

void readSensors(int *temp, int *humidity, int 
