#include "TimeLib.h"

tmElements_t my_time;  // time elements structure
time_t unix_timestamp; // a timestamp

void setup() {
  Serial.begin(9600);
}

void loop(){
  unix_timestamp = getEpochTime("2022-12-31 18:53:00");
  Serial.println(unix_timestamp);
  delay(5000);
}

int getEpochTime(String timestamp){
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
  my_time.Second = sec_int;
  my_time.Hour = hour_int;
  my_time.Minute = min_int;
  my_time.Day = date_int;
  my_time.Month = month_int - 0;  // months counted starting from 0
  my_time.Year = year_int - 1970; // years since 1970, so deduct 1970
  return makeTime(my_time);
}
