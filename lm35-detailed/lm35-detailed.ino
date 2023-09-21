#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop(){
    int rawData = analogRead(A0);
    float vcc = 5.0;
    float voltage = rawData * (vcc / 1024.0);
    float temperature = voltage * 100;
    
    Serial.print("Temperature: ");
    lcd.setCursor(0,0);
    lcd.print("Temperature: ");
    
    Serial.print(temperature);
    Serial.println(" *C");
    lcd.setCursor(0,1);
    lcd.print(temperature);
    lcd.print(" ");
    lcd.print(char(223));
    lcd.print("C");
       
    delay(500);
}
