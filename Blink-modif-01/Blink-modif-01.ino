int relay = 7;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(relay, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  for(int i=0; i<50; i++){
    digitalWrite(relay, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(20);                       // wait for a second
    digitalWrite(relay, HIGH);    // turn the LED off by making the voltage LOW
    delay(20); // wait for a second
  }
 for(int i=0; i<5; i++){
  digitalWrite(relay, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(relay, HIGH);    // turn the LED off by making the voltage LOW
  delay(500); // wait for a second
}  
}
