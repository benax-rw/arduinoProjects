int lightSensorPin = A0;     //Light sensor is connected to the pin A0 (Analog 0)
int moisture;
void setup(){
  Serial.begin(9600);       //Initializing the Serial Monitor       
}
void loop(){
  moisture = analogRead(lightSensorPin);
  Serial.println(moisture);
  delay(500);
}
