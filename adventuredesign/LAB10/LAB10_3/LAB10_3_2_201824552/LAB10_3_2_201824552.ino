//for slave
#include <Wire.h>

#define SLAVE 4
void receiveFromMaster(int)

void setup() {
  Wire.begin(SLAVE);
  Wire.onReceive(receiveFromMaster);
  Serial.begin(9600);
}

void loop() {
}

void receiveFromMaster(int bytes){
  byte r1 = Wire.read();
  byte r2 = Wire.read();

  int value = (r1 << 8) + r2;
  Serial.print("I got ");
  Serial.println(value);
}
