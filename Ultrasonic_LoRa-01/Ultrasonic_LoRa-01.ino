const int trigPin = 12;
const int echoPin = 13;
const int output = 2;
long duration, distance;
void setup(){
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(output, OUTPUT);
  pinMode(echoPin, INPUT);
}
 

void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
 
  if (distance >= 10 || distance <= 0){
     digitalWrite(output, LOW);
   }
   else{
     digitalWrite(output, HIGH);
     Serial.print(distance);
     Serial.println(" cm");
   }
   delay(500);
}
