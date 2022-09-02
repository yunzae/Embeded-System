int Enable1 = 38;
int PWM1 = 9;
int DIR1 = 39;
int state =0;
int pwm_value =0;
int button_pin=14;
void setup() {
  pinMode(Enable1, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(DIR1, OUTPUT);

  pinMode(button_pin,INPUT);
  digitalWrite(Enable1, HIGH);
  Serial.begin(9600);
}

void loop() { 
  if(digitalRead(button_pin)){
    state =(state+1)%3;
  }
  if (state==0){
    pwm_value =0;
  }
  if (state==1){
    pwm_value =128;
  }
  if (state==2){
    pwm_value =255;
  }
  digitalWrite(DIR1, LOW);
  analogWrite(PWM1, pwm_value);
  Serial.println(pwm_value);
  Serial.println(state);

  delay(1000);
}
