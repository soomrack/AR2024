#define LEFT_SENSOR A2
#define RIGHT_SENSOR A3
#define LEFT_MOTOR_FORWARD 6
#define LEFT_MOTOR_BACKWARD 7
#define RIGHT_MOTOR_FORWARD 5
#define RIGHT_MOTOR_BACKWARD 4
//мб поменять будет(расположение моторов)
#define PIN_BUTTON 8


void pins_stats() 
{
    pinMode(PIN_BUTTON, INPUT_PULLUP);
    
    pinMode(LEFT_SENSOR, INPUT);
    pinMode(RIGHT_SENSOR, INPUT);
    
    pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
    pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
    pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
}


void sensors ()
{
    int leftState = digitalRead(LEFT_SENSOR);   
    int rightState = digitalRead(RIGHT_SENSOR); 
}


void ride ()
{
    if (leftState == HIGH && rightState == HIGH) {
        moveForward();
    }
    else if (leftState == LOW && rightState == HIGH) {
        turnRight();
    }
    else if (leftState == HIGH && rightState == LOW) {
        turnLeft();
    }
    else {
        moveInCircle();
    }
}


void moveForward() 
{
    digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
    digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
    digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}


void moveBackward() 
{
    digitalWrite(LEFT_MOTOR_FORWARD, LOW);
    digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
    digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
}


void turnLeft() 
{
    digitalWrite(LEFT_MOTOR_FORWARD, LOW);
    digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
    digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
    digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}


void turnRight() 
{
    digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
    digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
}

void moveInCircle() 
{
    digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
    digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
}


void setup ()
{
    pins_stats ();
}


void loop ()
{
    sensors();
}