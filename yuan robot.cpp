// 定义电机、传感器和蜂鸣器的引脚
#define PIN_L_MOTOR 4      // 左侧电机PWM控制引脚
#define PIN_L_SWITCH 5     // 左侧电机方向控制引脚
#define PIN_R_MOTOR 7      // 右侧电机PWM控制引脚
#define PIN_R_SWITCH 6     // 右侧电机方向控制引脚
#define PIN_L_SENSOR A0    // 左侧传感器模拟输入引脚
#define PIN_R_SENSOR A1    // 右侧传感器模拟输入引脚
#define PIN_BUZZER 9       // 蜂鸣器控制引脚

// 传感器数据结构体
struct Data_sensors {
  int left_sensor;   // 左侧传感器值
  int right_sensor;  // 右侧传感器值
};

int motors_speed = 100;     // 电机基础速度
struct Data_sensors Sensors; // 传感器数据实例

void setup() {
  // 初始化所有引脚模式
  pinMode(PIN_L_MOTOR, OUTPUT);
  pinMode(PIN_L_SWITCH, OUTPUT);
  pinMode(PIN_R_MOTOR, OUTPUT);
  pinMode(PIN_R_SWITCH, OUTPUT);
  pinMode(PIN_L_SENSOR, INPUT);
  pinMode(PIN_R_SENSOR, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
}

// 读取传感器数据
void init_data() {
  Sensors.left_sensor = analogRead(PIN_L_SENSOR);
  Sensors.right_sensor = analogRead(PIN_R_SENSOR);
}

// 配置电机速度和方向
void configuration_of_motors(int speed_l, int speed_r) {
  // 控制左侧电机
  if (speed_l > 0) {
    digitalWrite(PIN_L_SWITCH, 1);  // 正转
    analogWrite(PIN_L_MOTOR, speed_l);
  } else {
    digitalWrite(PIN_L_SWITCH, 0);  // 反转
    analogWrite(PIN_L_MOTOR, -speed_l);
  }

  // 控制右侧电机
  if (speed_r > 0) {
    digitalWrite(PIN_R_SWITCH, 1);  // 正转
    analogWrite(PIN_R_MOTOR, speed_r);
  } else {
    digitalWrite(PIN_R_SWITCH, 0);  // 反转
    analogWrite(PIN_R_MOTOR, -speed_r);
  }
}

// 前进指令
void move_forward() {
  configuration_of_motors(motors_speed, motors_speed);
}

// 右转指令（左轮前进，右轮后退）
void turn_right() {
  configuration_of_motors(motors_speed, -motors_speed);
}

// 左转指令（左轮后退，右轮前进）
void turn_left() {
  configuration_of_motors(-motors_speed, motors_speed);
}

// 停止电机
void stop_motors() {
  configuration_of_motors(0, 0);
}

// 检测是否丢失路线
void check_of_line_loss() {
  // 当两侧传感器值都在500-700范围内时判定为路线丢失
  if (Sensors.left_sensor >= 500 && Sensors.left_sensor <= 700 && 
      Sensors.right_sensor >= 500 && Sensors.right_sensor <= 700) {
    // 蜂鸣器报警
    digitalWrite(PIN_BUZZER, 1);
    delay(500);
    digitalWrite(PIN_BUZZER, 0);
    delay(500);
    // 停止电机
    stop_motors();
  }
}

// 主循环
void loop() {
  init_data();  // 更新传感器数据
  
  check_of_line_loss(); // 路线丢失检测

  // 行为决策逻辑（优先级顺序：前进 > 右转 > 左转）
  if (Sensors.left_sensor >= 900 && Sensors.left_sensor <= 1000 && 
      Sensors.right_sensor >= 900 && Sensors.right_sensor <= 1000) {
    // 当两侧传感器值都在900-1000范围内时前进
    move_forward();
  } 
  else if (Sensors.left_sensor >= 500 && Sensors.left_sensor <= 700) {
    // 当左侧传感器在500-700范围内时右转
    turn_right();
  } 
  else if (Sensors.right_sensor >= 500 && Sensors.right_sensor <= 700) {
    // 当右侧传感器在500-700范围内时左转
    turn_left();
  } 
  else {
    // 无匹配条件时停止电机
    stop_motors();
  }
}