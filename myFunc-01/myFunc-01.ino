void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  myFunc();
  delay(1000);
}

void myFunc(){
  int a=10, b=20;
  Serial.printf("a=%d b=%d", a,b);
  Serial.println();
  a=a+b;
  b=a-b;
  a=a-b;
  Serial.printf("a=%d b=%d", a,b);
  Serial.println();
  Serial.println("******************");  
}
