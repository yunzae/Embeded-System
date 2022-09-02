//for master

#include <SPI.h>
int SS_arduino =53;

void setup() {
  pinMode(SS_arduino, OUTPUT);
  digitalWrite(SS_arduino, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV16);
}

void loop() {
  const char *p = "Hello, World\n";
  digitalWrite(SS_arduino, LOW);
  for(int i=0; i < strlen(p); i++){
    SPI.transfer(p[i]);
  }
  digitalWrite(SS_arduino, HIGH);

  delay(1000);
}
