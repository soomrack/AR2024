#define M1_DIR 4
#define M1_PWM 5
#define M2_DIR 7
#define M2_PWM 6
int ButtonRead(int ButtonPin)
{
  int Data = digitalRead(ButtonPin);
  if(ButtonPin == 12) Data = !Data;
  return Data;
}

void InitMotors()
{
  pinMode(M1_DIR, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
}

void Motors(int Speed_1, int Speed_2)
{
  if(Speed_1 > 255) Speed_1 = 255;
  if(Speed_1 < -255) Speed_1 = -255;
  if(Speed_2 > 255) Speed_2 = 255;
  if(Speed_2 < -255) Speed_2 = -255;

  if(Speed_1 > 0)
  {
    digitalWrite(M1_DIR, 1);
    analogWrite(M1_PWM, Speed_1);
  }
  else
  {
    digitalWrite(M1_DIR, 0);
    analogWrite(M1_PWM, -Speed_1);
  }

  if(Speed_2 > 0)
  {
    digitalWrite(M2_DIR, 1);
    analogWrite(M2_PWM, Speed_2);
  }
  else
  {
    digitalWrite(M2_DIR, 0);
    analogWrite(M2_PWM, -Speed_2);
  }
}

//Ехать вперед
void MoveForward(int Speed)
{
  Motors(Speed, Speed);
}

int LineSensorRead(int SensorPin)
{
  if(SensorPin < A0 || SensorPin > A3)
    return -1;

  int Data = analogRead(SensorPin);
  return Data;
}

void TurnLeft(int Speed)
{
  Motors(-Speed, Speed);
}

void TurnRight(int Speed)
{
  Motors(Speed, -Speed);
}

void Stop()
{
  Motors(0, 0);
}


void setup()
{
  pinMode(12, INPUT_PULLUP);
  InitMotors();
  Serial.begin(9600);
}

void loop()
{
  while (ButtonRead(12))
  {
    do
    {
      MoveForward(100);

      int leftSensor = LineSensorRead(A2);
      int rightSensor = LineSensorRead(A3);

      if(leftSensor > 900)
      {
        TurnRight(80);
        delay(200);
      }
      else if(rightSensor > 900)
      {
        TurnLeft(80);
        delay(200);
      }
    }
    while(LineSensorRead(A2) < 900 && LineSensorRead(A3) < 900);
    Stop();
    delay(100);	
  }

  Serial.print("message");
  Serial.print(LineSensorRead(A2));
  Serial.println();
}