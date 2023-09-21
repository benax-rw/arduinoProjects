#include <SoftwareSerial.h>
SoftwareSerial btSerial(5, 4); // D1 (GPIO5) is used as Rx while D2 (GPIO4) is used as Tx
int led = 15;   // led also the internal led of NodemCU
int ledState = LOW;   // led state to toggle
String ledB = "";

void setup() {
  delay(1000);
  Serial.begin(9600);     
  btSerial.begin(9600);     // bluetooth module baudrate 
  pinMode(led, OUTPUT);
  Serial.println("Started...");
}

void loop(){
  if (btSerial.available() > 0) {    // check if bluetooth module sends some data to esp8266
    String data = btSerial.readString();  // read the data from HC-05

    if(data.startsWith("lock")){
      ledB = "ON";
    }
    else if(data.startsWith("unlock")){
      ledB = "OFF";
    }
    
  }
  
  if(ledB == "ON") {          // if received data is 'n' the LED turns ON 
    Serial.println("turning ON");
    digitalWrite(led, HIGH);
  }
  else if(ledB == "OFF") {          // if received data is 'f' the LED turns ON 
    Serial.println("turning OFF");
    digitalWrite(led, LOW);
  } 
}
