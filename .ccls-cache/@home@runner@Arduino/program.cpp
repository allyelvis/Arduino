// Define pins
const int trigPin = 9;
const int echoPin = 10;
const int brakePin = 2;
const int motorPin = 3;

// Define constants
const int safeDistance = 30; // Safe distance in centimeters

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Define pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(brakePin, OUTPUT);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // Send a pulse to the sensor to trigger a reading
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse from the echo pin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  int distance = duration * 0.034 / 2;

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Decision making
  if (distance <= safeDistance) {
    // Object detected, take action
    digitalWrite(brakePin, HIGH); // Apply brake
    digitalWrite(motorPin, LOW); // Stop motor
    Serial.println("Object detected! Applying brake.");
  } else {
    // No object detected, continue process
    digitalWrite(brakePin, LOW); // Release brake
    digitalWrite(motorPin, HIGH); // Continue process
    Serial.println("No object detected. Continuing process.");
  }

  // Delay before next reading
  delay(1000);
}
