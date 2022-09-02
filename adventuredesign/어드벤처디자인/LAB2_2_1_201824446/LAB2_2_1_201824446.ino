void setup() {
  Serial.begin(9600);

}

void loop() {
  Serial.print("String : ");
  Serial.println("Test String");
  Serial.print("Char : ");
  Serial.println("c");
  Serial.print("Integer : ");
  Serial.println(123);
  Serial.print("Float : ");
  Serial.println(3.14);

  byte data = 65;
  Serial.println();
  Serial.print("With print : ");
  Serial.println(data);
  
  Serial.print("With write : ");
  Serial.write(data);

  while(true);

}
