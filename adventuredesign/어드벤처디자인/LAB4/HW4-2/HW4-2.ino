int pins[] = {2,3,4,5};
int state = 0;
int pin_button = 14;
boolean state_previous = false;
boolean state_current;
int count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pin_button,INPUT);
  for (int i = 0; i < 4; i++){
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i],LOW);
    
  }
}

void loop() {
      state_current = digitalRead(pin_button);
      if (state_current){
        if(state_previous == false){
            count++;
            state_previous = true;
        }
        delay(50);
      }
      else{
          state_previous = false;
      }

  
    if(count%2==0){



      for (int i = 0; i < 4; i++){

         
         if (i==state){
           digitalWrite(pins[i], HIGH);
         } else{
           digitalWrite(pins[i], LOW);
         }
    
        

      }
  
    }



    if(count%2==1){
    
          for (int i = 0; i < 4; i++){
    
            
            if (i==state){
              digitalWrite(pins[-(i-3)], HIGH);
            } else{
              digitalWrite(pins[-(i-3)], LOW);
            }
          }

     
     
      
  
     }
      state = (state+1) %4;
      delay(500);









}
