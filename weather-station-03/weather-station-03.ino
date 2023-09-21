#include <ESP8266WiFi.h>
#include <DHT.h>
DHT dht(14,DHT11);
WiFiClient wifiClient;    
void setup(){
    Serial.begin(115200);
    dht.begin();
    WiFi.begin("Benax Technologies", "ben@kusu");                                                                                       
}
void loop( ){
    float temperature = 0.0;
    float humidity = 0.0;
    float heat_index = 0.0;
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    if(isnan(humidity) || isnan(temperature)){
      Serial.println("Failed to read from DHT sensor.");
    }
    else{
      heat_index = dht.computeHeatIndex(temperature, humidity, false);
      String payload="";
      String device = "Nyabihu-Device-001";
      payload = "device="+device
      +"&temperature="+(String)temperature
      +"&humidity="+(String)humidity
      +"&heat_index="+(String)heat_index;    
      wifiClient.connect("iot.benax.rw", 80); 
      wifiClient.println("POST /projects/a001/backend.php HTTP/1.1");
      wifiClient.println("Host: iot.benax.rw");
      wifiClient.println("User-Agent: ESP8266/1.0");
      wifiClient.println("Content-Type: application/x-www-form-urlencoded");
      wifiClient.println("Content-Length: " +(String)payload.length());
      wifiClient.println();
      wifiClient.print(payload);   
      String response = "";
      response += wifiClient.readStringUntil('\n');
      Serial.println(response);
    }
    delay(15000);  
}
