#include <SPI.h>
#include <SD.h>

#define SD_CHIP_SELECT 4

File myFile;

void setup(){
  Serial.begin(9600);
  SPI.begin();
  if(!SD.begin(SD_CHIP_SELECT)) {
    Serial.println("SD Card not accessible!");
    while (1);
  }

  Serial.println("SD CARD READY:");
  myFile = SD.open("ops.txt");

  if(myFile){
    Serial.println("ops.txt:");
    while(myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
    }else {
    Serial.println("error opening ops.txt");
  }
}

void loop(){}  
