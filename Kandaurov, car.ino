constexpr int MOTOR1_DIR_PIN = 4;
constexpr int MOTOR1_PWM_PIN = 5;
constexpr int MOTOR2_DIR_PIN = 7;
constexpr int MOTOR2_PWM_PIN = 6;
constexpr int BUTTON_PIN = 12;

constexpr int LINE_SENSOR_LEFT = A2;
constexpr int LINE_SENSOR_RIGHT = A3;

constexpr int BASE_SPEED = 120;
constexpr int MAX_CORRECTION = 80;

constexpr int LINE_THRESHOLD = 900;
const long DEBOUNCE_DELAY = 50;

unsigned long lastDebounceTime = 0;
int lastButtonState = HIGH;
bool isRunning = false;

void initializeMotors() {
  pinMode(MOTOR1_DIR_PIN, OUTPUT);
  pinMode(MOTOR1_PWM_PIN, OUTPUT);
  pinMode(MOTOR2_DIR_PIN, OUTPUT);
  pinMode(MOTOR2_PWM_PIN, OUTPUT);
}

bool readButton() {
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading == LOW) {
      isRunning = !isRunning;
    }
  }
  lastButtonState = reading;
  return isRunning;
}

void setMotors(int speed1, int speed2) {
  speed1 = constrain(speed1, -255, 255);
  speed2 = constrain(speed2, -255, 255);

  digitalWrite(MOTOR1_DIR_PIN, speed1 > 0 ? HIGH : LOW);
  analogWrite(MOTOR1_PWM_PIN, abs(speed1));

  digitalWrite(MOTOR2_DIR_PIN, speed2 > 0 ? HIGH : LOW);
  analogWrite(MOTOR2_PWM_PIN, abs(speed2));
}

int readLineSensor(int pin) {
  if (pin < A0 || pin > A5) return -1;
  return analogRead(pin);
}

void followLine() {
  int leftValue = readLineSensor(LINE_SENSOR_LEFT);
  int rightValue = readLineSensor(LINE_SENSOR_RIGHT);

  int error = rightValue - leftValue;
  int correction = map(error, -1023, 1023, -MAX_CORRECTION, MAX_CORRECTION);

  int leftSpeed = BASE_SPEED - correction;
  int rightSpeed = BASE_SPEED + correction;

  setMotors(leftSpeed, rightSpeed);
}

void stopMotors() {
  setMotors(0, 0);
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  initializeMotors();
  Serial.begin(9600);
}

void loop() {
  readButton();

  if (isRunning) {
    followLine();

    int leftVal = readLineSensor(LINE_SENSOR_LEFT);
    int rightVal = readLineSensor(LINE_SENSOR_RIGHT);
    Serial.print("Left: ");
    Serial.print(leftVal);
    Serial.print(" | Right: ");
    Serial.println(rightVal);
  } else {
    stopMotors();
  }
}
