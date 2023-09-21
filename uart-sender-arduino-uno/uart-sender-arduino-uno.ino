void setup(){
  Serial.begin(9600);
}

void loop() {
  //Write something to Serial
  Serial.print("This is sent by print rather ...");
  delay(30000);
}
