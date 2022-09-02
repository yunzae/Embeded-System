#include <Wire.h>
#include <ADXL345.h>


ADXL345 adxl;
int led1Pin = 11;
int toggle =0;
int toggle_on=1;
void setup(){
  Serial.begin(9600);
  adxl.powerOn();
  pinMode(led1Pin, OUTPUT);
  
 
  adxl.setActivityThreshold(75);
  adxl.setInactivityThreshold(75); 
  adxl.setTimeInactivity(10); 
 
 
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);
 
  
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);
 
  
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);
 
 
  adxl.setTapThreshold(50); 
  adxl.setTapDuration(15); 
  adxl.setDoubleTapLatency(80); 
  adxl.setDoubleTapWindow(200); 
 
 
  adxl.setFreeFallThreshold(7); 
  adxl.setFreeFallDuration(45); 
 
 
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN );
 
  
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  1);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);
}

void loop(){
  
  
  int x,y,z;  
  adxl.readXYZ(&x, &y, &z); 
  double xyz[3];
  double ax,ay,az;
  adxl.getAcceleration(xyz);
  ax = xyz[0];
  ay = xyz[1];
  az = xyz[2];
  byte interrupts = adxl.getInterruptSource();
  if(adxl.triggered(interrupts, ADXL345_SINGLE_TAP) ){
    if (toggle%2 == 1){
      Serial.println("-----------------------------");
      Serial.print("tap : ");
      Serial.println(toggle); 
      Serial.println("light on");
      Serial.print("불이 켜진 횟수: ");
      Serial.println(toggle_on);
      digitalWrite(led1Pin, HIGH);
      Serial.println("-----------------------------");
      toggle_on +=1;
    }
    else{
      Serial.println("-----------------------------");
      Serial.print("tap : ");
      Serial.println(toggle); 
      Serial.println("light off");
      digitalWrite(led1Pin, LOW);
      Serial.println("-----------------------------");
    }
      toggle+=1;
  }
  delay(500);
 
}
