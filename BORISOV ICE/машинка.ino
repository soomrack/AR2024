#define PIN_SPEED_RIGHT 5  
#define PIN_SPEED_LEFT 6      
#define PIN_DIR_RIGHT 4       
#define PIN_DIR_LEFT 7        
#define PIN_SENSOR_RIGHT A0   
#define PIN_SENSOR_LEFT A1    
#define PIN_BUTTON A2         


#define SENSOR_TRESHOLD 500   
#define MOTOR_SPEED 150      
#define BACKUP_TIME 200      


boolean carActive = false;    
boolean searchingMode = false;
unsigned long searchTimer;    

void setup() {
 
  pinMode(PIN_DIR_RIGHT, OUTPUT);
  pinMode(PIN_DIR_LEFT, OUTPUT);
  
 
  pinMode(PIN_BUTTON, INPUT_PULLUP);
}

void loop() {
  checkButton(); 
  
  if(carActive) {
    if(searchingMode) {
      searchLine(); 
    } else {
      lineFollowing(); 
    }
  } else {
    stopCar(); 
  }
}

void lineFollowing() {
  boolean rightSensor = readSensor(PIN_SENSOR_RIGHT);
  boolean leftSensor = readSensor(PIN_SENSOR_LEFT);

  if(rightSensor && leftSensor) {
    moveForward(); 
  } 
  else if(rightSensor) {
    turnRight();  
  }
  else if(leftSensor) {
    turnLeft();     
  }
  else {
    startSearch(); 
  }
}

void startSearch() {
  searchingMode = true;
  searchTimer = millis();
  moveBackward();
}

void searchLine() {
  
  if(millis() - searchTimer > BACKUP_TIME) {
    searchingMode = false;
    moveForward();
  }
  
 
  if(readSensor(PIN_SENSOR_RIGHT) || readSensor(PIN_SENSOR_LEFT)) {
    searchingMode = false;
  }
}


boolean readSensor(int pin) {
  return analogRead(pin) > SENSOR_TRESHOLD;
}


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

void checkButton() {
  static unsigned long lastPress = 0;
  if(millis() - lastPress > 200 && digitalRead(PIN_BUTTON) == LOW) {
    carActive = !carActive;
    lastPress = millis();
  }
}
