#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

#define PIN_TX 10
#define PIN_RX 11

SoftwareSerial mySerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,

void setup(){
  mySerial.begin(9600);
  Serial.begin(9600);

  /************* Turn on the GPS power************/
  if(sim808.attachGPS())
    Serial.println("GPS started.");
  else
    Serial.println("GPS Failed.");
    
  Serial.println();
}

void loop(){
  /************** Get GPS data *******************/
  if(sim808.getGPS()){
    Serial.println("*****************");
    Serial.print(sim808.GPSdata.year);
    Serial.print("-");
    Serial.print(sim808.GPSdata.month);
    Serial.print("-");
    Serial.print(sim808.GPSdata.day);
    Serial.print(" ");
    Serial.print(sim808.GPSdata.hour);
    Serial.print(":");
    Serial.print(sim808.GPSdata.minute);
    Serial.print(":");
    Serial.print(sim808.GPSdata.second);

    Serial.println();
    
    Serial.print("Location: ");
    Serial.print(sim808.GPSdata.lat,6);
    
    Serial.print(",");
    Serial.println(sim808.GPSdata.lon,6);

    /*Restart the GPS*/
    sim808.detachGPS();
    delay(1000);
    sim808.attachGPS();
  }
}
