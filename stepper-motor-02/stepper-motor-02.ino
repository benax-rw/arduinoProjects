//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 1000;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 14, 12, 13, 15);

void setup() {
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  myStepper.setSpeed(25);
}

void loop() {
  myStepper.step(stepsPerRevolution);
  delay(1000);
  myStepper.step(-stepsPerRevolution);
  delay(1000);
}
