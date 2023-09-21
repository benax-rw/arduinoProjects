#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

WiFiClient httpClient;    
void setup(){
    Serial.begin(115200);
    WiFi.begin("dlink-M921-0cd4", "*Talk_le55#");                                                                                       
}
void loop( ){
    String payload="";
    String device = "Kigali-Device-001";
    payload = "device="+device;   
    httpClient.connect("iot.benax.rw", 80); 
    httpClient.println("POST /projects/4e8d42b606f70fa9d39741a93ed0356c/control/api.json HTTP/1.1");
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
    Serial.print("Actual Data Size: ");
    Serial.println(actualDataSize);

    for(int k=0; k<actualDataSize; k++){
      String _time = obj["data"][k]["time"];
      String command = obj["data"][k]["command"];

      Serial.print("Time: ");
      Serial.println(_time);
      Serial.print("Command: ");
      Serial.println(command); 
      Serial.print("**************************\n");  
    }
    
    delay(15000);  
}
