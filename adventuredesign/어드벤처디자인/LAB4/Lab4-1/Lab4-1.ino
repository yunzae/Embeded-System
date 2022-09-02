void setup() {
  Serial.begin(9600);
}

void loop() {
  String str1 = "One string",str2 = "Another string";
  int n = 1234;
  float f = 3.14;
  char c ='A';

   Serial.println(str1);
   Serial.println(str1+" " + str2);
   Serial.println(String(n));
   Serial.println(String(n,BIN));
   Serial.println(String(n,HEX));
   Serial.println(f);

   Serial.println("String + integer : "+String(n));
   String str3 = "String + character : ";
   str3 += n;
   Serial.println(str3);

   while(true);
  
}
