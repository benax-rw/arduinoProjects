
#include <SPI.h>
#include <SD.h>

#define SD_CHIP_SELECT 4        

File myFile;

void setup(){
  Serial.begin(9600);                                                                                     
  SPI.begin(); 
  Serial.println("Initializing SD card...");
  if (!SD.begin(SD_CHIP_SELECT)) {
    Serial.println("SD card initialization failed.");
    while (1);
  }
  Serial.println(F("SD card initialized.\n"));  
  Serial.println("Type some text and then hit RETURN Key");                                            
}
void loop(){
  String input = Serial.readStringUntil('\n');
  if(input!=""){
    if(writeToSDCard(input)){
      Serial.println("Text '"+input+"' written.");
    }
    else{
      Serial.println("Text writing failed."); 
    }
  }
}

bool writeToSDCard(String data){
  myFile = SD.open("data.txt", FILE_WRITE);
  if(myFile){
    myFile.println(data);
    myFile.close();
    return true;
  }else{
    Serial.println("error opening data.txt");
    return false;
  }      
 }
