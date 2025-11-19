/*
  distance_test.ino
  ------------------
  Test the HC-SR04 ultrasonic sensor.

  Prints distance in centimetres to the Serial Monitor.
  You should move an object in front of the robot and watch the values change.
*/

const int TRIG_PIN = 10;
const int ECHO_PIN = 9;

// Function to read distance in centimetres.
// Returns -1 if no echo is received (out of range or wiring problem).
long readDistanceCm() {
  // Ensure trigger is LOW for a short time
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10 microsecond HIGH pulse to trigger the measurement
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the time for the echo to return (in microseconds)
  // Add a timeout (e.g. 30,000 µs ≈ 5 m) to avoid blocking forever.
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // If no echo was received within timeout, return -1
  if (duration == 0) {
    return -1;
  }

  // Convert time to distance (cm)
  // Speed of sound ≈ 340 m/s ⇒ 29.1 µs per cm round-trip.
  long distanceCm = duration / 58;  // ≈ duration * 0.034 / 2

  return distanceCm;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
  Serial.println("Ultrasonic distance test");
}

void loop() {
  long d = readDistanceCm();

  if (d == -1) {
    Serial.println("distance_cm = -1 (no echo)");
  } else {
    Serial.print("distance_cm = ");
    Serial.println(d);
  }

  delay(200); // 5 readings per second
}
