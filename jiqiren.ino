// OmegaBot巡线机器人 - 初版本（带寻线功能）

// 定义电机控制引脚，电机引脚：rightSpeedPin和leftSpeedPin通过 PWM 控制电机转速（0-255）；rightDirPin和leftDirPin通过高低电平控制电机正反转。
//传感器引脚：红外传感器返回 0-1023 的模拟值（值越大表示反射光越强，通常黑线反射弱，值较小，但需根据实际环境调整threshold）。
//按钮引脚：使用INPUT_PULLUP模式（内部上拉电阻），未按下时引脚为 HIGH，按下时为 LOW（防抖动设计）。
//状态变量：isRunning控制机器人是否启动；isSearching用于丢失黑线时的搜索逻辑；searchStartTime记录搜索开始时间，用于超时判断。
int rightSpeedPin = 5;    // 右电机速度控制（PWM输出，0-255）
int leftSpeedPin = 6;     // 左电机速度控制
int rightDirPin = 4;      // 右电机方向控制（HIGH或LOW）
int leftDirPin = 7;       // 左电机方向控制

// 定义传感器引脚
int rightSensorPin = A0;  // 右红外传感器（检测黑线，返回0-1023）
int leftSensorPin = A1;   // 左红外传感器

// 定义按钮引脚
int buttonPin = A2;       // 启动/停止按钮

// 定义机器人状态
bool isRunning = false;   // 机器人是否运行（初始为停止）
bool isSearching = false; // 是否正在搜索黑线
unsigned long searchStartTime = 0; // 搜索开始时间

// 定义关键参数
int threshold = 500;      // 传感器阈值（高于此值认为检测到黑线）
int baseSpeed = 150;      // 基础速度（PWM值）
int searchTimeLimit = 5000; // 搜索超时时间（毫秒）

void setup() {
  // 初始化电机引脚为输出模式，电机引脚设为OUTPUT：确保可以通过digitalWrite（方向）和analogWrite（速度）控制电机。
//传感器引脚设为INPUT：读取红外传感器的模拟值。
//按钮启用INPUT_PULLUP：无需外部上拉电阻，按下时引脚电平从 HIGH 变为 LOW（更稳定）。
//串口初始化：通过Serial输出调试信息（如传感器值、状态变化），方便调试。这一部分包括所有setup的初始化函数解释
  pinMode(rightSpeedPin, OUTPUT);
  pinMode(leftSpeedPin, OUTPUT);
  pinMode(rightDirPin, OUTPUT);
  pinMode(leftDirPin, OUTPUT);
  
  // 初始化传感器引脚为输入模式
  pinMode(rightSensorPin, INPUT);
  pinMode(leftSensorPin, INPUT);
  
  // 初始化按钮引脚为输入，并启用内部上拉电阻
  pinMode(buttonPin, INPUT_PULLUP);
  
  // 初始化串口通信（用于调试）
  Serial.begin(9600);
  Serial.println("OmegaBot初始化完成！按按钮启动。");
}

void loop() {
  // 检查按钮状态，控制机器人启动/停止，主循环的核心逻辑是：
//不断检测按钮状态（checkButton()），切换isRunning状态。
//根据isRunning决定是否运行巡线或搜索逻辑。
//若未启动（!isRunning），立即停止电机。
//delay(10)用于降低循环频率，避免传感器读取过快导致数据不稳定。包括51-73行
  checkButton();
  
  // 如果机器人已启动，则执行相应逻辑
  if (isRunning) {
    if (isSearching) {
      handleSearch();  // 处理搜索状态
    } else {
      followLine();    // 正常巡线
    }
  } else {
    // 否则停止所有电机
    stopMotors();
  }
  
  // 短暂延时，稳定循环速度
  delay(10);
}

// 检查按钮状态，切换机器人运行状态，checkButton () 为按钮检测函数，去抖动逻辑：按钮按下时可能产生电平抖动（快速高低跳变），通过记录lastDebounceTime，仅当 200ms 内状态稳定为 LOW 时才认为是有效按下（避免误触发）。
//状态切换：按下按钮时isRunning取反（启动 / 停止），同时重置isSearching（避免搜索状态残留）。
void checkButton() {
  static bool lastButtonState = HIGH;  // 上次按钮状态
  static unsigned long lastDebounceTime = 0;  // 上次去抖时间
  
  // 读取当前按钮状态（LOW表示按下，HIGH表示松开）
  int currentButtonState = digitalRead(buttonPin);
  
  // 如果按钮状态发生变化，记录时间
  if (currentButtonState != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  // 防抖处理：如果持续200ms状态不变，认为是有效按下
  if ((millis() - lastDebounceTime) > 200) {
    // 如果确认按钮被按下（从HIGH变为LOW）
    if (currentButtonState == LOW) {
      isRunning = !isRunning;  // 切换运行状态
      isSearching = false;     // 重置搜索状态
      
      // 打印状态变化信息
      if (isRunning) {
        Serial.println("机器人启动！");
      } else {
        Serial.println("机器人停止！");
      }
    }
  }
  
  // 更新上次按钮状态
  lastButtonState = currentButtonState;
}

// 巡线主逻辑，followLine () 的巡线主逻辑，传感器值判断：通过analogRead读取红外传感器值，与threshold（500）比较，判断是否检测到黑线（值越大越可能是白色，值越小越可能是黑色，需根据实际环境校准），双传感器检测到黑线：说明机器人正沿黑线直行，电机全速前进。
//仅右传感器检测到黑线：说明机器人偏右（黑线在右侧），需要左转（左电机减速，右电机全速）。
//仅左传感器检测到黑线：说明机器人偏左（黑线在左侧），需要右转（右电机减速，左电机全速）。
//双传感器未检测到黑线：说明机器人偏离黑线，进入搜索模式（startSearch()）
void followLine() {
  // 读取左右传感器值
  int rightValue = analogRead(rightSensorPin);
  int leftValue = analogRead(leftSensorPin);
  
  // 将模拟值转换为布尔值（是否检测到黑线）
  bool rightLine = rightValue > threshold;
  bool leftLine = leftValue > threshold;
  
  // 打印传感器值（用于调试）
  Serial.print("右传感器: ");
  Serial.print(rightValue);
  Serial.print(" | 左传感器: ");
  Serial.print(leftValue);
  Serial.print(" | 状态: ");
  
  // 根据传感器检测结果控制电机
  if (rightLine && leftLine) {
    // 情况1：两个传感器都检测到黑线 -> 直行
    Serial.println("直行");
    moveForward(baseSpeed);
  } 
  else if (rightLine) {
    // 情况2：仅右传感器检测到黑线 -> 左转
    Serial.println("左转");
    turnLeft(baseSpeed);
  } 
  else if (leftLine) {
    // 情况3：仅左传感器检测到黑线 -> 右转
    Serial.println("右转");
    turnRight(baseSpeed);
  } 
  else {
    // 情况4：两个传感器都未检测到黑线 -> 开始搜索
    Serial.println("丢失黑线，开始搜索...");
    startSearch();
  }
}

// 启动搜索模式，startSearch () 为启动搜索
void startSearch() {
  isSearching = true;
  searchStartTime = millis();
  moveBackward(baseSpeed);  // 先后退
}

// 处理搜索逻辑，handleSearch ()函数为 处理搜索逻辑，搜索流程：后退阶段（0-500ms）：先后退离开当前区域，避免继续偏离黑线。旋转搜索（500ms-5000ms）：通过右转（顺时针旋转）扩大检测范围，同时持续读取传感器值，若重新检测到黑线则恢复巡线。超时处理（>5000ms）：长时间未找到黑线，停止机器人（避免无限旋转）。
void handleSearch() {
  unsigned long searchDuration = millis() - searchStartTime;
  
  if (searchDuration < 500) {  // 后退500ms
    moveBackward(baseSpeed);
  } 
  else if (searchDuration < searchTimeLimit) {  // 旋转搜索直到超时
    // 后退完成后开始旋转寻找
    turnRight(baseSpeed);  // 顺时针旋转
    
    // 检查是否重新找到黑线
    int rightValue = analogRead(rightSensorPin);
    int leftValue = analogRead(leftSensorPin);
    if (rightValue > threshold || leftValue > threshold) {
      Serial.println("重新找到黑线！");
      isSearching = false;
    }
  } 
  else {
    // 搜索超时，停止机器人
    Serial.println("搜索超时，停止运行");
    isRunning = false;
    isSearching = false;
    stopMotors();
  }
}

// 控制电机前进，电机控制函数，方向控制：通过digitalWrite设置rightDirPin和leftDirPin的高低电平（正转 / 反转需根据电机驱动板实际接线调整）。
//速度控制：通过analogWrite输出 PWM 值（0-255），值越大速度越快。
void moveForward(int speed) {
  digitalWrite(rightDirPin, LOW);   // 右电机正转
  digitalWrite(leftDirPin, LOW);    // 左电机正转
  analogWrite(rightSpeedPin, speed);
  analogWrite(leftSpeedPin, speed);
}

// 控制电机后退
void moveBackward(int speed) {
  digitalWrite(rightDirPin, HIGH);  // 右电机反转
  digitalWrite(leftDirPin, HIGH);   // 左电机反转
  analogWrite(rightSpeedPin, speed);
  analogWrite(leftSpeedPin, speed);
}

// 左转（左电机减速，右电机加速），转向控制，左转逻辑：左电机速度减半（慢），右电机全速（快），机器人整体向左偏转。
void turnLeft(int speed) {
  digitalWrite(rightDirPin, LOW);   // 右电机正转
  digitalWrite(leftDirPin, LOW);    // 左电机正转
  analogWrite(rightSpeedPin, speed);       // 右电机全速
  analogWrite(leftSpeedPin, speed * 0.5);  // 左电机半速
}

// 右转（右电机减速，左电机加速），转向控制，右转逻辑：右电机速度减半（慢），左电机全速（快），机器人整体向右偏转。
void turnRight(int speed) {
  digitalWrite(rightDirPin, LOW);   // 右电机正转
  digitalWrite(leftDirPin, LOW);    // 左电机正转
  analogWrite(rightSpeedPin, speed * 0.5);  // 右电机半速
  analogWrite(leftSpeedPin, speed);       // 左电机全速
}

// 停止所有电机
void stopMotors() {
  analogWrite(rightSpeedPin, 0);
  analogWrite(leftSpeedPin, 0);
} 
