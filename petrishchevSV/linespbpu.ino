#include "Wire.h"

#define leftsens A1
#define rightsens A0
#define Mr_1 4
#define Mr_2 5
#define Ml_1 6
#define Ml_2 7

float kd = 0,
kp = 10,
v=3,
d_lim = 5,
u, left, right, P, D, errold;

void setup() {
  Serial.begin(9600);
  pinMode(leftsens, INPUT);
  pinMode(rightsens, INPUT);
  pinMode(Mr_1, OUTPUT);
  pinMode(Ml_1, OUTPUT);
  pinMode(Mr_2, OUTPUT);
  pinMode(Ml_2, OUTPUT);
}

void loop() {

  left = analogRead(leftsens);
  right = analogRead(rightsens);
  Serial.print(left);
  Serial.println(right);

  float err = left - right;
  P = kp * err;

  float d = err - errold;
  D = kd * d;
  D = max(min(D, d_lim), -d_lim);

  u = P + D;
  motors(min(v-u,10), min(v+u,10));
  delay(10);
  float errold = err;
}
