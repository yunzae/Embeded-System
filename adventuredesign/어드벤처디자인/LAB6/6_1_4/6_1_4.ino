int pin_button = 14;
int pin_LED1 = 13, pin_LED2 = 2;
unsigned long time_previous, time_current;
boolean LED_state1 = false;
boolean LED_state2 = false;

void setup() {
  pinMode(pin_button,INPUT);
  pinMode(pin_LED1, OUTPUT);
  digitalWrite(pin_LED1, LED_state1);
  pinMode(pin_LED2,OUTPUT);
  digitalWrite(pin_LED2,LED_state2);
  time_previous = millis();
}

void loop() {
  time_current = millis();
  if (time_current - time_previous >= 1000) {
    time_previous = time_current;
    LED_state1 = !LED_state1;
    digitalWrite(pin_LED1, LED_state1);
  }
  if (digitalRead(pin_button)){
    LED_state2 = !LED_state2;
    digitalWrite(pin_LED2, LED_state2);
    delay(100);
  }

}
