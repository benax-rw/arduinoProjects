#include<SoftwareSerial.h> //Included SoftwareSerial Library

#define PIN_TX    4
#define PIN_RX    5

SoftwareSerial sim808(PIN_TX,PIN_RX);

void setup(){ 
  Serial.begin(115200); 
  sim808.begin(9600);
  delay(100); 
  sim808.println("AT\n"); //Once the handshake test is successful, it will back to OK
  sim808.println("AT+CMGF=1\r\n"); // We're expecting a text message
  sim808.println("AT+CNMI=1,2,0,0,0\r\n"); // Decides how newly arrived SMS messages should be handled 
  delay(100);   
}

void loop(){
  readIncomingData(); 
}


void readIncomingData(){
  String mData = "";
  if(sim808.available()>0){
    mData = sim808.readString();
    delay(10);  //A race condition exists to get the data. 
  }

  if(mData.indexOf("+CMT:")>=0 && mData !=""){
    String sender = mData.substring(9, 22); //extract 13 length phone number
    String message = mData.substring(50, mData.length()); 
    mData = ""; //Time to empty mData variable.
    Serial.println(sender);
    Serial.println(message);
    sim808.print("AT+CMGS=\""+sender+"\"\r"); // mobile number to be inserted
    delay(50);
    sim808.print(message);
    sim808.write(0x1A);
    delay(2000);
    
  }
} 
