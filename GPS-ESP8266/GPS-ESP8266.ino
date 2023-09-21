#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <SoftwareSerial.h>

#include <TinyGPS++.h>
WiFiClient wifiClient;
SoftwareSerial sim808(4,5); //TX, RX
TinyGPSPlus gps;

float longitude, latitude;
const char *host = "insecure.benax.rw";

// Timer for Send Data:
unsigned long previousMillis = 0;
const long interval = 30000;//n seconds to repeat the upload

void setup(){
  sim808.begin(9600);  
  Serial.begin(115200);
  delay(50);
  connectToWiFi("RCA-WiFi","rca@2019");
}

void loop(){
 
 while (sim808.available() > 0){
  Serial.println("GPS is available");
   gps.encode(sim808.read()) ; // read gps
   if(gps.location.isUpdated()){
     latitude = gps.location.lat() ;
     longitude = gps.location.lng() ;

     unsigned long currentMillis = millis();
     if(currentMillis - previousMillis >= interval){
      previousMillis = currentMillis;
      uploadData(String(latitude,6), String(longitude,6));
    }
   }
 }
}

void uploadData(String mLat, String mLong){
  HTTPClient http;
  String pass, postData;
  pass = "sudo123!";//for accept POST on gps.php on server
  postData = "lat=" + mLat + "&lng=" + mLong +"&pass=" + pass ;


  /*
   * Send HTTP POST Request
   */

  http.begin(wifiClient, "http://insecure.benax.rw/gps/gps.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(postData);

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
