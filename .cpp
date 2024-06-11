#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int ledPin = 13;
const int buzzerPin = 12;  // Optional
const float accelThreshold = 2.0;  // Adjust based on sensitivity required
const float gyroThreshold = 300.0;  // Adjust based on sensitivity required

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize the MPU6050
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  // Set up the pins
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);  // Optional

  // Ensure LED and Buzzer are off
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);  // Optional
}

void loop() {
  // Read accelerometer and gyroscope data
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Calculate acceleration in g's and gyroscope in degrees/s
  float axg = ax / 16384.0;
  float ayg = ay / 16384.0;
  float azg = az / 16384.0;
  float gxds = gx / 131.0;
  float gyds = gy / 131.0;
  float gzds = gz / 131.0;

  // Print the values to the Serial Monitor
  Serial.print("Accel: ");
  Serial.print(axg); Serial.print(", ");
  Serial.print(ayg); Serial.print(", ");
  Serial.print(azg); Serial.print(" | ");
  Serial.print("Gyro: ");
  Serial.print(gxds); Serial.print(", ");
  Serial.print(gyds); Serial.print(", ");
  Serial.print(gzds); Serial.println();

  // Check if the values exceed the threshold
  if (abs(axg) > accelThreshold || abs(ayg) > accelThreshold || abs(azg) > accelThreshold ||
      abs(gxds) > gyroThreshold || abs(gyds) > gyroThreshold || abs(gzds) > gyroThreshold) {
    // Turn on the LED and buzzer
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);  // Optional
    Serial.println("Hazardous movement detected!");
  } else {
    // Turn off the LED and buzzer
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);  // Optional
  }

  // Add a small delay
  delay(100);
}
