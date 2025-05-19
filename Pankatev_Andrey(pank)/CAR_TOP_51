#define RIGHT_SPEED 5
#define LEFT_SPEED 6
#define RIGHT_DIR 4
#define LEFT_DIR 7
#define SENSOR_RIGHT A0
#define SENSOR_LEFT A1
#define BUTTON_PIN A2

const int SENSOR_THRESHOLD = 500; 
const int BASE_SPEED = 150;       
const int BACK_TIME = 200;        

bool isActive = false;
bool isSearching = false;
unsigned long lostTime = 0;

void setup() 
{
    pinMode(RIGHT_DIR, OUTPUT);
    pinMode(LEFT_DIR, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
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
        startSearch();
    }
}


void startSearch() 
{
    isSearching = true;
    lostTime = millis();
    moveBackward(BASE_SPEED);
}


void handleSearch() 
{
    if(millis() - lostTime > BACK_TIME) {
        isSearching = false;
        moveForward(BASE_SPEED);
    }
    
    if(digitalReadSensor(SENSOR_RIGHT) || digitalReadSensor(SENSOR_LEFT)) {
        isSearching = false;
    }
}


void moveBackward(int speed) 
{
    digitalWrite(RIGHT_DIR, HIGH);  
    digitalWrite(LEFT_DIR, HIGH);
    analogWrite(RIGHT_SPEED, speed);
    analogWrite(LEFT_SPEED, speed);
}


void handleButton() 
{
    static unsigned long lastPress = 0;
    if(millis() - lastPress > 200 && digitalRead(BUTTON_PIN) == LOW) {
        isActive = !isActive;
        lastPress = millis();
    }
}

bool digitalReadSensor(int pin) 
{
    return analogRead(pin) > SENSOR_THRESHOLD ? 1 : 0;
}

void moveForward(int speed) 
{
    digitalWrite(RIGHT_DIR, LOW);
    digitalWrite(LEFT_DIR, LOW);
    analogWrite(RIGHT_SPEED, speed);
    analogWrite(LEFT_SPEED, speed);
}

void turnRight(int speed) 
{
    digitalWrite(RIGHT_DIR, HIGH);
    digitalWrite(LEFT_DIR, LOW);
    analogWrite(RIGHT_SPEED, speed);
    analogWrite(LEFT_SPEED, speed);
}

void turnLeft(int speed) 
{
    digitalWrite(RIGHT_DIR, LOW);
    digitalWrite(LEFT_DIR, HIGH);
    analogWrite(RIGHT_SPEED, speed);
    analogWrite(LEFT_SPEED, speed);
}

void stopMotors() 
{
    analogWrite(RIGHT_SPEED, 0);
    analogWrite(LEFT_SPEED, 0);
}

void loop()
{
    handleButton();
    
    if(isActive) {
        if(isSearching) {
            handleSearch();
        } else {
            followLine();
        }
    } else {
        stopMotors();
    }
}
