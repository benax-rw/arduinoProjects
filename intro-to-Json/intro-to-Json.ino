#include <ArduinoJson.h>

void setup(){
  Serial.begin(9600);
}

void loop(){ 
    parseJSON();
    delay(5000); //repeat after n seconds
}

void parseJSON(){
  String payload = "{'sensor':'gps','time':1351824120,'data':[48.756080,2.302038]}";
  

  StaticJsonDocument<200> doc;
  //Deserialization
  deserializeJson(doc, payload);
  JsonObject obj = doc.as<JsonObject>();

  //store data into variables  
  long time = obj[String("time")];
  String sensor = obj["sensor"];
  double latitude = doc["data"][0];
  double longitude = doc["data"][1];

  // Print values.
  Serial.print("Sensor: ");
  Serial.println(sensor);
  Serial.print("Time: ");
  Serial.println(time);
  Serial.print("Latitude: ");
  Serial.println(latitude, 6);
  Serial.print("Longitude: ");
  Serial.println(longitude, 6);
}
