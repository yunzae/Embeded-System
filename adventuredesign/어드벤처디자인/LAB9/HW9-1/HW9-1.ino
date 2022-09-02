#include <Servo.h>

Servo myServo;
int interval = 20;
int servoPin = 11;
int previous_state14 = 0;
int current_state14 = 0;
int previous_state15 = 0;
int current_state15 = 0;
int angle = 0;
unsigned long time_previous, time_current;
void setup() {
  myServo.attach(servoPin); // 서보 모터 연결
  myServo.write(angle); // 0°에서 시작
  delay(100);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  time_previous = millis();
}

void loop() {
  current_state14 = digitalRead(14);
  current_state15 = digitalRead(15);
  time_current = millis();
  if (time_current - time_previous >= interval) {
    time_previous = time_current;
    if(current_state14)
    {
      if(previous_state14==0)
       {
        previous_state14 = 1;
        if(angle <= 170)
          angle = angle + 10;
       }
     }
    else
      previous_state14 = 0;

    if(current_state15)
    {
     if(previous_state15==0)
     {
       previous_state15 = 1;
       if(angle >= 10)
         angle = angle - 10;
     }
    }
     else
        previous_state15 = 0;
  }
  myServo.write(angle);
  delay(5);  
}
