#include<SoftwareSerial.h> //Included SoftwareSerial Library
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define PIN_TX    4
#define PIN_RX    5

SoftwareSerial sim808(PIN_TX,PIN_RX);
HTTPClient httpClient;
WiFiClient wifiClient;
WiFiClientSecure wifiClientSecure;

void setup(){ 
  // SETUP WiFi
  WiFi.begin("dlink-M921-0cd4", "iisvz73994");  
  Serial.begin(9600);
  sim808.begin(9600);
  delay(150);  

  sim808.println("AT\n"); //Once the handshake test is successful, it will back to OK
  sim808.println("AT+CMGF=1\r\n"); // We're expecting a text message
  sim808.println("AT+CNMI=1,2,0,0,0\r\n"); // Decides how newly arrived SMS messages should be handled 
  delay(1000);
}

void loop(){
    //readIncomingData();
    //delay(10);  //A race condition exists to get the data.  
    wifiClientSecure.setInsecure(); //Security is not a concern here.
    httpClient.begin(wifiClientSecure, "https://smser.benax.rw/services/reb/api-test.json");  
    String payload = parseResponse(); 

    DynamicJsonDocument doc(2048);
    deserializeJson(doc, payload);
    JsonObject obj = doc.as<JsonObject>();

    int actualDataSize =(obj["topLevel"]).size();

    for(int k=0; k<actualDataSize; k++){
      String id = obj["topLevel"][k]["id"];
      String recipient = obj["topLevel"][k]["recipient"];
      String SMS = obj["topLevel"][k]["message"];

      sendSMS(recipient, SMS);
    }
}


void readIncomingData(){
    int count=0;
    uint8_t buffr[160];

    // reading data into char array
    while(sim808.available()){
        buffr[count++]=sim808.read();     // writing data into array
        if(count == sizeof(buffr))break;
    }
    
      sim808.write(buffr,count);
  
      String mData = sim808.readString();
      
      if(mData !=""){
        String payload="";
        String device = "node1";
        payload = "device="+device+"&msg="+mData;
        uploadData(80, "insecure.benax.rw", "/post/" , payload);
      }
} 

void uploadData(const int httpPort, const char* host,const char* filepath , String data){
  wifiClient.connect(host, httpPort);
  wifiClient.println("POST "+(String)filepath+" HTTP/1.1");
  wifiClient.println("Host: " + (String)host);
  wifiClient.println("User-Agent: ESP8266/1.0");
  wifiClient.println("Content-Type: application/x-www-form-urlencoded");
  wifiClient.println("Content-Length: " +(String)data.length());
  wifiClient.println();
  wifiClient.print(data);
}

/*
 * PARSE THE RESPONSE
*/

String parseResponse(){
    if(httpClient.GET() == 200){
     return httpClient.getString();
   }

   delay(30000);
}


void sendSMS(String number, String MSG){
  sim808.print("AT+CMGS=\""
  +number+
  "\"\r"); // mobile number to be inserted
  delay(50);

  /********content of the message *******/
  sim808.print(MSG);//Load Message to be sent
  sim808.write(0x1A); // sent message  
  delay(5000);
}
