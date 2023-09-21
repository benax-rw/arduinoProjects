#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#define tvPin 15
WiFiClient httpClient;    
void setup(){
    Serial.begin(115200);
    WiFi.begin("dlink-M921-0cd4", "*Talk_le55#"); 
    pinMode(tvPin, OUTPUT);                                                                                    
}
void loop(){
    String payload="";
    String device = "Kigali-Device-001";
    payload = "device="+device;   
    httpClient.connect("192.168.0.104", 80); 
    
    httpClient.println("POST /control-01/api.php HTTP/1.1");
    httpClient.println("Host: 192.168.0.104");
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
        String event_closing_time = obj["data"][k]["event_closing_time"];
        String now = obj["data"][k]["now"];
  
        if(_scheduled_time!="null"){
          String day = _scheduled_time.substring(0,1);
          String year = _scheduled_time.substring(2,6);
          String month = _scheduled_time.substring(7,9);
          String date = _scheduled_time.substring(10,12);
          String hour = _scheduled_time.substring(13,15);
          String minute = _scheduled_time.substring(16, 18);
          String second = _scheduled_time.substring(19, 22);
          int _scheduled_day = day.toInt();
          int _scheduled_year = year.toInt();
          int _scheduled_month = month.toInt();
          int _scheduled_date = date.toInt();
          int _scheduled_hour = hour.toInt();
          int _scheduled_min = minute.toInt();
          int _scheduled_sec = second.toInt();

          String now_day = now.substring(0,1);
          String now_year = now.substring(2,6);
          String now_month = now.substring(7,9);
          String now_date = now.substring(10,12);          
          String now_hour = now.substring(13,15);
          String now_minute = now.substring(16, 18);
          String now_second = now.substring(19, 22);
          int _now_day = now_day.toInt();
          int _now_year = now_year.toInt();
          int _now_month = now_month.toInt();
          int _now_date = now_date.toInt();
          int _now_hour = now_hour.toInt();
          int _now_min = now_minute.toInt();
          int _now_sec = now_second.toInt();

          String closing_day = event_closing_time.substring(0,1);
          String closing_year = event_closing_time.substring(2,6);
          String closing_month = event_closing_time.substring(7,9);
          String closing_date = event_closing_time.substring(10,12);          
          String closing_hour = event_closing_time.substring(13,15);
          String closing_minute = event_closing_time.substring(16, 18);
          String closing_second = event_closing_time.substring(19, 22);
          int _closing_day = closing_day.toInt();
          int _closing_year = closing_year.toInt();
          int _closing_month = closing_month.toInt();
          int _closing_date = closing_date.toInt();
          int _closing_hour = closing_hour.toInt();
          int _closing_min = closing_minute.toInt();
          int _closing_sec = closing_second.toInt();
          
          String current_RTC_time="";
          current_RTC_time = now_day+
          " "+now_year+
          ":"+now_month+
          ":"+now_date+
          " "+now_hour+
          ":"+now_minute+
          ":"+now_second; 
          
          Serial.print(current_RTC_time);
          Serial.print(": Current Event '");
          Serial.print(scheduled_event);
          Serial.print("' is triggered at ");
          Serial.println(_scheduled_time);

          if(scheduled_event=="turn-on-the-tv"){
            if(
              _now_day>=_scheduled_day &&
              _now_year>=_scheduled_year &&
              _now_month>=_scheduled_month &&
              _now_date>=_scheduled_date && 
              _now_hour>=_scheduled_hour && 
              _now_min>=_scheduled_min
           
              ){
                Serial.print("The time has come!");
                Serial.print("Turn on the TV!"); 
                digitalWrite(tvPin, HIGH); 
            }//ending TV switching ON
            
            if(
              _now_day>=_closing_day &&
              _now_year>=_closing_year &&
              _now_month>=_closing_month &&
              _now_date>=_closing_date && 
              _now_hour>=_closing_hour && 
              _now_min>=_closing_min           
              ){
              Serial.print("Turn off the TV!"); 
              digitalWrite(tvPin, LOW);
              String status = "";
              status = "id="+_id;
              /*
               For the LAN web server on the Raspberry Pi, 
               we needed to run the following line to reconnect the client to the server.
               */
              httpClient.connect("192.168.0.104", 80);
    
              /*
               Then HTTP request restarted.
               */
              httpClient.println("POST /control-01/update-status.php HTTP/1.1");
              httpClient.println("Host: 192.168.0.104");
              httpClient.println("User-Agent: ESP8266/1.0");
              httpClient.println("Content-Type: application/x-www-form-urlencoded");
              httpClient.println("Content-Length: " +(String)status.length());
              httpClient.println();
              httpClient.print(status);             
            } //ending TV switching OFF
          } //ending TV switching
        }
      }
    }
    
    delay(5000);  
}
