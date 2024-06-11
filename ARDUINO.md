# Hazardous Movement Detection System

This project uses an Arduino with an MPU6050 sensor to detect hazardous or malicious movements and trigger alerts to protect someone in danger. The system lights up an LED and optionally sounds a buzzer when such movements are detected.

## Components

- Arduino Uno
- MPU6050 (Accelerometer and Gyroscope sensor)
- LED
- Buzzer (optional)
- Resistor (220Ω for LED)
- Breadboard and Jumper Wires

## Setup

### Connecting the Components

1. **MPU6050:**
   - VCC to 5V
   - GND to GND
   - SCL to A5 (or SCL pin on some Arduino boards)
   - SDA to A4 (or SDA pin on some Arduino boards)

2. **LED:**
   - Long leg (anode) to pin 13 (through a 220Ω resistor)
   - Short leg (cathode) to GND

3. **Buzzer (optional):**
   - Positive terminal to pin 12
   - Negative terminal to GND

### Arduino Code

1. Open the Arduino IDE.
2. Copy the following Arduino code and paste it into the IDE:

    ```cpp
    #include <Wire.h>
    #include <MPU6050.h>

    MPU6050 mpu;

    const int ledPin = 13;
    const int buzzerPin = 12;  // Optional
    const float accelThreshold = 2.0;  // Adjust based on sensitivity required
    const float gyroThreshold = 300.0;  // Adjust based on sensitivity required

    void setup() {
      Serial.begin(9600);
      Wire.begin();
      mpu.initialize();
      if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed");
        while (1);
      }
      pinMode(ledPin, OUTPUT);
      pinMode(buzzerPin, OUTPUT);  // Optional
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);  // Optional
    }

    void loop() {
      int16_t ax, ay, az, gx, gy, gz;
      mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      float axg = ax / 16384.0;
      float ayg = ay / 16384.0;
      float azg = az / 16384.0;
      float gxds = gx / 131.0;
      float gyds = gy / 131.0;
      float gzds = gz / 131.0;

      Serial.print("Accel: ");
      Serial.print(axg); Serial.print(", ");
      Serial.print(ayg); Serial.print(", ");
      Serial.print(azg); Serial.print(" | ");
      Serial.print("Gyro: ");
      Serial.print(gxds); Serial.print(", ");
      Serial.print(gyds); Serial.print(", ");
      Serial.print(gzds); Serial.println();

      if (abs(axg) > accelThreshold || abs(ayg) > accelThreshold || abs(azg) > accelThreshold ||
          abs(gxds) > gyroThreshold || abs(gyds) > gyroThreshold || abs(gzds) > gyroThreshold) {
        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH);  // Optional
        Serial.println("Hazardous movement detected!");
      } else {
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW);  // Optional
      }
      delay(100);
    }
    ```

3. Upload the code to your Arduino board.

### Bash Script

1. Create a Bash script to read the serial output from the Arduino and take further actions.

    ```bash
    #!/bin/bash

    # Define the serial port where the Arduino is connected
    SERIAL_PORT="/dev/ttyACM0"
    BAUD_RATE="9600"

    # Open the serial port and read the data
    cat $SERIAL_PORT | while read LINE; do
      echo $LINE
      # Check if hazardous movement is detected
      if [[ $LINE == *"Hazardous movement detected!"* ]]; then
        echo "Warning: Hazardous movement detected!"
        # Add your custom actions here, e.g., sending an alert
        # Example: Trigger an external script
        # ./trigger_alarm.sh
      fi
    done
    ```

2. Ensure the script has execute permissions:

    ```bash
    chmod +x script.sh
    ```

3. Run the script:

    ```bash
    ./script.sh
    ```

## Usage

- Connect the components as described in the setup section.
- Upload the Arduino code to the Arduino Uno.
- Run the Bash script on your computer to monitor hazardous movements.
- If hazardous movements are detected, the LED will light up, and the buzzer will sound (if connected). The Bash script will also print a warning message.

## Customization

- Adjust the `accelThreshold` and `gyroThreshold` values in the Arduino code to change the sensitivity of the movement detection.
- Modify the Bash script to perform additional actions when hazardous movements are detected (e.g., send an alert, log data, etc.).

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements

- The MPU6050 library used in this project.
- Arduino community for resources and support.
