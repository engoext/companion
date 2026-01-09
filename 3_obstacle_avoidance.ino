/*
  SKETCH 3: OBSTACLE AVOIDANCE
  Objective: Your robot now thinks for itself!
*/

#include <Servo.h>

// --- CONFIGURATION ---
int MAX_POWER = 35;      // Use the same speed limit from Sketch 1
int stopDistance = 25;   // The distance (cm) to trigger a turn

Servo leftMotor;
Servo rightMotor;
const int trigPin = 2;
const int echoPin = 3;

void setup() {
  leftMotor.attach(9);
  rightMotor.attach(10);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
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
    
    // Step B: Back up slightly (Prevents getting stuck)
    setMotorSpeed(-60, -60);
    delay(500);
    
    // Step C: Turn/Spin (Left -100, Right 100)
    // Adjust the delay until it makes a roughly 90-degree turn
    setMotorSpeed(-100, 100); 
    delay(700);
    
    // Step D: Quick pause to stabilize
    setMotorSpeed(0, 0);
    delay(200);

  } else {
    // --- ACT: PATH IS CLEAR ---
    // Use your calibrated straight-line speeds here
    setMotorSpeed(100, 100); 
  }
  
  delay(30); // Short delay for sensor stability
}

// --- HELPER TOOLS ---

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout for range
  return duration * 0.034 / 2;
}

void setMotorSpeed(int left, int right) {
  left = constrain(left, -100, 100);
  right = constrain(right, -100, 100);
  int leftValue = map(left, -100, 100, 90 - MAX_POWER, 90 + MAX_POWER);
  int rightValue = map(right, -100, 100, 90 + MAX_POWER, 90 - MAX_POWER);
  leftMotor.write(leftValue);
  rightMotor.write(rightValue);
}
