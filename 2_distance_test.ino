/*
  SKETCH 2: ULTRASONIC EYE TEST
*/

const int trigPin = 2;
const int echoPin = 3;

void setup() {
  Serial.begin(9600); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  int distance = duration * 0.034 / 2;

  if (distance > 0 && distance < 400) { 
    Serial.print("Distance:"); 
    Serial.print(distance);
    Serial.print(",");
    Serial.print("Threshold:");
    Serial.println(20);        
  }

  delay(50); 
}
