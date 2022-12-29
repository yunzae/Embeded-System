// 배달로봇이 블루투스 사용 안 하는 코드
#include <SoftwareSerial.h>

SoftwareSerial HM10(4, 5); // 디지털핀 5번 RX, 디지털핀 4번 TX 블루투스

int press_Led = 3;
int press_SensorPin = A0;
int press_value = 0;

//모터B enable: pin8
//모터A enable:

//출발 버튼
int button_Pin = 8;

// 모터_전진컨트롤
int Left_motor_IN1 = 12;       // IN1
int Right_motor_IN2 = 13;      // IN2

// 모터_후진컨트롤
int Left_motor_IN3 = 10;      // IN3
int Right_motor_IN4 = 11;     // IN4

// 모터_속도컨트롤
int Left_PWM = 6;             // 왼쪽모터 속도
int Right_PWM = 7;            // 오른쪽모터 속도

// IR Sensor
const int Left_Sensor = 9;    // 왼쪽센서
const int Right_Sensor = 2;   // 오른쪽센서

int Left_Sensor_Value;        // 검은색:1
int Right_Sensor_Value;       // 흰색:0

void setup()
{
  Serial.begin(9600); // blue
  HM10.begin(9600); // blue
  pinMode(press_Led, OUTPUT);

  pinMode(button_Pin, INPUT);

  pinMode(Left_motor_IN1, OUTPUT);      // PIN 8
  pinMode(Right_motor_IN2, OUTPUT);     // PIN 9

  pinMode(Left_motor_IN3, OUTPUT);      // PIN 10
  pinMode(Right_motor_IN4, OUTPUT);     // PIN 11

  pinMode(Left_PWM, OUTPUT);            // PIN 5
  pinMode(Right_PWM, OUTPUT);           // PIN 6

  pinMode(Left_Sensor, INPUT);          // 왼쪽센서
  pinMode(Right_Sensor, INPUT);         // 오른쪽센서
}


void blue() { //
  while (1) {
    if (HM10.available())
    {
      Serial.write(HM10.read());
    }
    if (Serial.available())
    {
      HM10.write(Serial.read());
      //break;
    }
  }
}


bool orderFlag = false;
bool madeFlag = false;
void blue2() {
  while (1) {
    if (HM10.available() > 0)
    {
      int data = HM10.read();
      Serial.print(data);
      if (data == 49) { //1
        Serial.println("GO");
        orderFlag = true;
        //analogWrite(motor, 255);
      }
      else if (data == 50) { //2
        Serial.println("GO2");
        madeFlag = true;
        //analogWrite(motor, 255);
      }
    }
  }
}
int pressure() {
  press_value = analogRead(press_SensorPin); // 센서값 읽어 value 저장
  Serial.println(press_value); // 시리얼모니터로 출력
  press_value = map(press_value, 0, 1023, 0, 255); // value 저장된 센서값 (0-1024) 를 PWM 값 (0-255) 범위로 변환
  analogWrite(press_Led, press_value); // 변환된 PWM 값으로 LED 밝기 조절
  return press_value;
}

// 전진
void go() {
  digitalWrite(Left_motor_IN1, LOW);   // 왼쪽모터   전진_정지
  digitalWrite(Right_motor_IN2, HIGH);  // 오론쪽모터 전진_정지

  digitalWrite(Left_motor_IN3, HIGH);    // 왼쪽모터   후진_회전
  digitalWrite(Right_motor_IN4, LOW);   // 오른쪽모터 후진_회전

  Serial.println("go");
  delay(500);

  analogWrite(Left_PWM, 155);           // PWM값(0~255), 모터 회전속도 조절
  analogWrite(Right_PWM, 155);          // PWM값(0~255), 모터 회전속도 조절
  delay(5);
}

// 후진
void back() {
  digitalWrite(Left_motor_IN1, LOW);    // 왼쪽모터   전진_정지
  digitalWrite(Right_motor_IN2, HIGH);   // 오론쪽모터 전진_정지

  digitalWrite(Left_motor_IN3, LOW);   // 왼쪽모터   후진_회전
  digitalWrite(Right_motor_IN4, HIGH);  // 오른쪽모터 후진_회전

  Serial.println("back");
  delay(500);

  analogWrite(Left_PWM, 155);           // PWM값(0~255), 모터 회전속도 조절
  analogWrite(Right_PWM, 155);          // PWM값(0~255), 모터 회전속도 조절

}

// 정지
void brake() {
  digitalWrite(Left_motor_IN1, LOW);    // 왼쪽모터   전진_정지
  digitalWrite(Right_motor_IN2, LOW);   // 오론쪽모터 전진_정지

  digitalWrite(Left_motor_IN3, LOW);    // 왼쪽모터   후진_정지
  digitalWrite(Right_motor_IN4, LOW);   // 오른쪽모터 후진_정지
  delay(5);

  //Serial.println("stop");
  delay(500);
}

// 좌회전
void turn_left() {
  digitalWrite(Right_motor_IN2, HIGH);    // 왼쪽모터   전진_정지
  digitalWrite(Left_motor_IN1, LOW);  // 오론쪽모터 전진_회전

  digitalWrite(Left_motor_IN3, LOW);    // 왼쪽모터   후진_정지
  digitalWrite(Right_motor_IN4, LOW);   // 오른쪽모터 후진_정지

  analogWrite(Right_PWM, 255);           // PWM값(0~255), 모터 회전속도 조절
  delay(5);

  Serial.println("left");
  delay(500);
}

// 우회전
void turn_right() {
  digitalWrite(Left_motor_IN1, LOW);   // 왼쪽모터   전진_회전
  digitalWrite(Right_motor_IN2, LOW);   // 오론쪽모터 전진_정지

  digitalWrite(Right_motor_IN4, LOW);    // 왼쪽모터   후진_정지
  digitalWrite( Left_motor_IN3, HIGH);   // 오른쪽모터 후진_정지

  analogWrite(Left_PWM, 255);           // PWM값(0~255), 모터 회전속도 조절
  delay(5);

  Serial.println("right");
  delay(500);
}
int detectIR() {
  Right_Sensor_Value = digitalRead(Right_Sensor);
  Left_Sensor_Value = digitalRead(Left_Sensor);
  if (Left_Sensor_Value == HIGH && Right_Sensor_Value == HIGH)
    return 1;

  // 좌회전: 왼쪽센서 검은색, 오른쪽센서 흰색
  else if (Left_Sensor_Value == HIGH & Right_Sensor_Value == LOW)
    return 2;


  // 우회전: 왼쪽센서 흰색, 오른쪽센서 검은색
  else if (Left_Sensor_Value == LOW & Right_Sensor_Value == HIGH)
    return 3;

  // 정지: 왼쪽센서 흰색, 오른쪽센서 흰색
  else
    return 4;

}
void drive() {
  int result;
  while (1) {
    result = detectIR();
    switch (result) {
      case 1:
        go();
        break;
      case 2:
        turn_left();
        break;
      case 3:
        turn_right();
        break;
      default:
        brake();
        break;
    }
  }
  // // 전진: 왼쪽센서 검은색, 오른쪽센서 검은색
  // if (Left_Sensor_Value == HIGH && Right_Sensor_Value == HIGH)
  //   go();

  // // 좌회전: 왼쪽센서 검은색, 오른쪽센서 흰색
  // else if (Left_Sensor_Value == HIGH & Right_Sensor_Value == LOW)
  //   turn_left();


  // // 우회전: 왼쪽센서 흰색, 오른쪽센서 검은색
  // else if (Left_Sensor_Value == LOW & Right_Sensor_Value == HIGH)
  //   turn_right();

  // // 정지: 왼쪽센서 흰색, 오른쪽센서 흰색
  // else
  //   brake();
  //   //pressure();
  // }
}

void loop()
{
//  while(digitalRead(button_Pin)==HIGH){
//  Serial.println(digitalRead(button_Pin));
//    
//  }
//  Serial.print("Start Delivery\n");
//  while (detectIR() == 4) {
//    go();
//  }
//  Serial.print("find path\n");
//  while (detectIR() != 4) { //이탈할 경우 벗어남
//    drive();
//  }
//  Serial.println("디스펜서 도착");
//  delay(20000);
//  Serial.println("음료 배급 완료");
//  
//  while (detectIR() == 4) {
//    go();
//  }
//  Serial.print("find path\n");
//  while (detectIR() != 4) {
//    drive();
//  }
//  Serial.print("End Delivery");
drive();
}


/*
   배달로봇과 디스펜서 통신하는 원본 코드
  L298N - 2CH Motor Driver
  Direction         IN1    IN2    IN3    IN4
  -------------------------------------------
  GO                HIGH   HIGH   LOW    LOW
  BACK              LOW    LOW    HIGH   HIGH
  BRAKE             LOW    LOW    LOW    LOW
  LEFT_TURN         HIGH   LOW    LOW    LOW
  RIGHT_TURN        LOW    HIGH   LOW    LOW
  LEFT_BACK_TURN    LOW    LOW    HIGH   LOW
  RIGHT_BACK_TURN   LOW    LOW    LOW    HIGH

  PWM: 6V시 최소값 200이상은 되야 바퀴회전 가능 (너무 낮은 전압에서 회전 안됨)


  #include <SoftwareSerial.h>

  SoftwareSerial HM10(4,5); // 디지털핀 5번 RX, 디지털핀 4번 TX 블루투스

  int press_Led = 3;
  int press_SensorPin = A0;
  int press_value = 0;

  // 모터_전진컨트롤
  int Left_motor_IN1 = 12;       // IN1
  int Right_motor_IN2 = 13;      // IN2

  // 모터_후진컨트롤
  int Left_motor_IN3 = 10;      // IN3
  int Right_motor_IN4 = 11;     // IN4

  // 모터_속도컨트롤
  int Left_PWM=6;               // 왼쪽모터 속도
  int Right_PWM=7;              // 오른쪽모터 속도

  // IR Sensor
  const int Left_Sensor = 9;    // 왼쪽센서
  const int Right_Sensor = 2;   // 오른쪽센서

  int Left_Sensor_Value;        // 검은색:1
  int Right_Sensor_Value;       // 흰색:0

  void setup()
  {
  Serial.begin(9600); // blue
  HM10.begin(9600); // blue
  pinMode(press_Led, OUTPUT);

  pinMode(Left_motor_IN1, OUTPUT);      // PIN 8
  pinMode(Right_motor_IN2, OUTPUT);     // PIN 9

  pinMode(Left_motor_IN3, OUTPUT);      // PIN 10
  pinMode(Right_motor_IN4, OUTPUT);     // PIN 11

  pinMode(Left_PWM, OUTPUT);            // PIN 5
  pinMode(Right_PWM, OUTPUT);           // PIN 6

  pinMode(Left_Sensor, INPUT);          // 왼쪽센서
  pinMode(Right_Sensor, INPUT);         // 오른쪽센서
  }


  void blue() { //
  while(1) {
    if (HM10.available())
    {
      Serial.write(HM10.read());
    }
    if (Serial.available())
    {
      HM10.write(Serial.read());
      //break;
    }
  }
  }


  bool orderFlag=false;
  bool madeFlag=false;
  void blue2() {
  while(1) {
    if (HM10.available()>0)
    {
      int data = HM10.read();
      Serial.print(data);
      if (data == 49){ //1
        Serial.println("GO");
        orderFlag=true;
        //analogWrite(motor, 255);
      }
      else if (data == 50) { //2
      Serial.println("GO2");
        madeFlag=true;
        //analogWrite(motor, 255);
      }
    }
  }
  }
  int pressure() {
  press_value = analogRead(press_SensorPin); // 센서값 읽어 value 저장
  Serial.println(press_value); // 시리얼모니터로 출력
  press_value = map(press_value, 0, 1023, 0, 255); // value 저장된 센서값 (0-1024) 를 PWM 값 (0-255) 범위로 변환
  analogWrite(press_Led, press_value); // 변환된 PWM 값으로 LED 밝기 조절
  return press_value;
  }

  // 전진
  void go() {
  digitalWrite(Left_motor_IN1, LOW);   // 왼쪽모터   전진_정지
  digitalWrite(Right_motor_IN2, HIGH);  // 오론쪽모터 전진_정지

  digitalWrite(Left_motor_IN3, HIGH);    // 왼쪽모터   후진_회전
  digitalWrite(Right_motor_IN4, LOW);   // 오른쪽모터 후진_회전

  Serial.println("go");
  delay(500);

  analogWrite(Left_PWM, 255);           // PWM값(0~255), 모터 회전속도 조절
  analogWrite(Right_PWM, 255);          // PWM값(0~255), 모터 회전속도 조절
  delay(5);
  }

  // 후진
  void back() {
  digitalWrite(Left_motor_IN1, LOW);    // 왼쪽모터   전진_정지
  digitalWrite(Right_motor_IN2, HIGH);   // 오론쪽모터 전진_정지

  digitalWrite(Left_motor_IN3, LOW);   // 왼쪽모터   후진_회전
  digitalWrite(Right_motor_IN4, HIGH);  // 오른쪽모터 후진_회전

  Serial.println("back");
  delay(500);

  analogWrite(Left_PWM, 255);           // PWM값(0~255), 모터 회전속도 조절
  analogWrite(Right_PWM, 255);          // PWM값(0~255), 모터 회전속도 조절

  }

  // 정지
  void brake() {
  digitalWrite(Left_motor_IN1, LOW);    // 왼쪽모터   전진_정지
  digitalWrite(Right_motor_IN2, LOW);   // 오론쪽모터 전진_정지

  digitalWrite(Left_motor_IN3, LOW);    // 왼쪽모터   후진_정지
  digitalWrite(Right_motor_IN4, LOW);   // 오른쪽모터 후진_정지
  delay(5);

  Serial.println("stop");
  delay(500);
  }

  // 좌회전
  void turn_left(){
  digitalWrite(Left_motor_IN1, HIGH);    // 왼쪽모터   전진_정지
  digitalWrite(Right_motor_IN2, LOW);  // 오론쪽모터 전진_회전

  digitalWrite(Left_motor_IN3, LOW);    // 왼쪽모터   후진_정지
  digitalWrite(Right_motor_IN4, LOW);   // 오른쪽모터 후진_정지

  analogWrite(Right_PWM, 255);           // PWM값(0~255), 모터 회전속도 조절
  delay(5);

  Serial.println("left");
  delay(500);
  }

  // 우회전
  void turn_right() {
  digitalWrite(Left_motor_IN1, LOW);   // 왼쪽모터   전진_회전
  digitalWrite(Right_motor_IN2, LOW);   // 오론쪽모터 전진_정지

  digitalWrite(Left_motor_IN3, HIGH);    // 왼쪽모터   후진_정지
  digitalWrite(Right_motor_IN4, LOW);   // 오른쪽모터 후진_정지

  analogWrite(Left_PWM, 255);           // PWM값(0~255), 모터 회전속도 조절
  delay(5);

  Serial.println("right");
  delay(500);
  }
  int detectIR(){
  Right_Sensor_Value = digitalRead(Right_Sensor);
  Left_Sensor_Value = digitalRead(Left_Sensor);
  if (Left_Sensor_Value == HIGH && Right_Sensor_Value == HIGH)
    return 1;

  // 좌회전: 왼쪽센서 검은색, 오른쪽센서 흰색
  else if (Left_Sensor_Value == HIGH & Right_Sensor_Value == LOW)
    return 2;


  // 우회전: 왼쪽센서 흰색, 오른쪽센서 검은색
  else if (Left_Sensor_Value == LOW & Right_Sensor_Value == HIGH)
    return 3;

  // 정지: 왼쪽센서 흰색, 오른쪽센서 흰색
  else
    return 4;

  }
  void drive() {
  int result;
  while(1){
    result=detectIR();
    switch(result){
      case 1:
        go();
        break;
      case 2:
        turn_left();
        break;
      case 3:
        turn_right();
        break;
      default:
        brake();
        break;
    }
  }
  // // 전진: 왼쪽센서 검은색, 오른쪽센서 검은색
  // if (Left_Sensor_Value == HIGH && Right_Sensor_Value == HIGH)
  //   go();

  // // 좌회전: 왼쪽센서 검은색, 오른쪽센서 흰색
  // else if (Left_Sensor_Value == HIGH & Right_Sensor_Value == LOW)
  //   turn_left();


  // // 우회전: 왼쪽센서 흰색, 오른쪽센서 검은색
  // else if (Left_Sensor_Value == LOW & Right_Sensor_Value == HIGH)
  //   turn_right();

  // // 정지: 왼쪽센서 흰색, 오른쪽센서 흰색
  // else
  //   brake();
  //   //pressure();
  // }
  }

  void loop()
  {
  setup();
  while(1){
    if (HM10.available()>0) {
      while(!orderFlag){
        int data = HM10.read();
        Serial.print(data);
        if (data == 49){ //1
        Serial.println("delivery start!");
        orderFlag=true;
      }

      while(detectIR()==4){
        go();
      }
      while(detectIR()!=4){ //이탈할 경우 벗어남
        drive();
      }
      //블루투스 a 발신
      HM10.write("a");
      while(!madeFlag){ //음료 배출 대기
        int data = HM10.read();
        Serial.print(data);
        if (data == 50){ //2
        Serial.println("go to your customer!");
        madeFlag=true;
      }
      while(detectIR()==4){
        go();
      }
      while(detectIR()!=4){
        drive();
      }
      while(1){
        if(pressure()< 100) {
          break;
        }

      }
      //블루투스 b 발신
      HM10.write("b");
      orderFlag=false;
      madeFlag=false;
        }
      }
    }
  }
  }

*/
