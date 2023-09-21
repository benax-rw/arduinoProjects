int led_red = 8;
int led_green = 9;
int led_blue = 10;

void setup() {
  Serial.begin(9600);
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_blue, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    byte b = Serial.read();
    
    if (b == '1') {
      digitalWrite(led_red, HIGH);
      digitalWrite(led_green, LOW);
      digitalWrite(led_blue, LOW);
    } else if (b == '2') {
      digitalWrite(led_red, LOW);
      digitalWrite(led_green, HIGH);
      digitalWrite(led_blue, LOW);
    } else if (b == '3') {
      digitalWrite(led_red, LOW);
      digitalWrite(led_green, LOW);
      digitalWrite(led_blue, HIGH);
    } 
  }
}
