void setup() {
  Serial.begin(9600);
  Serial.println("Buffer is a place we need for storing our input before processing it.");
}

void loop() {
  String typedString = Serial.readStringUntil('\n');
  char Buffr[typedString.length()+1];
  typedString.toCharArray(Buffr, typedString.length()+1);

  if(typedString.length()>0){
    Serial.print("Typed String: ");
    Serial.println(typedString);
  
    Serial.print("Length of Typed String: ");
    Serial.println(typedString.length());

    Serial.print("Number of characters the Buffer was told to store: ");
    Serial.println(sizeof(Buffr));
    
    Serial.print("Part of Typed String Stored by Buffer: ");
    Serial.println(Buffr);
    Serial.println("\nWe did dynamic allocation.");
    Serial.println("\n********************************\n");
  }
}
