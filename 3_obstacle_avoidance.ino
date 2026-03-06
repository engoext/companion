/*
  SKETCH 3: OBSTACLE AVOIDANCE
  Objective: Your robot now thinks for itself!
*/

#include <Servo.h>

// --- CONFIGURATION ---
int MAX_POWER = 90;      // 0 to 90 (30 is safe, 90 is fast)
int stopDistance = 25;   // The distance (cm) to trigger a turn

Servo leftMotor;
Servo rightMotor;
const int trigPin = 2;
const int echoPin = 3;

void setup() {
  // Use the working Pins from Sketch 1
  leftMotor.attach(10); 
  rightMotor.attach(9);
  
  // Arm the servos with a stop signal
  leftMotor.write(90); 
  rightMotor.write(90);
  delay(1); 

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);
  Serial.println("Obstacle Avoidance System Active...");
}

void loop() {
  // 1. SEE: Get current distance
  int distance = getDistance();

  // 2. THINK: Is there something in the way?
  if (distance > 0 && distance < stopDistance) {
    
    // --- ACT: OBSTACLE DETECTED ---
    Serial.println("Obstacle! Choosing new path...");
    
    // Step A: Full Stop
    setMotorSpeed(0, 0);   
    delay(400);
    
    // Step B: Back up slightly
    setMotorSpeed(-60, -60);
    delay(500);
    
    // Step C: Turn/Spin 
    setMotorSpeed(-100, 100); 
    delay(700);
    
    // Step D: Quick pause to stabilize
    setMotorSpeed(0, 0);
    delay(200);

  } else {
    // --- ACT: PATH IS CLEAR ---
    // Robot drives forward
    setMotorSpeed(100, 100); 
  }
  
  delay(20); // The "Breathing Room" delay for Nano R4 stability
}

// --- HELPER TOOLS ---

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000); 
  return duration * 0.034 / 2;
}

void setMotorSpeed(int left, int right) {
  left = constrain(left, -100, 100);
  right = constrain(right, -100, 100);

  // Correct Mapping from your working Sketch 1
  // leftPower 100 -> 90 + MAX | rightPower 100 -> 90 - MAX
  int leftValue = map(left, -100, 100, 90 - MAX_POWER, 90 + MAX_POWER);
  int rightValue = map(right, -100, 100, 90 + MAX_POWER, 90 - MAX_POWER);

  leftMotor.write(leftValue);
  rightMotor.write(rightValue);
}
