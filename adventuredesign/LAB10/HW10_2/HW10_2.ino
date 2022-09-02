String temp_C="";

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if(Serial1.available()){
    temp_C = Serial1.readStringUntil('\n');
    Serial.print("Current temperature : ");
    Serial.println(temp_C);
  }
}
