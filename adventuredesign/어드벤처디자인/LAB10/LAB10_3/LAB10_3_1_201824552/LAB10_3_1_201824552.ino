


























































































































//for master
#include <Wire.h>

#define SLAVE 4

void i2c_communication();

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  i2c_communication();
  delay(1000);
}

void i2c_communication(){
  int reading = analogRead(A0);

  Wire.beginTransmission(SLAVE);
  Wire.write(reading >> 8);
  Wire.write(reading & 0xFF);
  Wire.endTransmission(SLAVE);

  Serial.print("I sent ");
  Serial.println(reading);
}
