#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "dlink-M921-0cd4";
const char* password = "*Talk_le55#";
const char* mqtt_server = "82.165.97.169";

WiFiClient espClient;
PubSubClient client(espClient);

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.subscribe("esp8266/publisher");
  client.connect("ESP8266Client");
}

void loop() {
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);
}
