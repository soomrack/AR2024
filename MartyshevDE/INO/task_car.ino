#define LEFT_SENSOR A2
#define RIGHT_SENSOR A3
#define LEFT_MOTOR_FORWARD 6
#define LEFT_MOTOR_BACKWARD 7
#define RIGHT_MOTOR_FORWARD 5
#define RIGHT_MOTOR_BACKWARD 4
//мб поменять будет(расположение моторов)
#define PIN_BUTTON 8

void setup() 
{
    pinMode(PIN_BUTTON, INPUT_PULLUP);
    
    pinMode(LEFT_SENSOR, INPUT);
    pinMode(RIGHT_SENSOR, INPUT);
    
    pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
    pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
}