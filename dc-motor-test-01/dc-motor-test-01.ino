#define motor1_1 3
#define motor1_2 4

void setup(){
  pinMode(motor1_1, OUTPUT);
  pinMode(motor1_2, OUTPUT);
}

void loop(){
  digitalWrite(motor1_1, HIGH);
  digitalWrite(motor1_2, LOW);
  delay(2000);
  digitalWrite(motor1_2,HIGH);
  digitalWrite(motor1_1, LOW);
  delay(2000);
}
