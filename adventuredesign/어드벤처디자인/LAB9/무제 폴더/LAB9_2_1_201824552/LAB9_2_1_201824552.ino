int Enable1 = 38; //Motor1
int PWM1 = 9;
int DIR1 = 39;

int Enable2 = 40; //Motor2
int PWM2 = 10;
int DIR2 = 41;

void setup() {
  pinMode(Enable1, OUTPUT);
  digitalWrite(Enable1, LOW);
  pinMode(PWM1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  
  pinMode(Enable2, OUTPUT);
  digitalWrite(Enable2, LOW);
  pinMode(PWM2, OUTPUT);
  pinMode(DIR2, OUTPUT);
}

void loop() {
  digitalWrite(Enable1, HIGH);

  digitalWrite(DIR1, HIGH); //정방향
  digitalWrite(PWM1, LOW); //최고속도
  delay(4000);
  digitalWrite(PWM1, HIGH); //속도0
  delay(200);

  digitalWrite(DIR1, LOW); //역방향
  digitalWrite(PWM1, HIGH); //최고속도
  delay(4000);
  digitalWrite(PWM1, LOW); //속도0
  delay(200);

  digitalWrite(Enable1, LOW);
}
