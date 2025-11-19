/*
  wheel_test.ino
  ----------------
  Test and calibrate the two continuous-rotation servos.
  The robot will drive forward forever after a brief stop of 1 second upon starting.

  You should edit leftForwardSpeed and rightForwardSpeed so that the
  robot drives as straight as possible.
*/

#include <Servo.h>

// Pin assignments
const int LEFT_SERVO_PIN  = 5;
const int RIGHT_SERVO_PIN = 6;

// Create servo objects for each wheel
Servo leftServo;
Servo rightServo;

// Servo speed values
// For most continuous-rotation servos: 90 = stop, >90 one direction, <90 opposite.
// TUNE THESE!
int leftForwardSpeed  = 110;  // try changing by +/- 5 or 10
int rightForwardSpeed = 70;   // try changing by +/- 5 or 10

// Helper functions
void driveForward() {
  leftServo.write(leftForwardSpeed);
  rightServo.write(rightForwardSpeed);
}

void driveStop() {
  leftServo.write(90);  // stop value
  rightServo.write(90); // stop value
}

void setup() {
  // Attach servos to their pins
  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);

  // Start stopped
  driveStop();

  // Small delay before starting
  delay(1000);
}

void loop() {
  // Drive forward
  driveForward();
  // Repeat forever
}
