#include <Arduino.h>

// Pin definitions
const int buttonPins[8] = {2, 3, 4, 5, 6, 7, 8, 9}; // Buttons connected to pins D2 to D9
const int ledPins[8] = {10, 11, 12, 13, A0, A1, A2, A3}; // LEDs connected to pins D10 to D13 and A0 to A3

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 bps
  for (int i = 0; i < 8; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // Initialize button pins as input with internal pull-up
    pinMode(ledPins[i], OUTPUT); // Initialize LED pins as output
  }
}

void loop() {
  byte buttonStates = 0; // Byte to hold all button states

  for (int i = 0; i < 8; i++) {
    bool buttonState = !digitalRead(buttonPins[i]); // Read button state, invert because of pull-up
    digitalWrite(ledPins[i], buttonState); // Set LED state same as button
    if (buttonState) {
      buttonStates |= (1 << i); // Set the corresponding bit in buttonStates byte
    }
  }

  Serial.write(buttonStates); // Transmit the byte of button states
  delay(100); // Simple debounce and rate control
}
