#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

WiFiClient wifiClient;
const char *host = "insecure.benax.rw";

// Timer for Send Data:
unsigned long previousMillis = 0;
const long interval = 30000;//n seconds to repeat the upload

void setup(){
  Serial.begin(115200);
  delay(50);
  connectToWiFi("RCA-WiFi","rca@2019");
}

void loop(){
    String mData="";
    String dummy_device = "Instructor-Device";
    String dummy_distance = "32 cm";   
    uploadData(mData);
    delay(5000);   
  
}

void uploadData(String mData){
  HTTPClient http;

  /*
   * Send HTTP POST Request
   */

  http.begin(wifiClient, "http://insecure.benax.rw/iot/");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(mData);

   /*
   * GET RESPONSE
   */

  if(httpCode==200){ 
  String payload = http.getString();

  Serial.print("............... Http-Code:");
  Serial.println(httpCode);   //Print HTTP return code
  Serial.print("............... Request Response:");
  Serial.println(payload);    //Print request response 
  }

  else{
    Serial.println("No response from server."); 
  }

  http.end();  //Close connection 
}

void connectToWiFi(char *ssid, char *password){
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);
  Serial.println(""); 
  Serial.print("Connecting");
  // Wait for connection ...
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected SSID: ");
  Serial.println(ssid);
  Serial.print("Local-IP: ");
  Serial.println(WiFi.localIP());  

}
