#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>

#define SD_ChipSelectPin 10 //defines the digital pin used by CS terminal of BT module

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
  do1(400); mi(400); sol(900); la(400); sol(600); do2(650); do2(1000); la(400); sol(500); 
  do1(400); mi(400); sol(900); sol(300); la(350); sol(300); mi(300); do1(300); re(1600); 
  do1(400); mi(400); sol(900); la(400); sol(600); do2(650); do2(1000); la(400); sol(500);
  do2(300); re2(350); mi2(1000); do2(300); re2(700); mi2(700); do2(1800); 

  /*
   * Chorus
   */
  do2(280); re2(300); mi2(1000); do2(280); re2(600); mi2(700); do2(1000); la(400); sol(600); 
  la(700); sol(900);sol(280); la(350); sol(300); mi(250); do1(300); re(1600); 
  do1(400); mi(400); sol(900); la(400); sol(600); do2(650); do2(1000); la(400); sol(500);
  do2(300); re2(350); mi2(1000); do2(300); re2(700); mi2(700); do2(1800); 
}

void do1(int t){
  tmrpcm.play("do.wav"); 
  delay(t); 
}

void re(int t){
  tmrpcm.play("re.wav"); 
  delay(t); 
}

void mi(int t){
  tmrpcm.play("mi.wav"); 
  delay(t); 
}

void fa(int t){
  tmrpcm.play("fa.wav"); 
  delay(t); 
}

void sol(int t){
  tmrpcm.play("sol.wav"); 
  delay(t); 
}

void la(int t){
  tmrpcm.play("la.wav"); 
  delay(t); 
}

void ti(int t){
  tmrpcm.play("ti.wav"); 
  delay(t); 
}
void do2(int t){
  tmrpcm.play("do2.wav"); 
  delay(t); 
}

void re2(int t){
  tmrpcm.play("re2.wav"); 
  delay(t); 
}

void mi2(int t){
  tmrpcm.play("mi2.wav"); 
  delay(t); 
}

void fa2(int t){
  tmrpcm.play("fa2.wav"); 
  delay(t); 
}

void sol2(int t){
  tmrpcm.play("sol2.wav"); 
  delay(t); 
}

void la2(int t){
  tmrpcm.play("la2.wav"); 
  delay(t); 
}

void ti2(int t){
  tmrpcm.play("ti2.wav"); 
  delay(t); 
}
void do3(int t){
  tmrpcm.play("do3.wav"); 
  delay(t); 
}
 
