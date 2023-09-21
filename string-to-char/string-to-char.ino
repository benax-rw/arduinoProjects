void setup() {
  Serial.begin(9600);
  Serial.println("Buffer is a place we need for storing our input before processing it.");
}

void loop() {
  String typedString = Serial.readStringUntil('\n');
  char Buffr[9];
  typedString.toCharArray(Buffr, 9);

  if(typedString.length()>0){
    Serial.print("Typed String: ");
    Serial.println(typedString);
  
    Serial.print("Length of Typed String: ");
    Serial.println(typedString.length());

    Serial.print("Number of characters the Buffer was told to store: ");
    Serial.println(sizeof(Buffr));
    
    Serial.print("Part of Typed String Stored by Buffer: ");
    Serial.println(Buffr);
    Serial.println("\nHave you noticed that a buffer stored less than it was told to?");
    Serial.println("Yes, because the buffer has to consider a NULL string terminator");
    Serial.println("NULL String Terminator serves as a reserved character used to signify the end of a string.");
    Serial.println("\n********************************\n");
  }
}
