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
 
    Serial.begin(9600);
    
    initialize();
}


void loop(){

  doReceive();

}



void doReceive(){
    String mString;

    mString = Serial.readStringUntil("\n");

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
      Serial.println("Moving forward..."); 
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
      Serial.println("Reversing..."); 
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
      Serial.println("Moving left..."); 
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
      Serial.println("Moving right..."); 
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
      Serial.println("Stopped."); 
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
      Serial.println("Lights ON"); 
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
      Serial.println("Lights OFF"); 
    }
    else{
      //do nothing! 
    } 
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
