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


void setup()
{
  pinMode(PIN_L_MOTOR, OUTPUT);
  pinMode(PIN_L_SWITCH, OUTPUT);
  pinMode(PIN_R_MOTOR, OUTPUT);
  pinMode(PIN_R_SWITCH, OUTPUT);
  pinMode(PIN_L_SENSOR, INPUT);
  pinMode(PIN_R_SENSOR, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
}


void init_data()
{
  Sensors.left_sensor = analogRead(PIN_L_SENSOR);
  Sensors.right_sensor = analogRead(PIN_R_SENSOR);
}


void configuration_of_motors(int speed_l, int speed_r)
{
  if (speed_l > 0){
    digitalWrite(PIN_L_SWITCH, 1);
    analogWrite(PIN_L_MOTOR, speed_l);
  } else {
    digitalWrite(PIN_L_SWITCH, 0);
    analogWrite(PIN_L_MOTOR, -speed_l);
  };

  if (speed_r > 0){
    digitalWrite(PIN_R_SWITCH, 1);
    analogWrite(PIN_R_MOTOR, speed_r);
  } else {
    digitalWrite(PIN_R_SWITCH, 0);
    analogWrite(PIN_R_MOTOR, -speed_r);
  };
}


void move_forward()
{
  if (900 <= Sensors.left_sensor <= 1000 and 900 <= Sensors.right_sensor <= 1000){
    configuration_of_motors(motors_speed, motors_speed);
  };
}


void turn_right()
{
  if (500 <= Sensors.left_sensor <= 700){
    configuration_of_motors(motors_speed, -motors_speed);
  };
}


void turn_left()
{
  if (500 <= Sensors.right_sensor <= 700){
    configuration_of_motors(-motors_speed, motors_speed);
  };
}


void check_of_line_loss() 
{
  if (500 <= Sensors.left_sensor <= 700 and 500 <= Sensors.right_sensor <= 700){
    digitalWrite(PIN_BUZZER, 1);
    delay(500);
    digitalWrite(PIN_BUZZER, 0);
    delay(500);
  };
}


void loop()
{
  init_data();

  check_of_line_loss();

  move_forward();

  turn_right();

  turn_left();
}
