#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5);

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
}


void loop(){
  RecieveMessage();
 if (mySerial.available()>0)
   Serial.write(mySerial.read());  
}



 void RecieveMessage(){
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }
 
