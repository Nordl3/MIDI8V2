#include <Encoder.h>

// Define the number of encoders and their associated pins
const int numEncoders = 8;
Encoder encoders[numEncoders] = {
  Encoder(2, 3),   // Encoder 1
  Encoder(4, 5),   // Encoder 2
  Encoder(6, 7),   // Encoder 3
  Encoder(10, 11), // Encoder 4
  Encoder(25, 26), // Encoder 5
  Encoder(27, 28), // Encoder 6
  Encoder(29, 30), // Encoder 7
  Encoder(31, 32)  // Encoder 8
};

long positions[numEncoders] = {0};  // Array to store the position of each encoder
byte lastButtonStates = 0;         // Last known button states to detect changes

void setup() {
  Serial.begin(9600);   // Start serial communication at 9600 baud
  Serial1.begin(9600);  // Begin listening for UART communications
}

void loop() {
  bool updateDisplay = false;

  // Check for new button state data via UART
  if (Serial1.available() > 0) {
    byte newButtonStates = Serial1.read(); // Read the new button states byte
    if (newButtonStates != lastButtonStates) {
      lastButtonStates = newButtonStates; // Update last known states
      updateDisplay = true;               // Flag to update the display
    }
  }

  // Check each encoder and update positions
  for (int i = 0; i < numEncoders; i++) {
    long newPosition = encoders[i].read();
    if (newPosition != positions[i]) {
      positions[i] = newPosition;
      updateDisplay = true;
    }
  }

  // Update the display if necessary
  if (updateDisplay) {
    Serial.println("----");
    for (int i = 0; i < numEncoders; i++) {
      Serial.print("Enc");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(positions[i]);
      Serial.print(" |  ");
      Serial.println(lastButtonStates & (1 << i) ? "ON" : "OFF");
    }
  }

  delay(10); // Reduced delay to ensure more responsive updates
}
