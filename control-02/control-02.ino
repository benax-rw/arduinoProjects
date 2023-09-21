#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "DS1302.h" 

#define ResetPin 2  
#define DataPin 0  
#define ClockPin 4

#define tvPin 14
 
DS1302 rtc(ResetPin, DataPin, ClockPin);

WiFiClient httpClient;    
void setup(){
    Serial.begin(115200);
    WiFi.begin("dlink-M921-0cd4", "*Talk_le55#"); 
    rtc.writeProtect(false);
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
    
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, response_mesg);
    JsonObject obj = doc.as<JsonObject>();
    int actualDataSize =(obj["data"]).size();
    //Serial.print("Actual Data Size: ");
    //Serial.println(actualDataSize);

    for(int k=0; k<actualDataSize; k++){
      String _id = obj["data"][k]["id"];
      String _time = obj["data"][k]["scheduled_time"];
      String command = obj["data"][k]["scheduled_event"];

      char * now = getRTCTime(); // obtain the time from readtime()
      Serial.println(now); // print the time to the serial monitor

      String day = _time.substring(0,1);
      String hour = _time.substring(13,15);
      String minute = _time.substring(16, 18);
      String second = _time.substring(19, 22);
      int dayInt = day.toInt(); 
      int hourInt = hour.toInt();
      int minInt = minute.toInt();
      int secInt = second.toInt();
  
      /* trigger event based on the input*/
      Time mNow = rtc.time();

      int state = 0;
      if(mNow.day==dayInt && mNow.hr==hourInt && mNow.min==minInt){                
        Serial.println(command);
        if(command.indexOf("turn-on")>0 && state==0){
          digitalWrite(tvPin, HIGH);
          delay(1000);
          state=1;
        }
        else if(command.indexOf("turn-off")>0 && state==1){
          digitalWrite(tvPin, LOW);
          delay(1000);
          state=0;
        }

        String mStatus = "";
        mStatus = "id="+_id;
        httpClient.println("POST /projects/4e8d42b606f70fa9d39741a93ed0356c/control-01/update-status.php HTTP/1.1");
        httpClient.println("Host: iot.benax.rw");
        httpClient.println("User-Agent: ESP8266/1.0");
        httpClient.println("Content-Type: application/x-www-form-urlencoded");
        httpClient.println("Content-Length: " +(String)mStatus.length());
        httpClient.println();
        httpClient.print(mStatus); 
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
