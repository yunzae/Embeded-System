#include <pitches.h>

int speakerPin = 57; 
int melody[] = { 0, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};
int noteDuration = 4;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(56);
  float volt = reading*5.0/1024;
  int noteLength = 1000 / noteDuration;
  if(volt < (5.0/9.0))
    tone(speakerPin, melody[0], noteLength);
  else if(volt >(5.0/9.0) && volt < (5.0/9.0)*2)
    tone(speakerPin, melody[1], noteLength);
  else if(volt >(5.0/9.0)*2 && volt < (5.0/9.0)*3)
    tone(speakerPin, melody[2], noteLength);
  else if(volt >(5.0/9.0)*3 && volt < (5.0/9.0)*4)
    tone(speakerPin, melody[3], noteLength);
  else if(volt >(5.0/9.0)*4 && volt < (5.0/9.0)*5)
    tone(speakerPin, melody[4], noteLength);
  else if(volt >(5.0/9.0)*5 && volt < (5.0/9.0)*6)
    tone(speakerPin, melody[5], noteLength);
  else if(volt >(5.0/9.0)*6 && volt < (5.0/9.0)*7)
    tone(speakerPin, melody[6], noteLength);
  else if(volt >(5.0/9.0)*7 && volt < (5.0/9.0)*8)
    tone(speakerPin, melody[7], noteLength);
  else if(volt >(5.0/9.0)*8 && volt < (5.0/9.0)*9)
    tone(speakerPin, melody[8], noteLength);
  delay(10);
}
