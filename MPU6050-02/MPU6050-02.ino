#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int amberLED=6;
int blueLED=10;
int greenLED=11;

void setup(){
  pinMode(amberLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}

void loop(){
  // Read normalized values 
  Vector normAccel = mpu.readNormalizeAccel();

  float pitch = normAccel.XAxis;
  float roll = normAccel.YAxis; 

  // Output
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);
  
  Serial.println();
  Serial.println("**********************************************");

/*
 * PITCH FRONT DETECTION INDICATION
 */
  if(pitch<0.00){
    Serial.println("Pitch front detected!");
    digitalWrite(blueLED, HIGH);
  }
  
/*
 * PITCH FRONT DETECTION INDICATION
 */
  else if(pitch>0.90){
    Serial.println("Pitch back detected!");
    digitalWrite(blueLED, HIGH);
  }else{
    digitalWrite(blueLED, LOW);
  }

 
  /*
 * ROLL DETECTION INDICATION
 */
 
  if(roll>0.60){
    Serial.println("Roll Right Detected!");
    digitalWrite(amberLED, HIGH);
  }

  else if(roll<0.00){
    Serial.println("Roll Left Detected!");
    digitalWrite(amberLED, HIGH);
  }else{
    digitalWrite(amberLED, LOW);
  }

/*
 * STABILITY INDICATION
 */
 
  if((pitch>0.00 && pitch<0.90) && (roll>0 && roll<0.60)){
    Serial.println("No Pitch and No Roll");
    digitalWrite(greenLED, HIGH);
  }else{
    digitalWrite(greenLED, LOW);
  } 
  delay(10);
}

 
