#include <LiquidCrystal.h>
unsigned time1, time2;
// 핀 번호 (RS, E, DB4, DB5, DB6, DB7)
LiquidCrystal lcd(44, 45, 46, 47, 48, 49); // LCD 연결

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); 
}

void loop() {
  int reading = analogRead(A1); //온도
  int reading1 = analogRead(A2); //조도
  float voltage1 = reading * 5.0 / 1024.0;
  float temper = voltage1 * 100;
    lcd.print("TEMP : ");
    lcd.print(temper);
    lcd.setCursor(0,1);
    lcd.print("LIGHT : ");
    lcd.print(reading1);
    lcd.setCursor(0, 0);
    delay(1000);
}
