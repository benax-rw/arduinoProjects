#include <Stepper.h>

// Define the number of steps per revolution of your stepper motor (28BYJ-48)
const int stepsPerRevolution = 2048; // 8 steps per full revolution, and the motor has a 64:1 gear reduction

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
}

void loop() {
  // Rotate the stepper motor 180 degrees clockwise (in full steps)
  for (int i = 0; i < stepsPerRevolution / 2; i++) {
    myStepper.step(1);
    delay(5); // Adjust the delay as needed for your motor speed
  }

  // Wait for a second
  delay(1000);

  // Rotate the stepper motor 180 degrees counterclockwise (in full steps)
  for (int i = 0; i < stepsPerRevolution / 2; i++) {
    myStepper.step(-1);
    delay(5); // Adjust the delay as needed for your motor speed
  }

  // Wait for a second
  delay(1000);
}
