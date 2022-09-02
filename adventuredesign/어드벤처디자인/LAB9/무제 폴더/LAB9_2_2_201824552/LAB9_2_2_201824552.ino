int Enable1 = 38;
int PWM1 = 9;
int DIR1 = 39;

void setup() {
  pinMode(Enable1, OUTPUT);
  digitalWrite(Enable1, LOW);
  pinMode(PWM1, OUTPUT);
  pinMode(DIR1, OUTPUT);
}

void loop() {
  digitalWrite(Enable1, HIGH);

  digitalWrite(DIR1, HIGH); //정방향
  for(int i = 255; i>=0; i--){ //속도 점차 증가
    analogWrite(PWM1, i);
    delay(30);
  }
  digitalWrite(PWM1, HIGH); //속도0
  delay(200);

  digitalWrite(DIR1, LOW); //정방향
  for(int i = 0; i<=255; i++){ //속도 점차 증가
    analogWrite(PWM1, i);
    delay(30);
  }
  digitalWrite(PWM1, LOW); //속도0
  delay(200);

  digitalWrite(Enable1, LOW);
}
