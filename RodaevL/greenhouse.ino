#include <iarduino_DHT.h> 

// Инициализация датчика температуры и влажности
iarduino_DHT tempHumSensor(13);

// Названия пинов
#define lightSensorPin A0     // датчик освещенности
#define soilMoisturePin A1    // датчик влажности почвы
#define ledIndicatorPin 6     // светодиодный индикатор
#define fanPin 7              // вентилятор
#define ledOutputPin 6        // световой выход (может быть тот же, что и ledIndicator)
#define waterPumpPin 5        // помпа для полива
#define heaterFanPin 4        // нагреватель с вентилятором
#define tempHumSensorPin 9    // датчик температуры и влажности

// Структура для хранения параметров системы
struct SystemStatus {
  int soilMoistureThreshold = 770;   // минимальное значение влажности почвы
  int lightThreshold = 300;          // порог освещенности
  int soilMoisture;
  int lightLevel;
  unsigned long pumpTimer = 0;
  bool isPumpActive = false;
  bool pumpOnPhase = false;
};

SystemStatus systemParams;

int tempFlag = 0;
int humidityFlag = 0;
unsigned long delayDuration = 1000;

void setup() {
  Serial.begin(9600);
  
  pinMode(heaterFanPin, OUTPUT);
  pinMode(waterPumpPin, OUTPUT);
  pinMode(ledOutputPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  
  pinMode(soilMoisturePin, INPUT);
  pinMode(lightSensorPin, INPUT);
}

void readSensors() {
  systemParams.soilMoisture = analogRead(soilMoisturePin);
  systemParams.lightLevel = analogRead(lightSensorPin);
}

void printData() {
    Serial.print("ДАТЧИК ТЕМПЕРАТУРЫ И ВЛАЖНОСТИ: ");
    switch(tempHumSensor.read()){
        case DHT_OK:             Serial.println((String) tempHumSensor.hum + "% - " + tempHumSensor.tem + "*C"); break;
        case DHT_ERROR_CHECKSUM: Serial.println("Ошибка контрольной суммы"); break;
        case DHT_ERROR_DATA:     Serial.println("Ошибка данных. Проверьте подключение 'DHT'"); break;
        case DHT_ERROR_NO_REPLY: Serial.println("Нет ответа от датчика"); break;
        default:                 Serial.println("Ошибка"); break;
    }
    Serial.print("Влажность почвы:");
    Serial.println(analogRead(soilMoisturePin));
    Serial.print("Освещенность:");
    Serial.println(analogRead(lightSensorPin));
}

void temperatureAndFanControl() {
    if (tempHumSensor.tem >= 30.0) {
        digitalWrite(heaterFanPin, LOW);   // выключить нагреватель
        digitalWrite(fanPin, HIGH);        // включить вентилятор
        tempFlag = 1;
    } else if (tempHumSensor.tem <=15.0) {
        digitalWrite(heaterFanPin, HIGH);   // включить нагреватель
        digitalWrite(fanPin, HIGH);         // включить вентилятор
        tempFlag =1;
    } else {
        if (humidityFlag ==0) {
            digitalWrite(heaterFanPin, LOW);
            digitalWrite(fanPin, LOW);
            tempFlag=0;
        }
    }
}

void humidityControl() {
    if (tempHumSensor.hum >=70) {
        digitalWrite(fanPin, HIGH);
        humidityFlag=1;
    } else {
        if (tempFlag==0) {
            digitalWrite(fanPin, LOW);
            humidityFlag=0;
        }
    }
}

void soilMoistureRegulation() {
    if (systemParams.soilMoisture >= systemParams.soilMoistureThreshold) {
        unsigned long currentTime=millis();

        if (!systemParams.isPumpActive) {
            digitalWrite(waterPumpPin,HIGH);
            systemParams.pumpTimer=currentTime;
            systemParams.isPumpActive=true;
            systemParams.pumpOnPhase=true;
        } else {
            if (systemParams.pumpOnPhase && currentTime - systemParams.pumpTimer >=7000) {
                digitalWrite(waterPumpPin,LOW);
                systemParams.pumpTimer=currentTime;
                systemParams.pumpOnPhase=false;
            }
        }
    } else {
        digitalWrite(waterPumpPin,LOW);
        systemParams.isPumpActive=false;
        systemParams.pumpOnPhase=false;
    }
}

void lightRegulation() {
    if (systemParams.lightLevel >= systemParams.lightThreshold) {
        digitalWrite(ledIndicatorPin,HIGH);
    } else {
        digitalWrite(ledIndicatorPin,LOW);
    }
}

void pause() {
    delay(delayDuration);
}

void loop() {
    printData();
    
    readSensors();
    
    temperatureAndFanControl();
    
    humidityControl();
    
    soilMoistureRegulation();
    
    lightRegulation();
    
    pause();
}