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
    httpClient.connect("192.168.0.100", 80); 
    
    httpClient.println("POST /tv-control/api.php HTTP/1.1");
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

    /*
    Json Buffer allocation: arduinojson assistant helps us to to compute the capacity
    */
    const size_t capacity = JSON_OBJECT_SIZE(2) + JSON_ARRAY_SIZE(1) + 16;
    DynamicJsonDocument jsonBuffer(capacity);
    DeserializationError error = deserializeJson(jsonBuffer, response_mesg);
    if (error) {
      Serial.print(F("Error: "));
      Serial.println(error.f_str());
      return;
    }   
    JsonObject obj = jsonBuffer.as<JsonObject>();
    
    String target = obj["target"].as<String>();
    String mode = obj["mode"].as<String>();
 
    Serial.println(F("***")); 

    if(target!="null"){
        if(mode=="on"){
            Serial.println(mode);
            digitalWrite(tvPin, HIGH); 
        }          
        else if(mode=="off"){
            Serial.println(mode);
            digitalWrite(tvPin, LOW);           
        }         
    }
    else{
      Serial.println(F("No data"));
    }
    delay(5000);  
} 
