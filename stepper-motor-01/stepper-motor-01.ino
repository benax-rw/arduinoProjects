#include <Stepper.h>

// Define the number of steps per revolution of your stepper motor
const int stepsPerRevolution = 1019;

// Define the pins connected to the ULN2003 driver inputs
const int in1Pin = 14;
const int in2Pin = 12;
const int in3Pin = 13;
const int in4Pin = 15;

// Create a Stepper object
Stepper myStepper(stepsPerRevolution, in1Pin, in3Pin, in2Pin, in4Pin);

void setup() {
  // Set the motor control pins as outputs
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  // Set the motor speed (higher value means slower movement)
  myStepper.setSpeed(25); // Adjust the value as needed
}

void loop() {
  // Rotate the stepper motor one full revolution clockwise
  myStepper.step(stepsPerRevolution);

  delay(1000); // Wait for a second

  // Rotate the stepper motor one full revolution counterclockwise
  myStepper.step(-stepsPerRevolution);

  delay(1000); // Wait for a second
}
