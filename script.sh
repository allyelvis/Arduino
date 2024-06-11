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
