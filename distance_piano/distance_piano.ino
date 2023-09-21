#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>

#define SD_ChipSelectPin 10 //defines the digital pin used by CS terminal of BT module

TMRpcm tmrpcm; //creates an object to the speaker library

const int trigPin = A0;
const int echoPin = A1;
long duration, distance;

void setup(){
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  tmrpcm.speakerPin = 9; //defining the speaker pin (it must be 9 in arduino uno)
  tmrpcm.setVolume(5); //defining the volume (1 a 7)
 
  Serial.begin(9600);
  if(!SD.begin(SD_ChipSelectPin)) { //if the microSD can't be read
    return; //do nothing
  } 
}
 

void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2)/29.1;
 
  if(distance >= 3 && distance <=5){
    do1(100);
   }
  if(distance >5 && distance <=8){
    re(100);
   } 
  if(distance >8 && distance <=10){
    mi(100);
   }
  if(distance >10 && distance <=12){
    fa(100);
   } 
  if(distance >12 && distance <=14){
    sol(100);
   }
  if(distance >14 && distance <=16){
    la(100);
   }
  if(distance >16 && distance <=18){
    ti(100);
   }
  if(distance >16 && distance <=18){
    do2(100);
   }                      
   else{
    //donothing
   }
   delay(100);
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
