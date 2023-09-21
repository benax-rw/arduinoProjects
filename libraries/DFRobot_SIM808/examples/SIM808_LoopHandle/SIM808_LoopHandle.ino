#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

#define PIN_TX    10
#define PIN_RX    11
SoftwareSerial mySerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,

//The content of messages sent
#define MESSAGE  "Hi. This is an automatic reply!"
#define MESSAGE_LENGTH 20
char gprsBuffer[64];
char *s = NULL;
char phone[16];
char datetime[24];

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);

 /******** Initialize sim808 module *************/
  while(!sim808.checkSIMStatus()) {
      delay(1000);
      Serial.print("SIM Card error\r\n");
  } 
  Serial.println("SIM Card ready."); 
  Serial.println("GSM Started.");
  Serial.println("Waiting for Incoming Call or SMS:");
}

void loop() {
   /******** Wait for serial data *************/
   if(sim808.readable()){
      sim808_read_buffer(gprsBuffer,32,DEFAULT_TIMEOUT);
      
      if(NULL != strstr(gprsBuffer,"RING")){
        Serial.println("Ringing...");
      }
      else if(NULL != strstr(gprsBuffer,"ATA")){
        Serial.println("Connected.");
      }      
      else if(NULL != strstr(gprsBuffer,"NO CARRIER")){
        Serial.println("Call ended.");
      }
      else if(NULL != strstr(gprsBuffer,"+CMTI: \"SM\"")){
        Serial.println("SMS Received:");  
      }
      else if(NULL != strstr(gprsBuffer,"+CMGS:")){
        Serial.println("Reply Sent.");  
      }      
      else{
        Serial.println(gprsBuffer);  
      }
      
   /************** Detect the current state of the telephone or SMS *********************/
      if(NULL != strstr(gprsBuffer,"RING")){
          sim808.answer();
      }
      else if(NULL != (s = strstr(gprsBuffer,"+CMTI: \"SM\""))){ 
          char message[MESSAGE_LENGTH];
          int messageIndex = atoi(s+12);
          sim808.readSMS(messageIndex, message, MESSAGE_LENGTH, phone, datetime);
                 
          Serial.print("From number: ");
          Serial.println(phone);  
          Serial.print("Datetime: ");
          Serial.println(datetime);        
          Serial.print("Received Message: ");
          Serial.println(message); 

          Serial.println("Auto Replying...");
          sim808.sendSMS(phone,MESSAGE); 
     }
     sim808_clean_buffer(gprsBuffer,32);  
   }
}