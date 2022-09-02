int pin_button = 15;
boolean state_previous = false;
boolean state_current;
int count = 0;
void setup() {
  Serial.begin(9600);
  pinMode(pin_button,INPUT);
}

void loop() {
  state_current = digitalRead(pin_button);
  if (state_current){
    if(state_previous == false){
      count++;
      state_previous = true;
      Serial.println(count);
    }
    delay(50);
  }
  else{
    state_previous = false;
  }
}
