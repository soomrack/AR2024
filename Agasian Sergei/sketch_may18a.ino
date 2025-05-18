#define RIGHT_SPEED 5    // скорость правого мотора
#define LEFT_SPEED 6     // скорость левого мотора
#define RIGHT_DIR 4      // направление правого мотора
#define LEFT_DIR 7       // направление левого мотора
#define SENSOR_RIGHT A0  // аналоговый пин для правого датчика линии
#define SENSOR_LEFT A1   // аналоговый пин для левого датчика линии
#define BUTTON_PIN A2    // пин для кнопки 

const int SENSOR_BORDER = 500;  // пороговое значение для датчиков линии (отличает линию от фона)
const int BASE_SPEED = 150;        // базовая скорость движения
const int BACK_TIME = 200;         // время движения назад при потере линии (мс)

bool Active = false;             // состояние активности робота
bool Seek = false;          // режима поиска линии
unsigned long lostTime = 0;        // время потери линии

void setup() // настройка
{
    pinMode(RIGHT_DIR, OUTPUT); // направление вращения 4 пин
    pinMode(LEFT_DIR, OUTPUT);  // направление вращения 7 пин
    pinMode(RIGHT_SPEED, OUTPUT); // скорость 5 пин
    pinMode(LEFT_SPEED, OUTPUT);  // скорость 6 пин
    pinMode(BUTTON_PIN, INPUT_PULLUP); // пин А2 вкл/выкл
}

void loop()
{
    handleButton(); // проверка нажатия кнопки
    
    if(Active) { // проверка включения робота
        if(Seek) {
            handleSeek(); // режим поиска линии
        } else {
            followLine();   // режим следования по линии
        }
    } else {
        stopMotors();      // остановка моторов
    }
}

void followLine() 
{
    bool right = digitalReadSensor(SENSOR_RIGHT);
    bool left = digitalReadSensor(SENSOR_LEFT);

    if(right && left) {       
        moveForward(BASE_SPEED);
    } 
    else if(right) {          
        turnRight(BASE_SPEED);
    } 
    else if(left) {           
        turnLeft(BASE_SPEED);
    } 
    else {                    
        startSeek();
    }
}

void startSeek() 
{
    Seek = true;    // активирует режим поиска
    lostTime = millis();   // запоминает время потери линии
    moveBackward(BASE_SPEED); // двигается назад
}

void handleSeek() 
{
    if(millis() - lostTime > BACK_TIME) {  // проверяет, не истекло ли время движения назад
    turnRight(BASE_SPEED); // крутится, ища линию
}
    
    // если хотя бы один датчик снова видит линию
    if(digitalReadSensor(SENSOR_RIGHT) || digitalReadSensor(SENSOR_LEFT)) {
        Seek = false;      // выключает поиск
    }
}

void moveBackward(int speed) {
    digitalWrite(RIGHT_DIR, HIGH);  
    digitalWrite(LEFT_DIR, HIGH);
    analogWrite(RIGHT_SPEED, speed);
    analogWrite(LEFT_SPEED, speed);
}

void moveForward(int speed) {
    digitalWrite(RIGHT_DIR, LOW);   
    digitalWrite(LEFT_DIR, LOW);
    analogWrite(RIGHT_SPEED, speed);
    analogWrite(LEFT_SPEED, speed);
}

void turnRight(int speed) {
    digitalWrite(RIGHT_DIR, HIGH);  
    digitalWrite(LEFT_DIR, LOW);    
    analogWrite(RIGHT_SPEED, speed);
    analogWrite(LEFT_SPEED, speed);
}

void turnLeft(int speed) {
    digitalWrite(RIGHT_DIR, LOW);   
    digitalWrite(LEFT_DIR, HIGH);   
    analogWrite(RIGHT_SPEED, speed);
    analogWrite(LEFT_SPEED, speed);
}

void stopMotors() {
    analogWrite(RIGHT_SPEED, 0);    // остановка
    analogWrite(LEFT_SPEED, 0);
}

void handleButton() // работка с кнопкой
{
    static unsigned long lastPress = 0; // переменная сохраняет значение
    if(millis() - lastPress > 200 && digitalRead(BUTTON_PIN) == LOW) { // проверка, прошло ли 200мс с нажатия
        Active = !Active; // переключает состояние робота
        lastPress = millis(); // обновляет время последнего нажатия
    }
}

bool digitalReadSensor(int pin) { // переводит сигнал в логическое значение
    return analogRead(pin) > SENSOR_BORDER ? 1 : 0;
}