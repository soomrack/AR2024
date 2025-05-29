#include "DHT.h"
#define PIN_DHT 13
#define PIN_SOILHUMIDITY A1
#define PIN_PHOTO_SENSOR A0
#define PIN_RELAY_HEATER 4
#define PIN_RELAY_PUMP 5
#define PIN_RELAY_LIGHT 6
#define PIN_RELAY_FAN 7

DHT dht(PIN_DHT, DHT11);

struct Data_parameters {
  float humidity;
  float temperature;
  int soilhumidity;
  int illumination;
};

struct System_status {
  bool heater_on;
  bool fan_on;
  bool pump_on;
  bool light_on;
  unsigned long pump_start_time;
  unsigned long pump_last_run;
  unsigned long fan_start_time;
  unsigned long last_sensor_read;
};

struct Data_parameters Parameters;
struct System_status Status;

const unsigned long READ_INTERVAL = 1000;        // 传感器读取间隔(1秒)
const unsigned long PUMP_WORK_TIME = 3000;       // 水泵工作时间(3秒)
const unsigned long PUMP_PAUSE_TIME = 300000;    // 水泵暂停时间(5分钟)
const unsigned long FAN_MAX_RUN_TIME = 1800000;  // 风扇最大连续运行时间(30分钟)

// 阈值设置
const float TEMP_HIGH_THRESHOLD = 30.0;
const float TEMP_LOW_THRESHOLD = 15.0;
const float HUMIDITY_THRESHOLD = 60.0;
const int SOIL_MOISTURE_THRESHOLD = 200;
const int LIGHT_THRESHOLD = 300;

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  pinMode(PIN_RELAY_HEATER, OUTPUT);
  pinMode(PIN_RELAY_PUMP, OUTPUT);
  pinMode(PIN_RELAY_LIGHT, OUTPUT);
  pinMode(PIN_RELAY_FAN, OUTPUT);
  
  resetSystem();
}

void resetSystem() {
  digitalWrite(PIN_RELAY_HEATER, LOW);
  digitalWrite(PIN_RELAY_PUMP, LOW);
  digitalWrite(PIN_RELAY_LIGHT, LOW);
  digitalWrite(PIN_RELAY_FAN, LOW);
  
  Status.heater_on = false;
  Status.fan_on = false;
  Status.pump_on = false;
  Status.light_on = false;
  Status.pump_start_time = 0;
  Status.pump_last_run = 0;
  Status.fan_start_time = 0;
  Status.last_sensor_read = 0;
}

bool readSensors() {
  if (millis() - Status.last_sensor_read < READ_INTERVAL) {
    return false;
  }
  
  Parameters.humidity = dht.readHumidity();
  Parameters.temperature = dht.readTemperature();
  Parameters.soilhumidity = analogRead(PIN_SOILHUMIDITY);
  Parameters.illumination = 1023 - analogRead(PIN_PHOTO_SENSOR);
  
  if (isnan(Parameters.humidity) || isnan(Parameters.temperature)) {
    Serial.println("DHT传感器读取错误!");
    return false;
  }
  
  Status.last_sensor_read = millis();
  return true;
}

void regulateTemperature() {
  if (Parameters.temperature >= TEMP_HIGH_THRESHOLD) {
    setHeater(false);
    setFan(true);
  } 
  else if (Parameters.temperature <= TEMP_LOW_THRESHOLD) {
    setHeater(true);
    setFan(true);
  }
  else {
    // 温度在适宜范围内，检查是否需要为湿度控制保留风扇开启
    if (!needsFanForHumidity()) {
      setFan(false);
    }
    setHeater(false);
  }
}

bool needsFanForHumidity() {
  return Parameters.humidity >= HUMIDITY_THRESHOLD;
}

void regulateHumidity() {
  if (needsFanForHumidity()) {
    setFan(true);
  }
}

void regulateSoilHumidity() {
  // 检查水泵是否在暂停期
  if (millis() - Status.pump_last_run < PUMP_PAUSE_TIME) {
    return;
  }
  
  // 土壤干燥，启动水泵
  if (!Status.pump_on && Parameters.soilhumidity < SOIL_MOISTURE_THRESHOLD) {
    setPump(true);
    Status.pump_start_time = millis();
  }
  
  // 水泵运行时间结束
  if (Status.pump_on && (millis() - Status.pump_start_time >= PUMP_WORK_TIME)) {
    setPump(false);
    Status.pump_last_run = millis();
  }
}

void regulateIllumination() {
  setLight(Parameters.illumination <= LIGHT_THRESHOLD);
}

void safetyCheck() {
  // 风扇连续运行时间保护
  if (Status.fan_on && (millis() - Status.fan_start_time >= FAN_MAX_RUN_TIME)) {
    Serial.println("警告: 风扇连续运行时间过长，已关闭!");
    setFan(false);
  }
}

void setHeater(bool state) {
  if (state != Status.heater_on) {
    digitalWrite(PIN_RELAY_HEATER, state ? HIGH : LOW);
    Status.heater_on = state;
    Serial.print("加热器 ");
    Serial.println(state ? "开启" : "关闭");
  }
}

void setFan(bool state) {
  if (state != Status.fan_on) {
    digitalWrite(PIN_RELAY_FAN, state ? HIGH : LOW);
    Status.fan_on = state;
    
    if (state) {
      Status.fan_start_time = millis();
    }
    
    Serial.print("风扇 ");
    Serial.println(state ? "开启" : "关闭");
  }
}

void setPump(bool state) {
  if (state != Status.pump_on) {
    digitalWrite(PIN_RELAY_PUMP, state ? HIGH : LOW);
    Status.pump_on = state;
    
    Serial.print("水泵 ");
    Serial.println(state ? "开启" : "关闭");
  }
}

void setLight(bool state) {
  if (state != Status.light_on) {
    digitalWrite(PIN_RELAY_LIGHT, state ? HIGH : LOW);
    Status.light_on = state;
    
    Serial.print("补光灯 ");
    Serial.println(state ? "开启" : "关闭");
  }
}

void printSystemStatus() {
  Serial.print("温度: ");
  Serial.print(Parameters.temperature);
  Serial.print("°C | 空气湿度: ");
  Serial.print(Parameters.humidity);
  Serial.print("% | 土壤湿度: ");
  Serial.print(Parameters.soilhumidity);
  Serial.print(" | 光照强度: ");
  Serial.print(Parameters.illumination);
  
  Serial.print(" | 状态: ");
  Serial.print(Status.heater_on ? "加热 " : "");
  Serial.print(Status.fan_on ? "风扇 " : "");
  Serial.print(Status.pump_on ? "浇水 " : "");
  Serial.print(Status.light_on ? "补光" : "");
  Serial.println();
}

void loop() {
  if (readSensors()) {
    printSystemStatus();
    
    regulateTemperature();
    regulateHumidity();
    regulateSoilHumidity();
    regulateIllumination();
    
    safetyCheck();
  }
  
  delay(100);
}    