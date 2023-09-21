/* HC-05 interfacing with NodeMCU ESP8266

    Author: Circuit Digest(circuitdigest.com)

*/
#include <SoftwareSerial.h>
SoftwareSerial btSerial(5, 4); // Rx,Tx
int led = 15;   // led also the internal led of NodemCU
int ledState = LOW;   // led state to toggle
String ledB = "";
unsigned long previousMillis = 0;  // millis instead of delay
const long interval = 500;  // blink after ecery 500ms
void setup() {
  delay(1000);
  Serial.begin(9600);     
  btSerial.begin(9600);     // bluetooth module baudrate 
  pinMode(led, OUTPUT);
  Serial.println("Started...");
}

void loop(){
  if (btSerial.available() > 0) {    // check if bluetooth module sends some data to esp8266
    char data = btSerial.read();  // read the data from HC-05
    switch (data){
      case 'B':         // if receive data is 'B'
        ledB = "blink";   // write the string
        break;
      case 'S':              // if receive data is 'S'
        ledB = "stop";
        break;
      default:
        break;
    }
  }
  
  unsigned long currentMillis = millis();
  if (ledB == "blink") {          // if received data is 'B' the start blinking 
    Serial.println("blinking started");
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(led, ledState);
    }
  }
}
