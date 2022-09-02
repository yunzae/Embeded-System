int Enable1 = 38;
int PWM1 = 9;
int DIR1 = 39;

int button_pin = 14;
boolean _direction = true;

void setup() {
  pinMode(Enable1, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(DIR1, OUTPUT);

  digitalWrite(Enable1, HIGH);
  digitalWrite(DIR1, _direction); //초기 정방향
  digitalWrite(PWM1, !_direction); //최고속도

  pinMode(button_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(button_pin)){
    _direction = !_direction;

    if(direction)
      Serial.println("Clockwire...");
    else
      Serial.println("Anti-clockwise...");

    digitalWrite(DIR1, _direction);
    digitalWrite(PWM1, !_direction);
    delay(2000);
  }
}
