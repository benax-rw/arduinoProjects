#include <LiquidCrystal_I2C.h>
#define greenLED 16
#define redLED 14
#define buzzer 12

LiquidCrystal_I2C lcd(0x27,16,2);

void setup(){
  Serial.begin(9600);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.init();
  lcd.backlight();
}

void loop(){
    int rawData = analogRead(A0);
    float vcc = 3.3; 
    float offset = 3.0;
    float celcius = rawData * (vcc / 1024.0) * 100;

    celcius = celcius-offset;
    Serial.print("Temperature: ");
    lcd.setCursor(0,0);
    lcd.print("Temperature: ");
    
    Serial.print(celcius);
    Serial.println(" *C");
    lcd.setCursor(0,1);
    lcd.print(celcius);
    lcd.print(" ");
    lcd.print(char(223));
    lcd.print("C");

    if(celcius<35){
      digitalWrite(greenLED, 1); 
      digitalWrite(redLED, 0);
      digitalWrite(buzzer, 0); 
    }
    else{
      digitalWrite(greenLED, 0);
      digitalWrite(redLED, 1);
      //call the function for data uploading.
      digitalWrite(buzzer, 1);
      delay(50);
    }   
}
