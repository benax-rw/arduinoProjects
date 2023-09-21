#include "LiquidCrystal_I2C.h";
#include "Wire.h";

LiquidCrystal_I2C lcd(0x27, 20, 4);
char buff[50];
volatile byte indx;

void setup(){
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void loop(){
    if(Serial.available() > 0){
        byte c = Serial.read();
        if(indx < sizeof(buff)){
            buff[indx++] = c; // save data in the next index in the array buff
            if(c == '\r'){ //check for the end of the word
                lcd.print(buff);
                delay(1000);
                indx = 0; //reset button to zero
                lcd.clear();
            }
        }
    }
}
