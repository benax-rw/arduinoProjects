#include <DHT.h>
DHT dht(2,DHT11); //pin2 is equivalent to D4 on esp8266 board

void setup(){
  Serial.begin (115200);
  dht.begin();
}

void readDHT11(String(&params)[3]){
  float Humidity = 0.0;
  float Temperature = 0.0;
  float HeatIndex = 0.0;
  /*Read temperature and humidity from DHT sensor*/
  Humidity = dht.readHumidity();
  Temperature = dht.readTemperature();
  /*The block of code below checks if either temperature or humidity failed
  and then exits early, allowing you not to waste a time.*/
  if (isnan(Humidity) || isnan(Temperature)){
    Serial.println("Failed to read from DHT sensor.");
    params [0] = "";
    params [1] = "";
    params [2] = "";
  }
  else{
    /*Calculate Heat Index */
    HeatIndex = dht.computeHeatIndex(Temperature, Humidity, false);
    params [0] = String(Temperature);
    params [1] = String(Humidity);
    params [2] = String(HeatIndex);
  }
}

void loop(){ 
  String data[3];
  readDHT11(data);
  String Temperature = data[0];
  String Humidity = data[1];
  String HeatIndex = data[2];
  
  Serial.print("Temperature: ");
  Serial.println(Temperature); 

  Serial.print("Humidity: ");
  Serial.println(Humidity); 

  Serial.print("Heat Index: ");
  Serial.println(HeatIndex); 

  Serial.println("******************");  
  delay(3000);
}
