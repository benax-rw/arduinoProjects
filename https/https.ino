#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
WiFiClientSecure wifiClientSec; 
#define LED_PIN 13 //D7 
const char* host = "projects.benax.rw"; //domain or subdomain of your website
void setup(){
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200); //Start Serial Monitor with the baud rate 115200
  connectToWiFi("dlink-M921-0cd4", "*Talk_le55#");                                            
}
void loop(){
    String field1 = "Bright";
    String field2 = "5000";
    String field3 = "500";
    String mData="";
    mData = "field1="+field1+"&field2="+field2+"&field3="+field3;    
    transferData(mData, "/f/o/r/e/a/c/h/p/r/o/j/e/c/t/s/4e8d42b606f70fa9d39741a93ed0356c/iot/api.php");  
}
void connectToWiFi(const char* ssid, const char* passwd){
  WiFi.mode(WIFI_OFF); //This prevents reconnection issue
  delay(10);
  WiFi.mode(WIFI_STA); //This hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid, passwd); //Connect to your WiFi router
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  Serial.println();  
}
void connectToHost(const char sha1_fingerprint[], const int httpsPort){
  int retry_counter=0; //To be used while retrying to get connected
  //SHA-1 fingerprint
  wifiClientSec.setFingerprint(sha1_fingerprint);
  wifiClientSec.setTimeout(15000); // 15 Seconds
  delay(1000);
  Serial.printf("Connecting to \"%s\"\n", host);
  //Serial.printf("Fingerprint \"%s\"\n", fingerprint);
  while((!wifiClientSec.connect(host, httpsPort)) && (retry_counter <= 30)){
    delay(100);
    Serial.print(".");
    retry_counter++;
  }
  if(retry_counter==31){
    Serial.println("\nConnection failed.");
    return;
  }
  else{
    Serial.printf("Connected to \"%s\"\n", host);
  }   
}
void transferData(String data, const char* filepath){
    connectToHost("2F BB 86 97 4B 48 19 18 FE 61 37 18 37 BB 6B F4 95 69 FB 0B", 443);
    Serial.println("Transferring data... ");
    wifiClientSec.println("POST "+(String)filepath+" HTTP/1.1");
    wifiClientSec.println("Host: " + (String)host);
    wifiClientSec.println("User-Agent: ESP8266/1.0");
    wifiClientSec.println("Content-Type: application/x-www-form-urlencoded");
    wifiClientSec.println("Content-Length: " +(String)data.length());
    wifiClientSec.println();
    wifiClientSec.print(data); 
    getResponse("Success");
}
/*
 * GET Response
*/
void getResponse(String success_msg){
    String datarx;
    while (wifiClientSec.connected()){
        String line = wifiClientSec.readStringUntil('\n');
        if (line == "\r") {
            break;
        }   
    }
    while (wifiClientSec.available()){
        datarx += wifiClientSec.readStringUntil('\n');
    }
    if(datarx.indexOf(success_msg) >= 0){
        Serial.println("Data Transferred.\n");
        for(int k=10; k>=0; k--){
          digitalWrite(LED_PIN, HIGH);
          delay(50);
          digitalWrite(LED_PIN, LOW);
          delay(50);
        }
    }
    else{
        Serial.println("Data Transfer Failed.\n"); 
    }
    datarx = "";  
}
