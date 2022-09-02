int pin_button = 14;
int pin_LED1 = 13, pin_LED2 = 2;
boolean LED_state1 = false;
boolean LED_state2 = false;

void setup() {
  pinMode(pin_button,INPUT);
  pinMode(pin_LED1, OUTPUT);
  digitalWrite(pin_LED1, LED_state1);
  pinMode(pin_LED2,OUTPUT);
  digitalWrite(pin_LED2, LED_state2);

}

void loop() {
  digitalWrite(pin_LED1,LED_state1);
  delay(1000);
  LED_state1 = !LED_state1;
  if(digitalRead(pin_button)) {
    LED_state2 = !LED_state2;
    digitalWrite(pin_LED2, LED_state2);

  }

}
