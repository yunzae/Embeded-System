int temperature_pin = A0;
float temp_C;
float computeTemperature(int analogReadValue);

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(temperature_pin, INPUT);
}

void loop() {
  temp_C = computeTemperature(analogRead(temperature_pin));
  Serial.print(temp_C / 100.0);
  Serial.print(" V : ");
  Serial.println(temp_C);

  Serial1.println(temp_C);
  delay(1000);
}

float computeTemperature(int analogReadValue){ 
  return ((float)analogReadValue * 5.0 / 1024.0) * 100.0;
}
