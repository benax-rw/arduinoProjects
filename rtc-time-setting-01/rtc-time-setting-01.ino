#include "DS1302.h"  
#define ResetPin 7  
#define DataPin 6  
#define ClockPin 5 
 
DS1302 rtc(ResetPin, DataPin, ClockPin); //Create a DS1302 object

void setup(){
    Serial.begin(9600); 
    rtc.writeProtect(false); // turn off write protection
    rtc.halt(false); // clear the clock halt flag  
    /*
    rtc.time(t);  is only used to set time. 
    Other times it will be commented out.

    The format for Time t() is t(year,month,date,hour,minutes,seconds,day)
    for example 2022, 11, 1, 9, 3, 30, Time::kTuesday set time as follows
    November 1st, 2022 at 09:03:30
    */
    Time t(2022, 11, 22, 19, 49, 00, Time::kTuesday); 
    rtc.time(t); //use it ONLY to set time. Otherwise, comment it out.                                                                                      
    Serial.println("Ready");
}

void loop(){}
