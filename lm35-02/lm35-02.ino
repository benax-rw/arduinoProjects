void setup(){
    Serial.begin(9600);
}

void loop(){
    float temp;
    temp = analogRead(A0);
    temp = temp * 0.48828125;
    Serial.print("Temperature = ");
    Serial.print(temp);
    Serial.print(char(176));
    Serial.print("C");
    Serial.println();
    delay(1000);
}
