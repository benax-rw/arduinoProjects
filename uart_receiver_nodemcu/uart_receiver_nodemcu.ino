#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started SoftwareSerial at RX and TX pin of ESP8266/NodeMCU
SoftwareSerial serial(3,1);

 char data; //Initialized variable to store recieved data
 String line;
 void setup() {
   serial.begin(9600);
   while (!serial) {
    ; 
  }
}

void loop() {

    if(serial.available()>=2) {
        for (int i = 0; i< 50; i++ ) {
            data = serial.read();
            line += data;
        }
    }


    serial.println(line);
    delay(5000);

}
