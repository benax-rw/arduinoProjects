#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define PIN_TX    4
#define PIN_RX    5

SoftwareSerial sim808(PIN_TX,PIN_RX);
HTTPClient httpClient; 
WiFiClientSecure wifiClient;

const char* SSID0 = "benax-iot-2";
const char* key0 = "Ben@ks10++";

const char* SSID1 = "RCA-WiFi";
const char* key1 = "rca@2019";

const char* SSID2 = "RCA-WiFii";
const char* key2 = "@rca@2023";

const char* SSID3 = "RCA";
const char* key3 = "@RcaNyabihu2023";

const char* SSID4 = "Benax-WiFi(2.4G)";
const char* key4 = "Rc@Nyabihu2023";

const char* SSID5 = "HUAWEI-4C9A";
const char* key5 = "9GR3GEYTETN";

const char* SSID6 = "dlink-M921-0cd4";
const char* key6 = "*Talk_le55#";

void setup(){ 
  Serial.begin(115200);
  sim808.begin(9600);
  delay(150);  
  WiFi.mode(WIFI_STA);
  connectToWiFi();
}

void loop(){
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Connection lost. Attempting to reconnect...");
      connectToWiFi();
    }  
    wifiClient.setInsecure(); //Security is not a concern here.
    httpClient.begin(wifiClient, "https://smser.benax.rw/services/nesa/api.php");  
    parseResponse();
    delay(3000); //Repeat after n seconds
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

void connectToWiFi() {
  Serial.println("Scanning for available Wi-Fi networks...");
  int scanResults = WiFi.scanNetworks();
  if (scanResults == 0) {
    Serial.println("No Wi-Fi networks found.");
    return;
  }
  for (int i = 0; i < scanResults; i++) {
    String ssid = WiFi.SSID(i);
    
    if (ssid.equals(SSID0)){
      WiFi.begin(ssid.c_str(), key0);
      delay(5000);
      if (WiFi.status() == WL_CONNECTED) {
        return;
      }
    }
  }

  WiFi.begin(SSID1, key1);
  delay(5000);
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }
  
  WiFi.begin(SSID2, key2);
  delay(5000);
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  WiFi.begin(SSID3, key3);
  delay(5000);
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  WiFi.begin(SSID4, key4);
  delay(5000);
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  WiFi.begin(SSID5, key5);
  delay(5000);
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  WiFi.begin(SSID6, key6);
  delay(5000);
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }
  
  Serial.println("Failed to connect to Wi-Fi network.");
}

/*
 * PARSE THE RESPONSE
*/
void parseResponse(){
    if(httpClient.GET() == 200){
      String payload = httpClient.getString();
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, payload);
      JsonObject obj = doc.as<JsonObject>();
      
      int actualDataSize =(obj["topLevel"]).size();
      
      //Serial.print("Actual Data Size: ");
      //Serial.println(actualDataSize);
      
      for(int k=0; k<actualDataSize; k++){
        String id = obj["topLevel"][k]["myid"];
        String recipient = obj["topLevel"][k]["recipient"];
        String SMS = obj["topLevel"][k]["message"];

        if(recipient!="null"){
          Serial.print("ID: ");
          Serial.println(id);
          Serial.print("Recipient: ");
          Serial.println(recipient);
          Serial.print("SMS: ");
          Serial.println(SMS);  
          Serial.print("\n**************************\n");  
  
          sendSMS(recipient, SMS);
        }
      }
   }
   else{
    Serial.println("No response received from the host!");
   }
}

void sendSMS(String number, String MSG){
  sim808.print("AT+CMGF=1\r"); //text message format
  delay(50);
  sim808.print("AT+CMGS=\""
  +number+
  "\"\r"); // mobile number to be inserted
  delay(50);

  /********content of the message *******/
  sim808.print(MSG);//Load Message to be sent
  sim808.write(0x1A); // sent message  
  delay(5000);
}
