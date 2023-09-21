#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

WiFiClient wifiClient;    
const char* host = "iot.benax.rw"; 

void setup(){
  Serial.begin(115200);
  connectToWiFi("Benax Technologies", "ben@kusu");
}

void loop(){
    String mData="";
    mData = ""; //No data to send in this example   
    connectToHost(80);
    makeRequest(mData, "/projects/4e8d42b606f70fa9d39741a93ed0356c/weather-station/data.json");  
    parseResponse();
    delay(10000); //repeat after n seconds
}

/*
 * CONNECT WIFI
*/

void connectToWiFi(const char* ssid, const char* passwd){
  WiFi.mode(WIFI_OFF); //This prevents reconnection issue
  delay(10);
  WiFi.mode(WIFI_STA); //This hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid, passwd); //Connect to your WiFi router
  while(WiFi.status()!= WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  Serial.println();  
}

/*
 * CONNECT TO HOST
*/
void connectToHost(const int httpPort){
  int retry_counter=0; //To be used while retrying to get connected
  wifiClient.setTimeout(15000); // n Seconds
  delay(1000);
  
  while((!wifiClient.connect(host, httpPort)) && (retry_counter <= 30)){
    delay(100);
    Serial.print(".");
    retry_counter++;
  }

  if(retry_counter==31){
    Serial.println("\nConnection failed.");
    return;
  } 
}

/*
 * MAKE AN HTTP REQUEST
*/
void makeRequest(String data, const char* filepath){        
  wifiClient.println("GET "+(String)filepath+"?"+data+" HTTP/1.1");
  wifiClient.println("Host: " +(String)host);
  wifiClient.println("User-Agent: ESP8266/1.0");
  wifiClient.println("Content-Type: application/x-www-form-urlencoded");
  wifiClient.println();
}

/*
 * PARSE THE RESPONSE
*/

void parseResponse(){
      String payload;
      while (wifiClient.connected()){
        String line = wifiClient.readStringUntil('\n');
        if (line == "\r") {
          break;
        }
      }
    
      while (wifiClient.available()){
        payload += wifiClient.readStringUntil('\n');
      }

      DynamicJsonDocument doc(2048);
      deserializeJson(doc, payload);
      JsonObject obj = doc.as<JsonObject>();
      
      int actualDataSize =(obj["data"]).size();
      
      Serial.print("Actual Data Size: ");
      Serial.println(actualDataSize);
      
      for(int k=0; k<actualDataSize; k++){
        String timestamp = obj["data"][k]["timestamp"];

        Serial.println(timestamp);

      }
      delay(3000);
} 
