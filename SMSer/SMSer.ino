#include <SoftwareSerial.h>
#define PIN_TX    4
#define PIN_RX    5

SoftwareSerial sim808(PIN_TX,PIN_RX);

String container;
char serial_in_char;
  
void setup(){ 
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Serial initialized.");
  sim808.begin(9600);

  sim808.println("AT\n"); //Once the handshake test is successful, it will back to OK
  sim808.println("AT+CMGF=1\r\n"); // We're expecting a text message
  sim808.println("AT+CNMI=1,2,0,0,0\r\n"); // Decides how newly arrived SMS messages should be handled 
  delay(1000);
}

void loop(){
  String in_sms = receiveSMS();
  Serial.println(in_sms);
  delay(1000);
}

String receiveSMS(){
  if(sim808.available()){
      serial_in_char = (unsigned char)sim808.read();
      container = String(container + serial_in_char); 
  }
  return container;
}
