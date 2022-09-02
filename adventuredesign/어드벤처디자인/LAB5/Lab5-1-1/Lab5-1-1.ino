int vResistor = A0;

void setup() {
  Serial.begin(9600);
  pinMode(vResistor,INPUT);
}

void loop() {
  Serial.println(analogRead(vResistor));
  delay(1000);

}
