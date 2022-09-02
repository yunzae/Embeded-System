int buttons[] = {14,15,16,17};


void setup() {
  Serial.begin(9600);
  for (int i = 0;i <4;i++){
    pinMode(buttons[i],INPUT);
  }
}

void loop() {
  for (int i = 0;i<4;i++){
    Serial.print(digitalRead(buttons[i]));
    Serial.print(" ");
  }
  Serial.println();
  delay(1000);
}
