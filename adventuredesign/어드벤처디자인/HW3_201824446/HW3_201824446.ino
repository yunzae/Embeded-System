int pins[] = {2,3,4,5};
int state = 0;
int shift = 0;


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++){
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i],LOW);
    
  }
}

void loop() {
  for(int i = 0;i<4;i++){
      if(i<state+1){
        Serial.print("O ");
        digitalWrite(pins[i], HIGH);
      }
      else{
        Serial.print("X ");
        digitalWrite(pins[i], LOW);
      }
    }

  if(shift==0){
    state = state+1;
  }
  else{
    state = state-1;
  }
  
  if (state==3 || state == 0){
    shift = (shift+1)%2;
  }
  Serial.println();
  delay(1000);
  
}
