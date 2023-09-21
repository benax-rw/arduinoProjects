//MORY ARDUINO AND TECH
//Audio Player using Arduino with micro SD card 

#include <SD.h>     //include SD module library
#include <TMRpcm.h> //include speaker control library

#define SD_ChipSelectPin 10   //define CS pin

TMRpcm tmrpcm;   //create an object for speaker library

void setup(){
  Serial.begin(9600);
  tmrpcm.speakerPin = 9;  //define speaker pin. 
  //you must use pin 9 of the Arduino Uno and Nano
  //the library is using this pin
  Serial.println("speakerPin"); 
 //see if the card is present and can be initialized
  if (!SD.begin(SD_ChipSelectPin)) { 
    //don't do anything more if not
    Serial.println("initialized"); 
    return; 
  }
  Serial.println("setVolume"); 
  //0 to 7. Set volume level
  tmrpcm.setVolume(6);
  Serial.println("Play"); 
  tmrpcm.play("music.wav");         
  Serial.println("Don"); 
}

void loop(){}
