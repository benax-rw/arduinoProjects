#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "DS1302.h" 

#define ResetPin 2  
#define DataPin 0  
#define ClockPin 4

#define tvPin 15
 
DS1302 rtc(ResetPin, DataPin, ClockPin);

WiFiClient httpClient;    
void setup(){
    Serial.begin(115200);
    WiFi.begin("HUAWEI-4C9A", "9GR3GEYTETN");  
    rtc.writeProtect(true);
    rtc.halt(false); 
    pinMode(tvPin, OUTPUT);                                                                                    
}
void loop(){
    String payload="";
    String device = "Kigali-Device-001";
    payload = "device="+device;   
    httpClient.connect("iot.benax.rw", 80); 
    httpClient.println("POST /projects/4e8d42b606f70fa9d39741a93ed0356c/control-01/api.php HTTP/1.1");
    httpClient.println("Host: iot.benax.rw");
    httpClient.println("User-Agent: ESP8266/1.0");
    httpClient.println("Content-Type: application/x-www-form-urlencoded");
    httpClient.println("Content-Length: " +(String)payload.length());
    httpClient.println();
    httpClient.print(payload);   
      
    String response_mesg;
    while (httpClient.connected()){
        String line = httpClient.readStringUntil('\n');
        if (line == "\r") {
        break;
        }
    }
    while (httpClient.available()){
      response_mesg += httpClient.readStringUntil('\n');
    }
    
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, response_mesg);
    JsonObject obj = doc.as<JsonObject>();
    
    int actualDataSize =(obj["data"]).size();

    Serial.print("\n***\n"); 

    if(actualDataSize>0){
      for(int k=0; k<actualDataSize; k++){
        String _id = obj["data"][k]["id"];
        String _scheduled_time = obj["data"][k]["scheduled_time"];
        String scheduled_event = obj["data"][k]["scheduled_event"];
  
        if(_scheduled_time!="null"){
          String day = _scheduled_time.substring(0,1);
          String hour = _scheduled_time.substring(13,15);
          String minute = _scheduled_time.substring(16, 18);
          String second = _scheduled_time.substring(19, 22);
          int _scheduled_day = day.toInt(); 
          int _scheduled_hour = hour.toInt();
          int _scheduled_min = minute.toInt();
          int _scheduled_sec = second.toInt();
    
          Time mNow = rtc.time();
          String current_RTC_time="";
          current_RTC_time = (String)mNow.day+
    
          " "+(String)mNow.mon+
          "/"+(String)mNow.date+
          "/"+(String)mNow.yr+ 
          " "+(String)mNow.hr+
          ":"+(String)mNow.min+
          ":"+(String)mNow.sec; 
          
          Serial.print(current_RTC_time);
          Serial.print(": Next event '");
          Serial.print(scheduled_event);
          Serial.print("' will be triggered at ");
          Serial.println(_scheduled_time);
    
          if(mNow.day==_scheduled_day && mNow.hr==_scheduled_hour && mNow.min==_scheduled_min){
              Serial.print("The time has come!");
              if(scheduled_event=="turn-on-the-tv"){
                Serial.print("Turn on the TV!"); 
                digitalWrite(tvPin, HIGH); 
              }
              else if(scheduled_event=="turn-off-the-tv"){
                Serial.print("Turn off the TV!"); 
                digitalWrite(tvPin, LOW);
                String status = "";
                status = "id="+_id;
                httpClient.println("POST /projects/4e8d42b606f70fa9d39741a93ed0356c/control-01/update-status.php HTTP/1.1");
                httpClient.println("Host: iot.benax.rw");
                httpClient.println("User-Agent: ESP8266/1.0");
                httpClient.println("Content-Type: application/x-www-form-urlencoded");
                httpClient.println("Content-Length: " +(String)status.length());
                httpClient.println();
                httpClient.print(status);                 
              }            
          }
        }
      }
    }
    
    delay(15000);  
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
