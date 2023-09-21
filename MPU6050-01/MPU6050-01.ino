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

  // If you want, you can set accelerometer offsets
  // mpu.setAccelOffsetX();
  // mpu.setAccelOffsetY();
  // mpu.setAccelOffsetZ();
  
  checkSettings();
}

void checkSettings(){
  Serial.println();
  Serial.print(" * Sleep Mode:            ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Clock Source:          ");
  switch(mpu.getClockSource()){
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Accelerometer:         ");
  switch(mpu.getRange()){
    case MPU6050_RANGE_16G:Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:Serial.println("+/- 2 g"); break;
  }  

  Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());
  
  Serial.println();
}

void loop(){
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();

  //Raw (Non-Normalized) vectors
  Serial.print(" Xraw = ");
  Serial.print(rawAccel.XAxis);
  
  Serial.print(" Yraw = ");
  Serial.print(rawAccel.YAxis);
  
  Serial.print(" Zraw = ");
  Serial.println(rawAccel.ZAxis);

  //Normalized vectors
  Serial.print(" Xnorm = ");
  Serial.print(normAccel.XAxis);
  
  Serial.print(" Ynorm = ");
  Serial.print(normAccel.YAxis);
  
  Serial.print(" Znorm = ");
  Serial.println(normAccel.ZAxis);

  Serial.println("*************************************************************");

/*
 * ROLL DETECTION INDICATION
 */
 
  if(normAccel.XAxis<0 || normAccel.XAxis>2){
    Serial.println("Roll detected!");
    digitalWrite(amberLED, HIGH);
    digitalWrite(greenLED, LOW);
  }else{
    digitalWrite(amberLED, LOW);
  }
/*
 * PITCH DETECTION INDICATION
 */
  if(normAccel.YAxis<0 || normAccel.YAxis>2){
    Serial.println("Pitch detected!");
    digitalWrite(blueLED, HIGH);
    digitalWrite(greenLED, LOW);
  }else{
    digitalWrite(blueLED, LOW);
  }

/*
 * STABILITY INDICATION
 */
 
  if((normAccel.XAxis>0 && normAccel.XAxis<2) && (normAccel.YAxis>0 && normAccel.YAxis<2) ){
    Serial.println("No Pitch and No Roll");
    digitalWrite(greenLED, HIGH);
  }else{
    digitalWrite(greenLED, LOW);
  } 
  delay(10);
}
