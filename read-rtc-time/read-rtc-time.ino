#include "DS1302.h" 
const int ResetPin = 7;  
const int DataPin = 6;  
const int ClockPin = 5; 
 
DS1302 rtc(ResetPin, DataPin, ClockPin); // create a DS1302 object

void setup(){
    Serial.begin(9600); // initialise the serial connection
    rtc.writeProtect(false); // turn off write protection
    rtc.halt(false); // clear the clock halt flag
}
 
// Loop and print the time every second.
void loop(){
    char * timearray = readTime(); // obtain the time from readtime()
    Serial.println(timearray); // print the time to the serial monitor
    delay(1000); // pause before looping
}

String dayAsString(const Time::Day day) { // function that converts the day ouptput into a string
  switch (day) {
    case Time::kSunday: return "Sunday";
    case Time::kMonday: return "Monday";
    case Time::kTuesday: return "Tuesday";
    case Time::kWednesday: return "Wednesday";
    case Time::kThursday: return "Thursday";
    case Time::kFriday: return "Friday";
    case Time::kSaturday: return "Saturday";
  }
  return "(unknown day)";
}

/*
function that reads the time from the chip and returns it in a character array
*/

char * readTime(){
    Time t = rtc.time(); // get the time and date from the chip.
    const String day = dayAsString(t.day); // obtain text for the day of the week
    static char CurrentTime[50]; // initialise a character array to hold the date text
    snprintf(
        CurrentTime, 
        sizeof(CurrentTime), 
        "%s %04d-%02d-%02d %02d:%02d:%02d", 
        day.c_str(), 
        t.yr, 
        t.mon, 
        t.date, 
        t.hr, 
        t.min, 
        t.sec
    ); // format the time into the character array
    return CurrentTime; // return the current time
}
