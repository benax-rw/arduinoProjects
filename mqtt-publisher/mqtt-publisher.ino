#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "dlink-M921-0cd4";
const char* password = "*Talk_le55#";
const char* mqtt_server = "82.165.97.169";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  client.setServer(mqtt_server, 1883);
  client.connect("publisher");
}

void loop() {
  client.publish("/esp8266/publisher", "Hello, subscriber!");
  delay(5000);
}
