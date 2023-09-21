void setup(){
  Serial.begin(9600);
}

void loop(){
    double temperature = 0.0;
    temperature = (analogRead(A0)*((double)5000.0/1024.0));
    Serial.println(temperature);
    delay(500);
}
