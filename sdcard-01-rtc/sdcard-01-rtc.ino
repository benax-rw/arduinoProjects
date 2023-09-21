
#include <SPI.h>
#include <SD.h>
#include "DS1302.h" 

#define SD_CHIP_SELECT 4
#define RTC_RST_PIN 7  
#define RTC_DATA_PIN 6  
#define RTC_CLK_PIN 5  
       
File myFile;
DS1302 rtc(RTC_RST_PIN, RTC_DATA_PIN, RTC_CLK_PIN); 

void setup(){
  Serial.begin(9600);                                                                                     
  SPI.begin(); 
  Serial.println("Initializing SD card...");
  if (!SD.begin(SD_CHIP_SELECT)) {
    Serial.println("SD card initialization failed.");
    while (1);
  }
  Serial.println(F("SD card initialized.\n"));  
  Serial.println("Type some text and then hit RETURN Key");                                            
}
void loop(){
  String input = Serial.readStringUntil('\n');
  char * timestamp = readTime();  
  if(input!=""){
    input = String(input+"["+timestamp+"]"); //Appending the timestamp
    
    if(writeToSDCard(input)){
      Serial.println("Text '"+input+"' written.");
    }
    else{
      Serial.println("Text writing failed."); 
    }
  }
}

bool writeToSDCard(String data){
  myFile = SD.open("data.txt", FILE_WRITE);
  if(myFile){
    myFile.println(data);
    myFile.close();
    return true;
  }else{
    Serial.println("error opening data.txt");
    return false;
  }      
 }

 String dayAsString(const Time::Day day){ 
  switch(day){
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

char * readTime(){
  Time t = rtc.time(); 
  const String day = dayAsString(t.day);
  static char CurrentTime[50]; 
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
