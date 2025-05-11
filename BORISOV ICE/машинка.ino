// ПИНЫ ДЛЯ ПОДКЛЮЧЕНИЯ
#define PIN_SPEED_RIGHT 5    // ШИМ для скорости правого мотора
#define PIN_SPEED_LEFT 6      // ШИМ для скорости левого мотора
#define PIN_DIR_RIGHT 4       // Направление правого мотора
#define PIN_DIR_LEFT 7        // Направление левого мотора
#define PIN_SENSOR_RIGHT A0   // Правый датчик линии
#define PIN_SENSOR_LEFT A1    // Левый датчик линии
#define PIN_BUTTON A2         // Кнопка включения

// НАСТРОЙКИ
#define SENSOR_TRESHOLD 500   // Порог срабатывания датчиков (0-1023)
#define MOTOR_SPEED 150       // Скорость моторов (0-255)
#define BACKUP_TIME 200       // Время движения назад при потере линии (мс)

// ПЕРЕМЕННЫЕ
boolean carActive = false;    // Флаг активности машинки
boolean searchingMode = false;// Режим поиска линии
unsigned long searchTimer;    // Таймер поиска линии

void setup() {
  // Настраиваем пины управления моторами
  pinMode(PIN_DIR_RIGHT, OUTPUT);
  pinMode(PIN_DIR_LEFT, OUTPUT);
  
  // Кнопка с подтяжкой к питанию
  pinMode(PIN_BUTTON, INPUT_PULLUP);
}

void loop() {
  checkButton(); // Проверяем кнопку
  
  if(carActive) {
    if(searchingMode) {
      searchLine(); // Поиск потерянной линии
    } else {
      lineFollowing(); // Основной режим следования
    }
  } else {
    stopCar(); // Остановка если выключено
  }
}

// ОСНОВНАЯ ФУНКЦИЯ СЛЕДОВАНИЯ ПО ЛИНИИ
void lineFollowing() {
  boolean rightSensor = readSensor(PIN_SENSOR_RIGHT);
  boolean leftSensor = readSensor(PIN_SENSOR_LEFT);

  if(rightSensor && leftSensor) {
    moveForward(); // Оба датчика видят линию
  } 
  else if(rightSensor) {
    turnRight();   // Только правый датчик
  }
  else if(leftSensor) {
    turnLeft();     // Только левый датчик
  }
  else {
    startSearch();  // Линия потеряна
  }
}

// ЗАПУСК ПОИСКА ЛИНИИ
void startSearch() {
  searchingMode = true;
  searchTimer = millis();
  moveBackward();
}

// ПРОЦЕДУРА ПОИСКА ЛИНИИ
void searchLine() {
  // Если прошло время поиска - едем вперед
  if(millis() - searchTimer > BACKUP_TIME) {
    searchingMode = false;
    moveForward();
  }
  
  // Если линия найдена - выходим из режима поиска
  if(readSensor(PIN_SENSOR_RIGHT) || readSensor(PIN_SENSOR_LEFT)) {
    searchingMode = false;
  }
}

// ЧТЕНИЕ ДАТЧИКА ЛИНИИ
boolean readSensor(int pin) {
  return analogRead(pin) > SENSOR_TRESHOLD;
}

// УПРАВЛЕНИЕ МОТОРАМИ
void moveForward() {
  digitalWrite(PIN_DIR_RIGHT, LOW);
  digitalWrite(PIN_DIR_LEFT, LOW);
  analogWrite(PIN_SPEED_RIGHT, MOTOR_SPEED);
  analogWrite(PIN_SPEED_LEFT, MOTOR_SPEED);
}

void moveBackward() {
  digitalWrite(PIN_DIR_RIGHT, HIGH);
  digitalWrite(PIN_DIR_LEFT, HIGH);
  analogWrite(PIN_SPEED_RIGHT, MOTOR_SPEED);
  analogWrite(PIN_SPEED_LEFT, MOTOR_SPEED);
}

void turnRight() {
  digitalWrite(PIN_DIR_RIGHT, HIGH);
  digitalWrite(PIN_DIR_LEFT, LOW);
  analogWrite(PIN_SPEED_RIGHT, MOTOR_SPEED);
  analogWrite(PIN_SPEED_LEFT, MOTOR_SPEED);
}

void turnLeft() {
  digitalWrite(PIN_DIR_RIGHT, LOW);
  digitalWrite(PIN_DIR_LEFT, HIGH);
  analogWrite(PIN_SPEED_RIGHT, MOTOR_SPEED);
  analogWrite(PIN_SPEED_LEFT, MOTOR_SPEED);
}

void stopCar() {
  analogWrite(PIN_SPEED_RIGHT, 0);
  analogWrite(PIN_SPEED_LEFT, 0);
}

// ПРОВЕРКА КНОПКИ С ЗАЩИТОЙ ОТ ДРЕБЕЗГА
void checkButton() {
  static unsigned long lastPress = 0;
  if(millis() - lastPress > 200 && digitalRead(PIN_BUTTON) == LOW) {
    carActive = !carActive;
    lastPress = millis();
  }
}