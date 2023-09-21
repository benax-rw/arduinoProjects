void setup() {
  // put your setup code here, to run once:
  pinMode(D15, OUTPUT);
}

void loop(){
  // put your main code here, to run repeatedly:
  for(int k=0; k<=1; k++){
    digitalWrite(D15,k);
    delay(100);
  }
}
