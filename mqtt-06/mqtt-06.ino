#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

const char* ssid = "RCA-WiFi";
const char* password = "rca@2019";
const char* mqtt_server = "82.165.97.169";

#define D1_pin 13
#define A0_pin A0

long now = millis();
long lastMeasure = 0;

void setup_wifi(){
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
  Serial.print(topic);
  Serial.print(": ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }

  if(messageTemp=="ON"){
    digitalWrite(D1_pin, LOW);
  }
  if(messageTemp=="OFF"){
    digitalWrite(D1_pin, HIGH);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect

    if (client.connect("ESP8266Client")) {
      Serial.println("connected");  
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      //Note: by the time of uploading the code the topics should be up and running!
      client.subscribe("/oti_light_signal");

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
  Serial.begin(115200);
  pinMode(A0_pin, INPUT);
  pinMode(D1_pin, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop(){
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client");
  now = millis();
  // Publishes light status and humidity every 10 seconds
  if(now - lastMeasure > 10000) {
    lastMeasure = now;
    int ldr_value = analogRead(A0_pin); 
    char* state;
    if(ldr_value<500){
      state = "OTI Light is ON"; 
    }
    else{
     state = "OTI Light is OFF";        
    }
    client.publish("/oti_light_status", state);
    
    Serial.print("Light Intensity: ");
    Serial.print(ldr_value);
    Serial.print(" ---- ");

    Serial.println(state);
  }
}
