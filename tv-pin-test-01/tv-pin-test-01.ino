int tvPin=12;
   
void setup(){
    Serial.begin(115200);
    pinMode(tvPin, OUTPUT);                                                                                    
}

void loop(){
  digitalWrite(tvPin, HIGH);
  execute("turn-off"); 
  delay(3000); 
}

void execute(String command){
    Serial.println(command);
    if(command.indexOf("turn-on-the-tv")>=0){
      digitalWrite(tvPin, HIGH);
      delay(100);
    }
    else if(command.indexOf("turn-off-the-tv")>=0){
      digitalWrite(tvPin, LOW);
      delay(100);
    }
}
