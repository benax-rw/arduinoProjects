#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>

#define PIN_TX    4
#define PIN_RX    5

WiFiClientSecure wifiClient;
SoftwareSerial sim808(PIN_TX,PIN_RX);

const char *host = "smser.benax.rw";


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Serial Interface Ready!");

  // set the data rate for the SoftwareSerial port
  sim808.begin(9600);

  connectToWiFi("dlink-M921-0cd4", "iisvz73994");
  sim808.println("AT"); //Once the handshake test is successful, it will back to OK 

  delay(150);
}

void loop(){
  String in_sms = receiveSMS();
    //uploadData("Sender", in_sms);
    Serial.println(in_sms);
    delay(1000);
}

String receiveSMS(){
  String mData;
  if(sim808.available()){
    mData = sim808.readString();
    char Buf[mData.length()+1];
    mData.toCharArray(Buf, mData.length()+1); 
  }
  return mData; 
}

void uploadData(String sender, String msg){
  HTTPClient http;
  String pass, postData;
  postData = "sender=" + sender + "&SMS=" + msg;


  /*
   * Send HTTP POST Request
   */
  wifiClient.setInsecure(); //Security is not a concern here.
  http.begin(wifiClient, "https://smser.benax.rw/handleIncomingSMS.php");
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
