#include <Arduino.h>

const int buttonPins[] = {2, 3, 4, 5, 6, 7, 8, 9}; // Button pins D2 to D9
const int ledPins[] = {10, 11, 12, 13, 14, 15, 16, 17}; // LED pins from D10 to D17
const int numButtons = sizeof(buttonPins) / sizeof(buttonPins[0]);
int lastButtonState[numButtons]; // Array to store the last state of each button
int ledState[numButtons]; // Array to store the current state of each LED

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT); // Set each button pin as input (assuming external pull-ups)
    pinMode(ledPins[i], OUTPUT); // Set each LED pin as output
    lastButtonState[i] = HIGH; // Initialize the last button state as HIGH (unpressed)
    ledState[i] = LOW; // Initialize the LED state as OFF
    digitalWrite(ledPins[i], ledState[i]); // Set initial LED state
  }
}

void loop() {
  bool updateNeeded = false; // Flag to track if any LED state has changed

  for (int i = 0; i < numButtons; i++) {
    int currentButtonState = digitalRead(buttonPins[i]); // Read the current state of the button
    if (currentButtonState != lastButtonState[i] && currentButtonState == LOW) {
      // Only toggle the LED if the button goes from HIGH to LOW (button pressed)
      ledState[i] = !ledState[i]; // Toggle the state of the LED
      digitalWrite(ledPins[i], ledState[i]); // Update the LED state
      updateNeeded = true; // Mark that an update is needed
    }
    lastButtonState[i] = currentButtonState; // Update the last known state of the button
  }

  if (updateNeeded) {
    sendStateUpdate(); // Send updated LED states over UART
  }
}

void sendStateUpdate() {
  Serial.print("SN:"); // Identifier for STATENANO
  for (int i = 0; i < numButtons; i++) {
    Serial.print(ledState[i]); // Send each LED's state as part of the bit string
  }
  Serial.println(); // End of message
}
