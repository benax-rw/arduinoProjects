#include <AFMotor.h>    //Adafruit Motor Driver Shield library
AF_DCMotor motorFrontLeft(1);
AF_DCMotor motorFrontRight(2);
AF_DCMotor motorRearLeft(3);
AF_DCMotor motorRearRight(4);

void setup() {
  Serial.begin (9600);
  pinMode(A1, OUTPUT);    //Analog pin A1 connected to TRIG
  pinMode(A0, INPUT);     //Analog pin A0 connected to ECHO
  motorInitialize(200);
}
void loop(){
  int distance_in_cm = detectObstacle();
  if(distance_in_cm <= 400){
    Serial.print(distance_in_cm);
    Serial.println(" cm");

    if(distance_in_cm >20){
      moveForward();
    }
    else{
      halt();  
    }
  }
  else{}
}

int detectObstacle(){
  long duration;           
  digitalWrite(A1, LOW);
  delayMicroseconds(2);
  digitalWrite(A1, HIGH);    //give a pulse of 10us on TRIG
  delayMicroseconds(10);
  digitalWrite(A1, LOW);
  duration = pulseIn(A0, HIGH);     //check time elasped in receiving back the pulse on ECHO
  return duration * 0.034 / 2; 
}

void motorInitialize(int x){
  motorFrontLeft.setSpeed(x);
  motorFrontRight.setSpeed(x);
  motorRearLeft.setSpeed(x);
  motorRearRight.setSpeed(x);
 
  motorFrontLeft.run(RELEASE);
  motorFrontRight.run(RELEASE);
  motorRearLeft.run(RELEASE);
  motorRearRight.run(RELEASE);  
}

void moveForward(){
    motorFrontLeft.run(FORWARD);
    motorFrontRight.run(FORWARD);
    motorRearLeft.run(FORWARD);
    motorRearRight.run(FORWARD);
    delay(1000);  
    motorFrontLeft.run(RELEASE);
    motorFrontRight.run(RELEASE);
    motorRearLeft.run(RELEASE);
    motorRearRight.run(RELEASE);      
}

void reverse(){
    motorFrontLeft.run(BACKWARD);
    motorFrontRight.run(BACKWARD);
    motorRearLeft.run(BACKWARD);
    motorRearRight.run(BACKWARD); 
    delay(1000);
    motorFrontLeft.run(RELEASE);
    motorFrontRight.run(RELEASE);
    motorRearLeft.run(RELEASE);
    motorRearRight.run(RELEASE);        
}

void halt(){
    motorFrontLeft.run(RELEASE);
    motorFrontRight.run(RELEASE);
    motorRearLeft.run(RELEASE);
    motorRearRight.run(RELEASE); 
    delay(1000);   
}
