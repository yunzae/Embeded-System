void setup() {
  Serial.begin(9600);

}

void loop()
{
  int n = 123;
  float f = 3.1415927;

  Serial.println(n, BIN);
  Serial.println(n, DEC);
  Serial.println(n, HEX);

  Serial.println();
  Serial.println(f);
  Serial.println(f, 5);

  while(true);
}
