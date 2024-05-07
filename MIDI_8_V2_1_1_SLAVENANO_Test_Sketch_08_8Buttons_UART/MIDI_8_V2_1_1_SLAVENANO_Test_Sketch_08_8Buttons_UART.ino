// Define the button and LED pins
const int buttonPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int ledPins[] = {10, 11, 12, 13, 14, 15, 16, 17};
const int numButtons = 8;
bool buttonStates[numButtons];  // Current state of each button
bool lastButtonStates[numButtons];  // Last state of each button

void setup() {
  Serial.begin(9600);
  
  // Initialize button pins as input and LED pins as output
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
    buttonStates[i] = false;
    lastButtonStates[i] = digitalRead(buttonPins[i]);
  }
}

void loop() {
  byte stateByte = 0;  // This byte will store the state of all buttons

  for (int i = 0; i < numButtons; i++) {
    bool currentReading = digitalRead(buttonPins[i]);

    // Check if button state has changed from the last reading
    if (currentReading != lastButtonStates[i]) {
      if (currentReading == LOW) {  // Assuming active-low due to external pull-up
        buttonStates[i] = !buttonStates[i];  // Toggle the state
        digitalWrite(ledPins[i], buttonStates[i]);  // Update LED state
      }
    }
    lastButtonStates[i] = currentReading;  // Save the current state as the last state

    // Set the corresponding bit in stateByte
    if (buttonStates[i]) {
      stateByte |= (1 << i);
    }
  }

  // Send the state byte
  Serial.write(stateByte);

  delay(50);  // Debounce delay
}
