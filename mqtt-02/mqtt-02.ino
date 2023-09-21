#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

WiFiClient espClient;
PubSubClient client(espClient);
#define DHTPin 14
DHT dht(DHTPin, DHT11);

const char* ssid = "RCA-Wifii";
const char* password = "@rca@2013";
const char* mqtt_server = "82.165.97.169";


long now = millis();
long lastMeasure = 0;

void connectToWiFi(){
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("WiFi connected - ESP IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }

  Serial.println();
}

void reconnect(){
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");  
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  dht.begin();
  Serial.begin(115200);
  connectToWiFi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop(){
  if (!client.connected()){
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client");
    
  now = millis();
  // Publishes new temperature every 10 seconds
  if(now - lastMeasure > 10000){
    lastMeasure = now;
    // Read temperature as Celsius (the default)
    float temperature_as_double = dht.readTemperature();
    // Check if any reads failed and exit early (to try again).
    if(isnan(temperature_as_double)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    //Let's use dtostrf() to convert a float into a string.
    //The synthax is: dtostrf(float_value, min_width, num_digits_after_decimal, where_to_store_string)
    static char temperature_buffer[7];
    dtostrf(temperature_as_double, 6, 2, temperature_buffer);

    //Let's publish the temperature
    client.publish("/esp8266/rca_room_temperature", temperature_buffer);

    Serial.print(" %\t Temperature: ");
    Serial.print(temperature_buffer);
    Serial.println(" *C ");
  }
}
