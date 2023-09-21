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
    char * now = getRTCTime(); // obtain the time from readtime()
    Serial.println(now); // print the time to the serial monitor
    /*
     * Keep in Mind that Day 1 is Sunday and Day 7 is Saturday
     * Sunday=1
     * Monday=2
     * Tuesday=3
     * Wednesday=4
     * Thursday=5
     * Friday=6
     * Saturday=7
     */
    String schedule1 = "3 11/22/2022 22:38:00"; 
    String schedule2 = "3 11/22/2022 22:39:00";
    triggerEvent(schedule1,playBuzzer); 
    triggerEvent(schedule2,switchOFFBuzzer);
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
  return "(Unknown Day)";
}

/*
function that reads the time from the chip and returns it in a character array
*/

char * getRTCTime(){
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

template <typename T>
void triggerEvent(String input, T const & event){
    /* parse the input*/
    String day = input.substring(0,1);
    String hour = input.substring(13,15);
    String minute = input.substring(16, 18);
    String second = input.substring(19, 22);
    int dayInt = day.toInt(); 
    int hourInt = hour.toInt();
    int minInt = minute.toInt();
    int secInt = second.toInt();
    
    /* trigger event based on the input*/
    Time mNow = rtc.time();
    
    if(mNow.day==dayInt && mNow.hr==hourInt && mNow.min==minInt && mNow.sec==secInt){
        event();
    }
}

void playBuzzer(){
    Serial.println("Buzzer ON");
}

void switchOFFBuzzer(){
    Serial.println("Buzzer OFF");
}
