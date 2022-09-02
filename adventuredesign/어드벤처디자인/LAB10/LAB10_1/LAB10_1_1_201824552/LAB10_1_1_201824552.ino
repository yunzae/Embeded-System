#include <SoftwareSerial.h>
SoftwareSerial mySerial(4,5); // call Constructure
int button_pin = 2;
boolean previous_state = false;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(button_pin, INPUT);
}

void loop() {
  boolean state = digitalRead(button_pin);

  if(state){
    if(previous_state == false){
      mySerial.write('1');
      Serial.println("button is pressed...");
    }
    previous_state = true;
    delay(20);
  }
  else{
    previous_state = false;
  }
}
