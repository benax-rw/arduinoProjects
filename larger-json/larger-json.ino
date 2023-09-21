#include <ArduinoJson.h>
#include <stdio.h>

#define LONG_STRING "{\
 "topLevel":[\
        {\
        "id":"10079",\
        "recipient":"+250789449645",\
        "message":"Muraho Gabi. Icyangombwa mwasabye kirimo gukorwa.\r\nMushobora kuza kukireba kuri REB nyuma y'iminsi ibiri. Murakoze."\
        },\
  
        {\
        "id":"10208",\
        "recipient":"+250788862399",\
        "message":"Muraho Happier. Dossier yanyu irabura ibi bikurikira: please attach the payment slip."\
        }\
  ]\
}\
";

void setup(){ 
  Serial.begin(9600);
}

void loop(){
    parseResponse();
    delay(5000); //Repeat after n seconds
}

/*
 * PARSE THE RESPONSE
*/
void parseResponse(){
    String payload = 
    
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, payload);
    JsonObject obj = doc.as<JsonObject>();
    
    int actualDataSize =(obj["topLevel"]).size();
    
    Serial.print("Actual Data Size: ");
    Serial.println(actualDataSize);
    
    for(int k=0; k<actualDataSize; k++){
      String id = obj["topLevel"][k]["id"];
      String recipient = obj["topLevel"][k]["recipient"];
      String SMS = obj["topLevel"][k]["message"];

      Serial.print("ID: ");
      Serial.println(id);
      Serial.print("Recipient: ");
      Serial.println(recipient);
      Serial.print("SMS: ");
      Serial.println(SMS);  
      Serial.print("\n**************************\n");  

    }
}
