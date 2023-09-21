#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN         
const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
int button_pin = 2;
boolean button_state = 0;

void setup(){
  Serial.begin(9600);
  pinMode(button_pin, INPUT);
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
}

void loop(){
   String mData = Serial.readStringUntil('\n');
   char text[mData.length()+1];
   mData.toCharArray(text, mData.length()+1);

  if(mData.length()>0){
    radio.write(&text, sizeof(text)); 
  }
}
