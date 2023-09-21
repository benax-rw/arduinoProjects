#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#define relayPin 13 //D7
#define ldr A0 //A0

WiFiClient httpClient;    
void setup(){
    Serial.begin(115200);
    WiFi.begin("RCA", "@RcaNyabihu2023"); 
    pinMode(relayPin, OUTPUT); 
    pinMode(ldr, INPUT);
    Serial.println("Ready!");                                                                                  
}
void loop(){
    int ldr_value = 0;
    ldr_value = analogRead(ldr); 
    Serial.println(ldr_value);
    String payload="";
    String device = "Benax-001";
    String state;

    Serial.println(F("***"));
    
    if(ldr_value<500){
      //light is ON
      state = "1"; 
      Serial.println(F("Light is ON")); 
    }
    else{
      //light is OFF
      state = "0"; 
      Serial.println(F("Light is OFF")); 
    }
    
    payload = "device="+device+"&status="+state+"&action=request-command";   
    httpClient.connect("iot.benax.rw", 80); 
    
    httpClient.println("POST /projects/4e8d42b606f70fa9d39741a93ed0356c/over-the-internet-light-switching/api.php HTTP/1.1");
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

    /*
    Json Buffer allocation: arduinojson assistant helps us to to compute the capacity
    */
    const size_t capacity = JSON_OBJECT_SIZE(2) + JSON_ARRAY_SIZE(1) + 16;
    DynamicJsonDocument jsonBuffer(capacity);
    DeserializationError error = deserializeJson(jsonBuffer, response_mesg);
    if (error){
      Serial.print(F("Error: "));
      Serial.println(error.f_str());
      return;
    }   
    JsonObject obj = jsonBuffer.as<JsonObject>();
   
    String command = obj["command"].as<String>();
 
    Serial.println(F("***")); 

    if(command=="1"){
        digitalWrite(relayPin, LOW);
        Serial.println("Let it be ON");
    }          
    else if(command=="0"){
        digitalWrite(relayPin, HIGH);
        Serial.println("Let it be OFF");         
    }         

    delay(5000);  
} 
