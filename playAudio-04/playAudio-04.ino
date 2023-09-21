#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>

#define SD_ChipSelectPin 4 //defines the digital pin used by CS terminal of BT module

TMRpcm tmrpcm; //creates an object to the speaker library

const int checkEvery = 22000; //loop interval in miliseconds
const int shadowThreshold = 500; //threshold to the foto resistor that will define if the cellphone is in or out the box


void setup() {
 tmrpcm.speakerPin = 9; //defining the speaker pin (it must be 9 in arduino uno)
 tmrpcm.setVolume(5); //defining the volume (1 a 7)
 pinMode(SS, OUTPUT);

 Serial.begin(9600);
 if(!SD.begin(SD_ChipSelectPin)) { //if the microSD can't be read
 return; //do nothing
 }
}

void loop() {
 checkCel(shadowThreshold); 
 delay(checkEvery);
}

void checkCel(int shadowLevelLimit){
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

 if(sensorValue > shadowLevelLimit){ //if there's a low amount of light
  if(tmrpcm.isPlaying()){ //if the audio file is being played
    tmrpcm.disable(); //stops the sound
  }
 }else{ //if there's a hight amount of incoming light
 tmrpcm.play("music.wav"); //play audio file
}
  
}
