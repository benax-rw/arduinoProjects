#include<SoftwareSerial.h> //Included SoftwareSerial Library
#include <ESP8266WiFi.h>

WiFiClient wifiClient;
#define PIN_TX    4
#define PIN_RX    5

SoftwareSerial sim808(PIN_TX,PIN_RX);

void setup(){ 
  // SETUP WiFi
  WiFi.begin("dlink-M921-0cd4", "iisvz73994");  
  sim808.begin(9600);
  delay(100); 
  sim808.println("AT\n"); //Once the handshake test is successful, it will back to OK
  sim808.println("AT+CMGF=1\r\n"); // We're expecting a text message
  sim808.println("AT+CNMI=1,2,0,0,0\r\n"); // Decides how newly arrived SMS messages should be handled 
  delay(100);   
}

void loop(){
  handleIncomingData(); 
}


void handleIncomingData(){
  String mData = "";
  if(sim808.available()>0){
    mData = sim808.readString();
    delay(10);  //A race condition exists to get the data. 
  }

  if(mData.indexOf("+CMT:")>=0 && mData !=""){
    String payload="";
    String device = "node1";
    payload = "device="+device+"&msg="+mData;
    uploadData(80, "insecure.benax.rw", "/post/" , payload);
    
    int index = mData.indexOf(","); //Get to the first comma from left
    String number = mData.substring(9, index-1); //extract the number
    mData = "";
    
    sim808.print("AT+CMGS=\""+number+"\"\r"); // mobile number to be inserted
    delay(50);
    sim808.print("Your request has been accepted.");
    sim808.write(0x1A);
    delay(1000);
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

  //serial.println("Response: " + wifiClient.readStringUntil('\n'));
}
