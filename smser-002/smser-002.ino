#include <SoftwareSerial.h>
#define PIN_TX    4
#define PIN_RX    5

SoftwareSerial sim808(PIN_TX,PIN_RX);

void setup(){ 
  Serial.begin(115200);
  sim808.begin(9600);
  delay(150);  

  Serial.println("SMSer initializing...");
  sim808.println("AT\n"); //Once the handshake test is successful, it will back to OK
  sim808.println("AT+CMGF=1\r\n"); // We're expecting a text message
  sim808.println("AT+CNMI=1,2,0,0,0\r\n"); // Decides how newly arrived SMS messages should be handled 
  delay(1000);
}

void loop(){
  String in_sms = receiveSMS();
  Serial.print(in_sms);
}

String receiveSMS(){
  String container = "";
  if(sim808.available()){
      char serial_in_char;
      serial_in_char = (unsigned char)sim808.read();
      container = String(container + serial_in_char);  
  }
  return container;
}
