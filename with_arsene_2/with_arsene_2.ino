int redLED = 12;
int greenLED = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  String mData = Serial.readStringUntil('\n');
  char Buf[mData.length()+1];
  mData.toCharArray(Buf, mData.length()+1);

  if(mData=="ON"){
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, HIGH);  
  }
  else if(mData=="OFF"){
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);    
  }

}
