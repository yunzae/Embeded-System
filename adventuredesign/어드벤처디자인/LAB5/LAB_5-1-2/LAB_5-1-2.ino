int vResistor = A0;
int pins_LED[] = {2,3,4,5};
void setup() {
  Serial.begin(9600);
  pinMode(vResistor,INPUT);
  for (int i = 0; i<4;i++){
    pinMode(pins_LED[i],OUTPUT);
    digitalWrite(pins_LED[i],LOW);
  }
}

void loop() {
  int adc = analogRead(vResistor);
  int count_led = (adc >> 8) +1;
  for (int i=0; i<4;i++){
    if (i< count_led)
      digitalWrite(pins_LED[i],HIGH);
     else
      digitalWrite(pins_LED[i],LOW);
  }
  Serial.println(String("ADC :  ") + adc + ",LED count : " + count_led);
  delay(1000);
}
