String inputword[]={"a","b","c","d","e"};
void setup() {
  Serial.begin(9600);
}

void loop() {
    int state = 1;
    char buffer[128];
    int i=0;
    while (i<5){
      if (state == 1){
        Serial.print("Enter the "+String(i+1)+"th Word --> ");
        state = 2;
      }
      while (Serial.available()){
        int len = Serial.readBytesUntil('\n',buffer,127);
        if (len > 0) {
          buffer[len] = '\0';
          inputword[i] = String(buffer);
          Serial.println(inputword[i] );
          state =1;
          i++;
          break;
        }
      }
      
  
    }

  Serial.println("After Sorting");
  for(int i=0;i<5;i++){
    for(int j=i+1;j<5;j++){
      int compare = inputword[i].compareTo(inputword[j]);
      if (compare > 0) {
        String temp = inputword[i];
        inputword[i]= inputword[j];
        inputword[j]= temp;
      }
    }
  }
  for (int i = 0;i<5;i++){
    Serial.println(inputword[i]);
  }
 }
  
