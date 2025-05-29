#define PIN_L_MOTOR 4
#define PIN_L_SWITCH 5
#define PIN_R_MOTOR 7
#define PIN_R_SWITCH 6
#define PIN_L_SENSOR A0
#define PIN_R_SENSOR A1
#define PIN_BUZZER 9

// 传感器阈值（根据实际场地校准）
const int LINE_THRESHOLD = 700;  // 检测到黑线的最大值
const int BG_THRESHOLD = 900;    // 检测到背景的最小值

int motors_speed = 100;  // 基础电机速度

void setup() {
  // 配置所有引脚模式
  pinMode(PIN_L_MOTOR, OUTPUT);
  pinMode(PIN_L_SWITCH, OUTPUT);
  pinMode(PIN_R_MOTOR, OUTPUT);
  pinMode(PIN_R_SWITCH, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
}

// 电机控制函数
void config_motors(int speed_l, int speed_r) {
  // 左电机控制
  digitalWrite(PIN_L_SWITCH, speed_l > 0 ? HIGH : LOW);
  analogWrite(PIN_L_MOTOR, abs(speed_l));
  
  // 右电机控制
  digitalWrite(PIN_R_SWITCH, speed_r > 0 ? HIGH : LOW);
  analogWrite(PIN_R_MOTOR, abs(speed_r));
}

void loop() {
  // 实时读取传感器数值
  int left_val = analogRead(PIN_L_SENSOR);
  int right_val = analogRead(PIN_R_SENSOR);

  /* 行为优先级决策链（从上到下优先级降低）*/
  
  // 1. 线丢失检测（最高优先级）
  if (left_val <= LINE_THRESHOLD && right_val <= LINE_THRESHOLD) {
    config_motors(0, 0);  // 立即停止电机
    digitalWrite(PIN_BUZZER, HIGH);
    delay(500);
    digitalWrite(PIN_BUZZER, LOW);
    delay(500);
  }
  // 2. 前进：两个传感器都看到背景
  else if (left_val >= BG_THRESHOLD && right_val >= BG_THRESHOLD) {
    config_motors(motors_speed, motors_speed);
  }
  // 3. 右转：左侧传感器检测到线
  else if (left_val <= LINE_THRESHOLD) {
    config_motors(motors_speed, -motors_speed); // 左轮前进，右轮后退
  }
  // 4. 左转：右侧传感器检测到线
  else if (right_val <= LINE_THRESHOLD) {
    config_motors(-motors_speed, motors_speed); // 右轮前进，左轮后退
  }
  // 5. 安全停止（未预料到的情况）
  else {
    config_motors(0, 0);
  }
}