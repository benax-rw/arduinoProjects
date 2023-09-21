#include <AFMotor.h>
AF_DCMotor motorFrontLeft(1);
AF_DCMotor motorFrontRight(2);
AF_DCMotor motorRearLeft(3);
AF_DCMotor motorRearRight(4);

void setup() {
  Serial.begin(9600);
  Serial.println("Motor test!");
  motorInitialize(200);
}

void loop(){
  moveForward(1000);
  delay(1000);
  reverse(1000);
  delay(1000); 
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

void moveForward(int duration){
    motorFrontLeft.run(FORWARD);
    motorFrontRight.run(FORWARD);
    motorRearLeft.run(FORWARD);
    motorRearRight.run(FORWARD);
    delay(duration);
    motorFrontLeft.run(RELEASE);
    motorFrontRight.run(RELEASE);
    motorRearLeft.run(RELEASE);
    motorRearRight.run(RELEASE);     
}

void reverse(int duration){
    motorFrontLeft.run(BACKWARD);
    motorFrontRight.run(BACKWARD);
    motorRearLeft.run(BACKWARD);
    motorRearRight.run(BACKWARD);
    delay(duration);
    motorFrontLeft.run(RELEASE);
    motorFrontRight.run(RELEASE);
    motorRearLeft.run(RELEASE);
    motorRearRight.run(RELEASE);     
}
