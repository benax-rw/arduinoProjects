int sensorPin = A0;
void setup(){
  Serial.begin(9600);      
}
void loop(){
  int lightIntensity;
  lightIntensity = analogRead(sensorPin);
  Serial.println(lightIntensity);
  delay(200);
}
