// /*
//   SKETCH 1: SAFE WHEEL CALIBRATION
//   Objective: Get the robot moving forward in a straight line.
// */

#include <Servo.h>

// --- SPEED GOVERNOR ---
// Change this to limit the robot's top speed (Range: 0 to 90)
// 90 is full speed, 30 is a safe walking pace.
int MAX_SPEED = 20; 

Servo leftMotor;
Servo rightMotor;

void setup() {
  // Connect the muscles (servos) to the brain (Arduino)
  leftMotor.attach(10);   // Pin 10
  rightMotor.attach(9);    // Pin 9
  
  leftMotor.write(90); 
  rightMotor.write(90);
  delay(1); 

  Serial.begin(9600);
  Serial.println("Robot Ready for Calibration...");
}

void loop() {
  // --- STUDENT SECTION: CALIBRATION --- CHANGE THIS!
  int leftPower = 100;  
  int rightPower = 100; 

  setMotorSpeed(leftPower, rightPower);
  
  delay(20); 
}

/**
 * setMotorSpeed helper function
 */
void setMotorSpeed(int left, int right) {
  left = constrain(left, -100, 100);
  right = constrain(right, -100, 100);

  int leftValue = map(left, -100, 100, 90 - MAX_SPEED, 90 + MAX_SPEED);
  int rightValue = map(right, -100, 100, 90 + MAX_SPEED, 90 - MAX_SPEED); 

  leftMotor.write(leftValue);
  rightMotor.write(rightValue);
}
