int pin_a = 2;
int pin_b = 3;
int pin_c = 6;
int pin_d = 10;
int pin_e = 11;

void setup() {
  pinMode(pin_a, OUTPUT);
  pinMode(pin_b, OUTPUT);
  pinMode(pin_c, OUTPUT);
  pinMode(pin_d, OUTPUT);
  pinMode(pin_e, OUTPUT);
}

void loop() {
  digitalWrite(pin_a, HIGH);
  digitalWrite(pin_b, LOW);
  digitalWrite(pin_c, HIGH);
  digitalWrite(pin_d, LOW);
  
  digitalWrite(pin_e, HIGH);
  delay(3000);
  
  digitalWrite(pin_a, LOW);
  digitalWrite(pin_b, HIGH);
  digitalWrite(pin_c, LOW);
  digitalWrite(pin_d, HIGH);
  
  digitalWrite(pin_e, LOW);
  delay(3000);
}
