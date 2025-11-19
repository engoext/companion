/*
  avoid_starter.ino
  ------------------
  Combine wheel control + ultrasonic distance.

  Behaviour:
    - Robot drives forward.
    - If an obstacle is closer than stopDistanceCm:
        * Stop briefly,
        * Turn right for turnTimeMs,
        * Then continue forward.

  You should:
    - Tune leftForwardSpeed / rightForwardSpeed (carry over from wheel_test).
    - Tune stopDistanceCm and turnTimeMs.
    - Optional challenge: add a "caution zone" or change the turning behaviour.
*/

#include <Servo.h>

// Pin assignments
const int LEFT_SERVO_PIN  = 5;
const int RIGHT_SERVO_PIN = 6;
const int TRIG_PIN        = 10;
const int ECHO_PIN        = 9;

// Servo objects
Servo leftServo;
Servo rightServo;

// Tunable constants
int leftForwardSpeed  = 110;  // copy the best values found in wheel_test.ino
int rightForwardSpeed = 70;   // copy the best values found in wheel_test.ino

int stopDistanceCm = 20;      // how close is "too close" (in cm)
int turnTimeMs     = 600;     // how long to turn when blocked (in ms)

// Helper: read distance in cm, or -1 if no echo
long readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return -1;  // no echo
  }

  long distanceCm = duration / 58;
  return distanceCm;
}

// Movement helper functions
void driveForward() {
  leftServo.write(leftForwardSpeed);
  rightServo.write(rightForwardSpeed);
}

void driveStop() {
  leftServo.write(90);
  rightServo.write(90);
}

// Simple turn functions (pivot turns by driving one wheel)
void driveTurnRight() {
  leftServo.write(leftForwardSpeed);  // left wheel forward
  rightServo.write(90);               // right wheel stopped
}

void driveTurnLeft() {
  leftServo.write(90);                // left wheel stopped
  rightServo.write(rightForwardSpeed);// right wheel forward
}

void setup() {
  // Attach servos
  leftServo.attach(LEFT_SERVO_PIN);
  rightServo.attach(RIGHT_SERVO_PIN);

  // Set up ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Optional: start Serial for debugging
  Serial.begin(9600);
  Serial.println("Obstacle avoidance starter");
  
  driveStop();
  delay(1000);
}

void loop() {
  long distance = readDistanceCm();

  // Optional debug print
  if (distance == -1) {
    Serial.println("distance_cm = -1 (no echo)");
  } else {
    Serial.print("distance_cm = ");
    Serial.println(distance);
  }

  // Core logic:
  // If we have a valid distance and it's closer than stopDistanceCm, react.
  if (distance > 0 && distance < stopDistanceCm) {
    // Too close: stop and turn
    driveStop();
    delay(200);

    // Turn right for a fixed time
    driveTurnRight();
    delay(turnTimeMs);

    // Stop briefly before moving again
    driveStop();
    delay(200);
  } else {
    // Safe: drive forward
    driveForward();
  }

  // Small delay to avoid spamming the sensor
  delay(50);
}
