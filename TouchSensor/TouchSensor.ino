int ledpin = 7 ; // sets the LED @pin 7
int touchpin = 9; // sets the KY-036 metal touch sensor @pin 9
int value ;         // defines the numeric variables as value
void setup ()
{
  pinMode (touchpin, INPUT) ; // sets the metal touch sensor as INPUT
  pinMode (ledpin, OUTPUT) ; // sets LED as the OUTPUT
}
void loop (){
  value = digitalRead (touchpin) ; // reads the value of the touchpin
  if (value == HIGH)      // If the value is HIGH 
  {
    digitalWrite (ledpin, HIGH);   // It will turn the LED ON, indicating that the sensor has been triggered
  }
  else        //otherwise
  {
    digitalWrite (ledpin, LOW);  // LED is turned off if sensor is not triggered
  }
}
