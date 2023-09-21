#define ldr A0 //A0
void setup(){
  Serial.begin(9600);
  pinMode(ldr, INPUT_PULLUP);  
}

void loop() {
  int ldr_value = 0;
  ldr_value = analogRead(ldr);
  Serial.println(ldr_value);
  delay(1000);
}
