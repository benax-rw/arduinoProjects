#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

#define MESSAGE_LENGTH 160
#define PIN_TX    10
#define PIN_RX    11

char message[MESSAGE_LENGTH];
int messageIndex = 0;
char phone[16];
char datetime[24];

SoftwareSerial mySerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR

void setup(){
  mySerial.begin(9600);
  Serial.begin(9600);

 /******** Initialize sim808 module *************/
  while(!sim808.checkSIMStatus()) {
      delay(1000);
      Serial.print("SIM Card error\r\n");
  } 

  Serial.println("SIM Card ready."); 
  Serial.println("GSM Started.");
  Serial.println("Waiting for Incoming SMS:");
}

void loop() {
  /*********** Detecting unread SMS ************************/
   messageIndex = sim808.isSMSunread();

   /*********** At least, there is one UNREAD SMS ***********/
   if(messageIndex > 0){ 
      Serial.println("Incoming SMS Detected:");
      sim808.readSMS(messageIndex, message, MESSAGE_LENGTH, phone, datetime);

      Serial.print("From number: ");
      Serial.println(phone);  
      Serial.print("Datetime: ");
      Serial.println(datetime);        
      Serial.print("Received Message: ");
      Serial.println(message); 

      /***********In order not to full SIM Memory, is better to delete it**********/
      sim808.deleteSMS(messageIndex);
   }
}
