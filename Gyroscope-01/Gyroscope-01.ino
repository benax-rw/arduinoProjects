#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;
// Timers
unsigned long timer = 0;
float timeStep = 0.01;
// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

int amberLED=6;
int blueLED=10;
int greenLED=11;
int redLED=12;

void setup(){
  pinMode(amberLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
    
  Serial.begin(115200);
  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();
  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  // mpu.setThreshold(3);
}
void loop()
{
  timer = millis();
  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();
  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;
  // Output raw
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);  
  Serial.print(" Yaw = ");
  Serial.println(yaw);


/*
 * PITCH FRONT DETECTION INDICATION
 */
  if(pitch>-0.50){
    Serial.println("Pitch front detected!");
    digitalWrite(blueLED, HIGH);
  }
  else if(pitch<-0.80){
    Serial.println("Pitch back detected!");
    digitalWrite(blueLED, HIGH);
  }else{
    digitalWrite(blueLED, LOW);
  }

 
  /*
 * ROLL DETECTION INDICATION
 */
 
  if(roll>-0.70){
    Serial.println("Roll Right Detected!");
    digitalWrite(amberLED, HIGH);
  }

  else if(roll<-0.90){
    Serial.println("Roll Left Detected!");
    digitalWrite(amberLED, HIGH);
  }else{
    digitalWrite(amberLED, LOW);
  }


 
  /*
 * YAW DETECTION INDICATION
 */
 
  if(yaw>4.20){
    Serial.println("Yaw Right Detected!");
    digitalWrite(redLED, HIGH);
  }

  else if(yaw<4.00){
    Serial.println("Yaw Left Detected!");
    digitalWrite(redLED, HIGH);
  }else{
    digitalWrite(redLED, LOW);
  }  

/*
 * STABILITY INDICATION
 */
 
  if((pitch>-42.50 && pitch<-40.50) && (roll>-1.92 && roll<-1.52) && (yaw>80.00 && yaw<60.00)){
    Serial.println("No Pitch and No Roll");
    digitalWrite(greenLED, HIGH);
  }else{
    digitalWrite(greenLED, LOW);
  }
  
  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));
}
