// Пины подключения
#define MOTOR_L 5    // Левый мотор (PWM скорость)
#define MOTOR_R 6    // Правый мотор (PWM скорость)
#define DIR_L 4      // Направление левого мотора
#define DIR_R 7      // Направление правого мотора
#define SENSOR_L A1  // Левый датчик
#define SENSOR_R A0  // Правый датчик
#define BUTTON A2    // Кнопка старта/стопа

// Настройки
const int SPEED = 150;   // Стандартная скорость (0-255)
const int BLACK = 500;   // Порог для чёрной линии
const int SEARCH_TIME = 300; // Время поиска линии (мс)

// Состояния
bool isRunning = false;  // Флаг работы
bool isSearching = false;// Флаг поиска линии
unsigned long searchStartTime = 0; // Время начала поиска

void setup() {
  pinMode(DIR_L, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP); // Кнопка с подтяжкой к +5V
  stopMotors();
}

void loop() {
  checkButton(); // Проверяем кнопку
  
  if(isRunning) {
    if(isSearching) {
      searchLine(); // Поиск линии
    } else {
      followLine(); // Движение по линии
    }
  } else {
    stopMotors(); // Остановка
  }
}

void checkButton() {
  static unsigned long lastPress = 0;
  // Защита от дребезга - проверяем раз в 200мс
  if(millis() - lastPress > 200 && digitalRead(BUTTON) == LOW) {
    isRunning = !isRunning; // Переключаем состояние
    isSearching = false;    // Сбрасываем поиск
    lastPress = millis();
  }
}

void followLine() {
  bool left = analogRead(SENSOR_L) < BLACK;
  bool right = analogRead(SENSOR_R) < BLACK;

  if(left && right) {
    moveForward(); // Оба на линии - вперед
  } 
  else if(right) {
    turnRight();   // Поворот вправо
  }
  else if(left) {
    turnLeft();    // Поворот влево
  }
  else {
    startSearch(); // Линия потеряна - начать поиск
  }
}

void startSearch() {
  isSearching = true;
  searchStartTime = millis();
  moveBackward(); // Начинаем движение назад
}

void searchLine() {
  // Если время поиска истекло
  if(millis() - searchStartTime > SEARCH_TIME) {
    isSearching = false;
    moveForward(); // Пробуем снова вперед
  }
  
  // Если хотя бы один датчик нашел линию
  if(analogRead(SENSOR_L) < BLACK || analogRead(SENSOR_R) < BLACK) {
    isSearching = false;
  }
}

// Функции движения
void moveForward() {
  digitalWrite(DIR_L, LOW);
  digitalWrite(DIR_R, LOW);
  analogWrite(MOTOR_L, SPEED);
  analogWrite(MOTOR_R, SPEED);
}

void moveBackward() {
  digitalWrite(DIR_L, HIGH);
  digitalWrite(DIR_R, HIGH);
  analogWrite(MOTOR_L, SPEED);
  analogWrite(MOTOR_R, SPEED);
}

void turnRight() {
  digitalWrite(DIR_L, LOW);
  digitalWrite(DIR_R, HIGH);
  analogWrite(MOTOR_L, SPEED);
  analogWrite(MOTOR_R, SPEED);
}

void turnLeft() {
  digitalWrite(DIR_L, HIGH);
  digitalWrite(DIR_R, LOW);
  analogWrite(MOTOR_L, SPEED);
  analogWrite(MOTOR_R, SPEED);
}

void stopMotors() {
  analogWrite(MOTOR_L, 0);
  analogWrite(MOTOR_R, 0);
}