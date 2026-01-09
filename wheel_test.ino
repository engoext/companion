/*
  SKETCH 1: EASY WHEEL CALIBRATION
  Objective: Get the robot moving forward in a straight line using 0-100 power levels.
*/

#include <Servo.h>

// 1. SETTINGS (Teachers: Adjust MAX_POWER here to slow down the whole class)
int MAX_POWER = 10; // 100% power in the code will only be 30% speed in real life.

Servo leftMotor;
Servo rightMotor;

void setup() {
  leftMotor.attach(9);
  rightMotor.attach(10);
  
  // Start Serial so we can see what's happening
  Serial.begin(9600);
  Serial.println("Robot Starting...");
}

void loop() {
  // --- STUDENT SECTION: CALIBRATION ---
  // Goal: Change these numbers until your robot drives perfectly straight!
  // Range: -100 (Full Reverse) to 100 (Full Forward). 0 is Stop.
  
  int leftPower = 100;  
  int rightPower = 100; 

  setMotorSpeed(leftPower, rightPower);
  // ------------------------------------
}

/**
 * setMotorSpeed helper function
 * Converts -100 to 100 into Servo Degrees (0-180)
 * and handles the "mirroring" of the motors.
 */
void setMotorSpeed(int left, int right) {
  // 1. Constrain inputs to -100 to 100 range for safety
  left = constrain(left, -100, 100);
  right = constrain(right, -100, 100);

  // 2. Map the -100 to 100 range to our MAX_POWER limit
  // Instead of 0-180, we use (90 - MAX) to (90 + MAX)
  int leftValue = map(left, -100, 100, 90 - MAX_POWER, 90 + MAX_POWER);
  int rightValue = map(right, -100, 100, 90 + MAX_POWER, 90 - MAX_POWER); 
  // Note: 'rightValue' is inverted (90+ to 90-) because it's on the other side!

  // 3. Send the command to the motors
  leftMotor.write(leftValue);
  rightMotor.write(rightValue);
}
