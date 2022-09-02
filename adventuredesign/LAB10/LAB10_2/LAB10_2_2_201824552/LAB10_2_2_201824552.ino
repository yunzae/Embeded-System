// for master - control slave

#include <SPI.h>
char buf[100];
volatile byte pos = 0;
volatile boolean process_it = false;

void setup() {
  Serial.begin(9600);
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);

  SPI.setClockDivider(SPI_CLOCK_DIV16);

  SPCR |= (1 << SPE);
  SPCR &= ~(1 << MSTR);
  SPCR |= (1 << SPIE);
}

ISR(SPI_STC_vect){
  byte c = SPDR;
  if(pos < sizeof(buf)){
    buf[pos++] = c;

    if(c == '\n'){
      process_it = true;
    }
  }
}

void loop() {
  if(process_it){
    buf[pos] = 0;
    Serial.print(buf);

    pos = 0;
    process_it = false;
  }
}
