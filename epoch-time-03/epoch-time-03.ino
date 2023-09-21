#include "DS1302.h" 
#include "TimeLib.h"

#define relayPin 14
#define buzzerPin 4

#define ResetPin 15
#define DataPin 13 
#define ClockPin 12
 
DS1302 rtc(ResetPin, DataPin, ClockPin); // create a DS1302 object

void setup(){
    Serial.begin(9600); // initialise the serial connection
    pinMode(relayPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    rtc.writeProtect(false); // turn off write protection
    rtc.halt(false); // clear the clock halt flag
}

int state = 0;
void loop(){
  char * current_timestamp_char = getCurrentTime(); // obtain the time from readtime()
  /*
   * Convert char to str
   */
  String current_timestamp_str;
  current_timestamp_str = String(current_timestamp_str + current_timestamp_char); 

  Serial.println(current_timestamp_str);
  time_t current_timestamp_epoch = strtotime(current_timestamp_str);

  String event_start_time = "2023-01-01 16:10:00";
  time_t event_start_time_epoch = strtotime(event_start_time);
  
  String event_stop_time = "2023-01-01 16:15:00";
  time_t event_stop_time_epoch = strtotime(event_stop_time);
 
  if(current_timestamp_epoch > event_start_time_epoch && current_timestamp_epoch < event_stop_time_epoch){
      if(state==0){
        for(int k=1; k<=20; k++){
          digitalWrite(buzzerPin, HIGH); //buzzer on
          delay(50);
          digitalWrite(buzzerPin, LOW); //buzzer off
          delay(50);
        }
      }
      
      digitalWrite(relayPin, HIGH); //on
      state = 1;
  }
  else{
    digitalWrite(relayPin, LOW); //off
    state = 0;
  }
   
  delay(5000);
}

int strtotime(String timestamp){
  String year_str = timestamp.substring(0,4);
  String month_str = timestamp.substring(5,7);
  String date_str = timestamp.substring(8,10);
  String hour_str = timestamp.substring(11,13);
  String minute_str = timestamp.substring(14,16);
  String second_str = timestamp.substring(17,19);
  int year_int = year_str.toInt();
  int month_int = month_str.toInt();
  int date_int = date_str.toInt();
  int hour_int = hour_str.toInt();
  int min_int = minute_str.toInt();
  int sec_int = second_str.toInt();
  
  tmElements_t my_time;  // time elements structure
  my_time.Second = sec_int;
  my_time.Hour = hour_int;
  my_time.Minute = min_int;
  my_time.Day = date_int;
  my_time.Month = month_int - 0;  // months counted starting from 0
  my_time.Year = year_int - 1970; // years since 1970, so deduct 1970
  return makeTime(my_time);
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

char * getCurrentTime(){
    Time t = rtc.time(); // get the time and date from the chip.
    static char CurrentTime[50]; // initialise a character array to hold the date text
    snprintf(
        CurrentTime, 
        sizeof(CurrentTime), 
        "%04d-%02d-%02d %02d:%02d:%02d", 
        t.yr, 
        t.mon, 
        t.date, 
        t.hr, 
        t.min, 
        t.sec
    ); // format the time into the character array
    return CurrentTime; // return the current time
}
