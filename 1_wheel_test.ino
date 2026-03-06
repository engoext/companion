// /*
//   SKETCH 1: SAFE WHEEL CALIBRATION
//   Objective: Get the robot moving forward in a straight line.
// */

// #include <Servo.h>

// Servo leftMotor;
// Servo rightMotor;

// void setup() {
//   // Connect the muscles (servos) to the brain (Arduino)
//   leftMotor.attach(10);   // Left servo on Pin D9
//   rightMotor.attach(9); // Right servo on Pin D10
  
//   // NECESSARY CHANGE 1: Arm the servos with a stop signal and a delay.
//   // This prevents them from "spamming" or rotating unpredictably at power-up.
//   leftMotor.write(90); 
//   rightMotor.write(90);
//   delay(1); 

//   // Start Serial so we can see what's happening
//   Serial.begin(9600);
//   Serial.println("Robot Ready for Calibration...");
// }

// void loop() {
//   // --- STUDENT SECTION: CALIBRATION ---
//   int leftPower = 100;  
//   int rightPower = 100; 

//   setMotorSpeed(leftPower, rightPower);
  
//   // NECESSARY CHANGE 2: The "Breathing Room" delay.
//   // Without this, the Nano R4 sends signals too fast for the servos to process.
//   delay(20); 
//   // ------------------------------------
// }

// /**
//  * setMotorSpeed helper function
//  * Converts -100 to 100 into Servo Degrees.
//  */
// void setMotorSpeed(int left, int right) {
//   left = constrain(left, -100, 100);
//   right = constrain(right, -100, 100);

//   // NECESSARY CHANGE 3: Full Torque Mapping & Direction Fix
//   // We use 0-180 to ensure the robot has the strength to move.
//   // Mapping adjusted so that 100 = Forward (Left 180, Right 0).
//   int leftValue = map(left, -100, 100, 0, 180);
//   int rightValue = map(right, -100, 100, 180, 0); 

//   leftMotor.write(leftValue);
//   rightMotor.write(rightValue);
// }

/*
  SKETCH 1: SAFE WHEEL CALIBRATION
  Objective: Get the robot moving forward in a straight line.
*/

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
