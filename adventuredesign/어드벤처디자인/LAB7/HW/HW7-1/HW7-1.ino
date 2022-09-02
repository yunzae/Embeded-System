int pin[4] = {2, 3, 4, 5};

void setup() {
  for(int i=0; i<4; i++)
  {
    pinMode(pin[i], OUTPUT);
    digitalWrite(pin[i], LOW);
  }
  Serial.begin(9600); // 직렬 포트 초기화
}

void loop() {
  int reading = analogRead(56);
  Serial.println(reading);
    if(reading <= 150)
    {
      digitalWrite(pin[0], LOW);
      digitalWrite(pin[1], LOW);
      digitalWrite(pin[2], LOW);
      digitalWrite(pin[3], LOW);
    }
    else if(reading < 256)
    {
      digitalWrite(pin[0], HIGH);
      digitalWrite(pin[1], LOW);
      digitalWrite(pin[2], LOW);
      digitalWrite(pin[3], LOW);
    }
      
    else if(reading >256 && reading < 512)
    {
      digitalWrite(pin[0], HIGH);
      digitalWrite(pin[1], HIGH);
      digitalWrite(pin[2], LOW);
      digitalWrite(pin[3], LOW);
    }
    else if(reading >512 && reading < 768)
    {
      digitalWrite(pin[0], HIGH);
      digitalWrite(pin[1], HIGH);
      digitalWrite(pin[2], HIGH);
      digitalWrite(pin[3], LOW);
    }
    else if(reading >768 && reading < 1024)
    {
      digitalWrite(pin[0], HIGH);
      digitalWrite(pin[1], HIGH);
      digitalWrite(pin[2], HIGH);
      digitalWrite(pin[3], HIGH);
    }
    delay(1000);

}
