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

#define OPT_TEMP        25
#define OPT_HUMIDITY    50
#define OPT_MOISTURE    400
#define OPT_LIGHT       500

#define TEMP_TOLERANCE  2
#define HUMID_TOLERANCE 2
#define MOIST_TOLERANCE 2
#define LIGHT_TOLERANCE 2

#define PUMP_RUN_DURATION  5000
#define PUMP_PAUSE_DURATION 30000

bool pumpIsOn = false;
unsigned long pumpCycleStart = 0;
unsigned long pumpPauseStart = 0;

void setup(void) {
  Serial.begin(115200);
  
  pinMode(LED_GROW_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  digitalWrite(LED_GROW_PIN, LOW);
  digitalWrite(WATER_PUMP_PIN, HIGH);
  digitalWrite(HEATER_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);
}

void readSensors(int *temp, int *humidity, int *light, int *moisture) {
  envSensor.read();
  *temp = envSensor.readTemperature();
  *humidity = envSensor.readHumidity();
  *light = analogRead(LIGHT_SENSOR_PIN);
  *moisture = analogRead(MOISTURE_SENSOR_PIN);
}

void controlLight(int light) {
  if (light < OPT_LIGHT - LIGHT_TOLERANCE) {
    digitalWrite(LED_GROW_PIN, HIGH);
  }
  else if (light > OPT_LIGHT + LIGHT_TOLERANCE) {
    digitalWrite(LED_GROW_PIN, LOW);
  }
}

void controlWater(int moisture) {
  if (moisture > OPT_MOISTURE + MOIST_TOLERANCE) {
    if (!pumpIsOn) {
      if ((pumpPauseStart == 0) || (millis() - pumpPauseStart >= PUMP_PAUSE_DURATION)) {
        digitalWrite(WATER_PUMP_PIN, LOW);
        pumpIsOn = true;
        pumpCycleStart = millis();
        Serial.println("Pump ON");
      }
    }
    else {
      if (millis() - pumpCycleStart >= PUMP_RUN_DURATION) {
        digitalWrite(WATER_PUMP_PIN, HIGH);
        pumpIsOn = false;
        pumpPauseStart = millis();
        Serial.println("Pump OFF");
      }
    }
  }
  else {
    digitalWrite(WATER_PUMP_PIN, HIGH);
    pumpIsOn = false;
    pumpCycleStart = 0;
    pumpPauseStart = 0;
  }
}

void controlTemperature(int temp) {
  if (temp < OPT_TEMP - TEMP_TOLERANCE) {
    digitalWrite(HEATER_PIN, HIGH);
  }
  else if (temp >= OPT_TEMP) {
    digitalWrite(HEATER_PIN, LOW);
  }
}

void controlVentilation(int temp, int humidity) {
  if (humidity > OPT_HUMIDITY + HUMID_TOLERANCE || temp > OPT_TEMP + 1 || digitalRead(HEATER_PIN) == HIGH)
    digitalWrite(FAN_PIN, HIGH);
  else
    digitalWrite(FAN_PIN, LOW);
}

void logData(int temp, int humidity, int light, int moisture) {
  Serial.print("T: ");
  Serial.print(temp);
  Serial.print("C, H: ");
  Serial.print(humidity);
  Serial.print("%, Light: ");
  Serial.print(light);
  Serial.print(", Moisture: ");
  Serial.println(moisture);
}

void loop(void) {
  int temp, humidity, light, moisture;
  
  readSensors(&temp, &humidity, &light, &moisture);
  
  controlLight(light);
  controlWater(moisture);
  controlTemperature(temp);
  controlVentilation(temp, humidity);
  
  logData(temp, humidity, light, moisture);
  
  delay(1000);
}

int main(void) {
  init();
  setup();
  for (;;) {
    loop();
  }
  return 0;
}
