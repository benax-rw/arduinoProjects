#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "dlink-M921-0cd4";
const char* password = "*Talk_le55#";
const char* mqtt_server = "82.165.97.169";
                  
WiFiClient espClient;
PubSubClient client(espClient);

void setup(){
  Serial.begin(115200);                       
  setup_wifi(); 
  client.setServer(mqtt_server, 1883);
  client.setCallback(Received_Message);
}

void setup_wifi(){
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void Received_Message(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println((char)payload[0]);
  Serial.println();

}


void reconnect(){
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      //Once connected, publish an announcement...
      //client.publish("ESP8266/ESP02", "1");

      // ... and resubscribe

      client.subscribe("esp8266/temperature");
    }
    else{
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop(){
  if(!client.connected()) {
    reconnect();
  }
  client.loop();
}
