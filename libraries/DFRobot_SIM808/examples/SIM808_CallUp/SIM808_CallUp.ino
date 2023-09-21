#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

//Mobile phone number,need to change
#define PHONE_NUMBER "0789449645"  


#define PIN_TX    10
#define PIN_RX    11
SoftwareSerial mySerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,

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
  Serial.print("Calling ");
  Serial.println(PHONE_NUMBER);

  //*********Call specified number***************
  sim808.callUp(PHONE_NUMBER);
}
void loop() {
  //nothing to do
}
