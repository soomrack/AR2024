void motors(int speed_left, int speed_right)
{
  //Обрезаем значение скорости до допустимых величин
  speed_left = constrain(speed_left, -255, 255);
  speed_right = constrain(speed_right, -255, 255);

  
  if (speed_left>=0)
  {
    digitalWrite(Ml_1, HIGH);
    digitalWrite(Ml_2, speed_left);
  }
  if (speed_right>=0)
  {
    digitalWrite(Mr_1, HIGH);
    digitalWrite(Mr_2, speed_right);
  }
  if (speed_left<0)
  {
    digitalWrite(Ml_1, LOW);
    digitalWrite(Ml_2, abs(speed_left));
  }
  if (speed_right<0)
  {
    digitalWrite(Mr_1, LOW);
    digitalWrite(Mr_2, abs(speed_right));
  }
  
}