#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>

#define SD_ChipSelectPin 4 //defines the digital pin used by CS terminal of BT module

TMRpcm tmrpcm; //creates an object to the speaker library

void setup(){
  tmrpcm.speakerPin = 9; //defining the speaker pin (it must be 9 in arduino uno)
  tmrpcm.setVolume(5); //defining the volume (1 a 7)
 
  Serial.begin(9600);
  if(!SD.begin(SD_ChipSelectPin)) { //if the microSD can't be read
    return; //do nothing
  }
}

void loop(){
  tmrpcm.play("solfege.wav"); 
  /*
   * The delay (Dt) below must be longer than the duration (Da) of the audio file
   * Dt-Da=The delay before the next round starts.
   */
  delay(26000);

    tmrpcm.play("music.wav"); 
  /*
   * The delay (Dt) below must be longer than the duration (Da) of the audio file
   * Dt-Da=The delay before the next round starts.
   */
  delay(290000);
}
