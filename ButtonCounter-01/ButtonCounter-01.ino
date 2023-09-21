#include "SevSeg.h"
SevSeg sevseg; 

int btn1=2;
int btn2=3;
int btn3=4;
int led1=5;
int led2=6;
int led3=7;
int buzzer=10;
int btn1state, btn2state, btn3state;
int total_pressed;

void setup(){
  pinMode(btn1,INPUT_PULLUP);
  pinMode(btn2,INPUT_PULLUP);
  pinMode(btn3,INPUT_PULLUP);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  
  byte numDigits = 1;
  byte digitPins[] = {};
  byte segmentPins[] = {A4, A3, A0, A1, A2, A5, 8, 9};
  bool resistorsOnSegments = true;

  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void loop(){
  btn1state=digitalRead(btn1)^1; 
  btn2state=digitalRead(btn2)^1; 
  btn3state=digitalRead(btn3)^1;

  total_pressed = btn1state + btn2state + btn3state;

  /*
   * Print the total only if there is a pressed button
   */
  if(btn1state==1 || btn2state==1 || btn3state==1){
    sevseg.setNumber(total_pressed);
    sevseg.refreshDisplay();
    Serial.println(total_pressed);
  }
  else{
    sevseg.blank();
  }

  /*
   * When a button is pressed turn on a corresponding led
   */
  if(btn1state==1){
    digitalWrite(led1,HIGH);  
  }
  else{
    digitalWrite(led1,LOW);  
  }
  
  if(btn2state==1){
    digitalWrite(led2,HIGH);   
  }
  else{
    digitalWrite(led2,LOW); 
  }
  
  if(btn3state==1){
    digitalWrite(led3,HIGH);   
  }
  else{
    digitalWrite(led3,LOW);   
  }
  beep(total_pressed);
}

void beep(int times){
  for(int k=0; k<times; k++){
    digitalWrite(buzzer, HIGH);
    delay(500);   
    digitalWrite(buzzer, LOW);
    delay(50);     
  }
    digitalWrite(buzzer, LOW);
    delay(1000);  
}
