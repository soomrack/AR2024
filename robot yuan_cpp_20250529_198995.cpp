#define PIN_L_MOTOR 4
#define PIN_L_SWITCH 5
#define PIN_R_MOTOR 7
#define PIN_R_SWITCH 6
#define PIN_L_SENSOR A0
#define PIN_R_SENSOR A1
#define PIN_BUZZER 9

struct Data_sensors {
  int left_sensor;
  int right_sensor;
};

int motors_speed = 100;
struct Data_sensors Sensors;

void setup() {
  pinMode(PIN_L_MOTOR, OUTPUT);
  pinMode(PIN_L_SWITCH, OUTPUT);
  pinMode(PIN_R_MOTOR, OUTPUT);
  pinMode(PIN_R_SWITCH, OUTPUT);
  pinMode(PIN_L_SENSOR, INPUT);
  pinMode(PIN_R_SENSOR, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
}

void init_data() {
  Sensors.left_sensor = analogRead(PIN_L_SENSOR);
  Sensors.right_sensor = analogRead(PIN_R_SENSOR);
}

void configuration_of_motors(int speed_l, int speed_r) {
  // 左电机控制
  digitalWrite(PIN_L_SWITCH, (speed_l > 0) ? HIGH : LOW);
  analogWrite(PIN_L_MOTOR, abs(speed_l));
  
  // 右电机控制
  digitalWrite(PIN_R_SWITCH, (speed_r > 0) ? HIGH : LOW);
  analogWrite(PIN_R_MOTOR, abs(speed_r));
}

void move_forward() {
  configuration_of_motors(motors_speed, motors_speed);
}

void turn_right() {
  configuration_of_motors(motors_speed, -motors_speed);
}

void turn_left() {
  configuration_of_motors(-motors_speed, motors_speed);
}

void check_of_line_loss() {
  if ((Sensors.left_sensor >= 500 && Sensors.left_sensor <= 700) && 
      (Sensors.right_sensor >= 500 && Sensors.right_sensor <= 700)) {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(500);
    digitalWrite(PIN_BUZZER, LOW);
    delay(500);
  }
}

void loop() {
  init_data();
  
  if ((Sensors.left_sensor >= 900 && Sensors.left_sensor <= 1000) && 
      (Sensors.right_sensor >= 900 && Sensors.right_sensor <= 1000)) {
    move_forward();
  } 
  else if (Sensors.left_sensor >= 500 && Sensors.left_sensor <= 700) {
    turn_right();
  } 
  else if (Sensors.right_sensor >= 500 && Sensors.right_sensor <= 700) {
    turn_left();
  }
  
  check_of_line_loss();
}