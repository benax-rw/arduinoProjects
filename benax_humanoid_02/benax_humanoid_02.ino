#include <SPI.h>
#include <RH_RF95.h>
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7
#define RF95_FREQ 950.0
RH_RF95 rf95(RFM95_CS, RFM95_INT);

int left_wheel_forward = 2; //Pin2 of the LoRa Board "Adafruit Feather 32u4"
int left_wheel_reverse = 3; //Pin3
int right_wheel_forward = 6; //Pin6
int right_wheel_reverse = 10; //Pin10
int lights = 11; //Pin11

void setup(){
    pinMode(left_wheel_reverse, OUTPUT);
    pinMode(left_wheel_forward, OUTPUT);
    pinMode(right_wheel_forward, OUTPUT);
    pinMode(right_wheel_reverse, OUTPUT);
    pinMode(lights, OUTPUT);
 
    pinMode(RFM95_RST, OUTPUT);
    digitalWrite(RFM95_RST, HIGH);
    Serial.begin(9600);
    
    Serial.println("Rx Ready!");
    digitalWrite(RFM95_RST, LOW);
    digitalWrite(RFM95_RST, HIGH);
    while (!rf95.init()) {
        Serial.println("LoRa radio init failed");
    Serial.println("Uncomment '#define SERIAL_DEBUG' in RH_RF95.cpp for detailed debug info");
    while (1)
        ;
    }
    Serial.println("LoRa radio init OK!");
    if (!rf95.setFrequency(RF95_FREQ)) {
            Serial.println("setFrequency failed");
            while (1)
                ;
    }
    Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
    rf95.setTxPower(23, false);

    initialize();
}


void loop(){

  doReceive();

}



void doReceive(){
  if(rf95.available()){
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if(rf95.recv(buf, &len)){
    char* mChar = (char*)buf;
    Serial.println(mChar);

    String mString;

    mString = String(mString + mChar);

    mString.trim();
    mString.replace("     "," "); //Turn 5 spaces into 1 space
    mString.replace("    "," "); //Turn 4 spaces into 1 space
    mString.replace("   "," "); //Turn 3 spaces into 1 space
    mString.replace("  "," "); //Turn 2 spaces into 1 space

    if(mString.indexOf("forward")>=0){
      int duration;
      mString.replace("forward", "");
      mString.trim();
      if(mString !=""){
        duration = mString.toInt();
        moveForward(duration*1000);
        standStillNoArgs();
      }
      else{
        moveForwardNoArgs(); 
      }
      doReply("Moving forward..."); 
    }
    else if(mString.indexOf("reverse")>=0){
      int duration;
      mString.replace("reverse", "");
      mString.trim();
      if(mString !=""){
        duration = mString.toInt();
        reverse(duration*1000);
        standStillNoArgs();
      }
      else{
        reverseNoArgs(); 
      }
      doReply("Reversing..."); 
    }
            
    else if(mString.indexOf("left")>=0){
      int duration;
      mString.replace("left", "");
      mString.trim();
      if(mString !=""){
        duration = mString.toInt();
        moveLeft(duration*1000);
        standStillNoArgs();
      }
      else{
        moveLeftNoArgs(); 
      }
      doReply("Moving left..."); 
    }

    else if(mString.indexOf("right")>=0){
      int duration;
      mString.replace("right", "");
      mString.trim();
      if(mString !=""){
        duration = mString.toInt();
        moveRight(duration*1000);
        standStillNoArgs();
      }
      else{
        moveRightNoArgs(); 
      }
      doReply("Moving right..."); 
    }

    else if(mString.indexOf("stop")>=0){
      int duration;
      mString.replace("stop", "");
      mString.trim();
      if(mString !=""){
        duration = mString.toInt();
        standStill(duration*1000); //When used in a series of commands
      }
      else{
        standStillNoArgs(); 
      }
      doReply("Stopped."); 
    }
    
    else if(mString.indexOf("lights on")>=0){
      int duration;
      mString.replace("lights on", "");
      mString.trim();
      if(mString !=""){
        duration = mString.toInt();
        lightsON(duration*1000);
      }
      else{
        lightsONNoArgs(); 
      }
      doReply("Lights ON"); 
    }

    else if(mString.indexOf("lights off")>=0){
      int duration;
      mString.replace("lights off", "");
      mString.trim();
      if(mString !=""){
        duration = mString.toInt();
        lightsOFF(duration*1000);
      }
      else{
        lightsOFFNoArgs(); 
      }
      doReply("Lights OFF"); 
    }
    
    else{
      doReply("Invalid Command!"); 
    }
  }
  else{

    Serial.println("Receive failed");

  }
}  

}



void doReply(uint8_t data[]){

  rf95.send(data, 160); //I know no limit of characters per message!

  rf95.waitPacketSent();

}

void initialize(){
  digitalWrite(left_wheel_forward,0);
  digitalWrite(right_wheel_forward,0);  
  digitalWrite(left_wheel_reverse,0);
  digitalWrite(right_wheel_reverse,0);
  digitalWrite(lights,1);        
}

void moveForward(int duration){
  digitalWrite(left_wheel_forward,1);
  digitalWrite(right_wheel_forward,1);  
  digitalWrite(left_wheel_reverse,0);
  digitalWrite(right_wheel_reverse,0);   
  delay(duration);     
}

void moveForwardNoArgs(){
  digitalWrite(left_wheel_forward,1);
  digitalWrite(right_wheel_forward,1);  
  digitalWrite(left_wheel_reverse,0);
  digitalWrite(right_wheel_reverse,0);   
  delay(500);     
}

void reverse(int duration){
  digitalWrite(left_wheel_forward,0);
  digitalWrite(right_wheel_forward,0);  
  digitalWrite(left_wheel_reverse,1);
  digitalWrite(right_wheel_reverse,1);   
  delay(duration);     
}

void reverseNoArgs(){
  digitalWrite(left_wheel_forward,0);
  digitalWrite(right_wheel_forward,0);  
  digitalWrite(left_wheel_reverse,1);
  digitalWrite(right_wheel_reverse,1);   
  delay(500);     
}

void moveLeft(int duration){
  digitalWrite(left_wheel_forward,0);
  digitalWrite(right_wheel_forward,1);  
  digitalWrite(left_wheel_reverse,0);
  digitalWrite(right_wheel_reverse,0);   
  delay(duration);  
}

void moveLeftNoArgs(){
  digitalWrite(left_wheel_forward,0);
  digitalWrite(right_wheel_forward,1);  
  digitalWrite(left_wheel_reverse,0);
  digitalWrite(right_wheel_reverse,0);   
  delay(500);  
}

void moveRight(int duration){
  digitalWrite(left_wheel_forward,1);
  digitalWrite(right_wheel_forward,0);  
  digitalWrite(left_wheel_reverse,0);
  digitalWrite(right_wheel_reverse,0);   
  delay(duration);  
}

void moveRightNoArgs(){
  digitalWrite(left_wheel_forward,1);
  digitalWrite(right_wheel_forward,0);  
  digitalWrite(left_wheel_reverse,0);
  digitalWrite(right_wheel_reverse,0);   
  delay(500);  
}

void standStill(int duration){
  digitalWrite(left_wheel_forward,0);
  digitalWrite(right_wheel_forward,0);  
  digitalWrite(left_wheel_reverse,0);
  digitalWrite(right_wheel_reverse,0);   
  delay(duration);  
}

void standStillNoArgs(){
  digitalWrite(left_wheel_forward,0);
  digitalWrite(right_wheel_forward,0);  
  digitalWrite(left_wheel_reverse,0);
  digitalWrite(right_wheel_reverse,0);   
  delay(500);  
}

void lightsON(int duration){
  digitalWrite(lights,0);
  delay(duration);
  lightsOFF(10);
}

void lightsOFF(int duration){
  digitalWrite(lights,1); //Lights OFF
  delay(duration);
}

void lightsONNoArgs(){
  digitalWrite(lights,0); //Lights ON
}

void lightsOFFNoArgs(){
  digitalWrite(lights,1); //Lights OFF
}
