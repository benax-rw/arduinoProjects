#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Replace with your network credentials
const char* ssid = "dlink-M921-0cd4";
const char* password = "*Talk_le55#";

// Replace with your MQTT broker IP address
const char* mqtt_server = "82.165.97.169";

// Initialize the WiFi and MQTT client objects
WiFiClient espClient;
PubSubClient client(espClient);

// MQTT topic to subscribe to
  const char* topic = "esp8266/temperature";

// MQTT callback function that is called when a message is received
void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Message received: ");
  Serial.println((char*)payload);
}

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Set up the MQTT client
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // Connect to MQTT broker
  while (!client.connected()) {
    if (client.connect("ESP8266Client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }

  // Subscribe to the MQTT topic
  client.subscribe(topic);
}

void loop() {
  // Check if client is connected to MQTT broker
  if (!client.connected()) {
    //Serial.println("Connection lost, reconnecting...");
    if (client.connect("ESP8266Client")) {
      //Serial.println("Reconnected to MQTT broker");

      //Serial.println(topic);
      // Resubscribe to the MQTT topic
      
      client.subscribe(topic);
    }
  }

  // Process incoming MQTT messages
  client.loop();
}
