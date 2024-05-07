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

// Variables to hold the current position of each encoder
long encoderPositions[numEncoders] = {0};

// Variable to hold button states
volatile uint8_t buttonStates;

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  Serial1.begin(9600); // Initialize UART communication at 9600 baud
}

void loop() {
  // Read encoder positions
  for (int i = 0; i < numEncoders; i++) {
    long newPosition = encoders[i].read() / 4; // Assuming each click results in 4 counts
    encoderPositions[i] = newPosition;
  }

  // Read UART for button states if available
  if (Serial1.available() > 0) {
    buttonStates = Serial1.read(); // Read a single byte that contains all button states
  }

  // Print the positions and button states in a formatted manner
  Serial.println("Encoder Positions and Button States:");
  for (int i = 0; i < numEncoders; i++) {
    Serial.print("ST");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(encoderPositions[i]);
    Serial.print(" ");
    Serial.print((buttonStates & (1 << i)) ? "ON" : "OFF"); // Check each bit for button state
    Serial.print("\t");
  }
  Serial.println();

  delay(100); // Reduce the rate of the serial output to make it readable
}
