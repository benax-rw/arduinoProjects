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

  delay(1000);
  
  myFile = SD.open("data.txt");
  if(myFile){
      Serial.println("\n****** Content of data.txt starts ******\n");
      while(myFile.available()){
        Serial.write(myFile.read());
      }
      myFile.close();
      Serial.println("\n****** Content of data.txt ends ******\n");
    }else{
      Serial.println("error opening data.txt");
    }
}

void loop(){}
