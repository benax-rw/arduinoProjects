#include<SoftwareSerial.h> //Included SoftwareSerial Library
#include <ESP8266WiFi.h>

WiFiClient wifiClient;

SoftwareSerial serial(3,1); // Rx, Tx respectively

void setup(){
    serial.begin(9600);
    while(!serial){
        ;  //Do nothing
    }

    // SETUP WiFi
     WiFi.begin("dlink-M921-0cd4", "*Talk_le55#");    
}

void loop(){
    readIncomingData();
    delay(10);  //A race condition exists to get the data.  
}

void readIncomingData(){
    int count=0;
    uint8_t buffr[160];

    // reading data into char array
    while(serial.available()){
        buffr[count++]=serial.read();     // writing data into array
        if(count == sizeof(buffr))break;
    }
    
      serial.write(buffr,count);
  
      String mData = serial.readString();
      
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

  //serial.println("Response: " + wifiClient.readStringUntil('\n'));
}
