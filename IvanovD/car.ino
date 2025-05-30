#define MOTOR_L 5    
#define MOTOR_R 6    
#define DIR_L 10     
#define DIR_R 9      
#define SENSOR_L A1 
#define SENSOR_R A0  
#define BUTTON A2  

const int SPEED = 150;   
const int BLACK = 500;   
const int SEARCH_TIME = 300; 

bool isRunning = false;  
bool isSearching = false;
unsigned long searchStartTime = 0; 

void setup() {
  pinMode(DIR_L, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP); 
  stopMotors();
}

void loop() {
  checkButton();
  
  if(isRunning) {
    if(isSearching) {
      searchLine(); 
    } else {
      followLine(); 
    }
  } else {
    stopMotors(); 
  }
}

void checkButton() {
  static unsigned long lastPress = 0;
  if(millis() - lastPress > 200 && digitalRead(BUTTON) == LOW) {
    isRunning = !isRunning; 
    isSearching = false;    
    lastPress = millis();
  }
}

void followLine() {
  bool left = analogRead(SENSOR_L) < BLACK;
  bool right = analogRead(SENSOR_R) < BLACK;

  if(left && right) {
    moveForward(); 
  } 
  else if(right) {
    turnRight();   
  }
  else if(left) {
    turnLeft();    
  }
  else {
    startSearch(); 
  }
}

void startSearch() {
  isSearching = true;
  searchStartTime = millis();
  moveBackward();
}

void searchLine() {
  if(millis() - searchStartTime > SEARCH_TIME) {
    isSearching = false;
    moveForward(); 
  }
  

  if(analogRead(SENSOR_L) < BLACK || analogRead(SENSOR_R) < BLACK) {
    isSearching = false;
  }
}


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