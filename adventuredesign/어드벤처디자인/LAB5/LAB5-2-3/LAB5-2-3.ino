int pins_LED[] = {2,3,4,5};

void setup() {
  Serial.begin(9600);
  for(int i =0;i<4;i++){
    pinMode(pins_LED[i],OUTPUT);
  }
  pinMode(A0,INPUT);
}

void loop() {
  int ADC_value = analogRead(A0);
  int PWM_value[4] = {0, };
  Serial.println(String("ADC value : ") +ADC_value);
  for (int i=3; i>=0;i--){
    if (ADC_value >=256*i){
      PWM_value[i] = ADC_value -256*i;
      ADC_value -=(PWM_value[i] +1);
    }
    analogWrite(pins_LED[i],PWM_value[i]);
    Serial.print(" ");
    Serial.print(PWM_value[i]);
  }
  Serial.println();
  delay(500);

}
