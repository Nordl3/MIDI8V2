#include <Encoder.h>
#include <ArduinoJson.h> // Include the ArduinoJson library for parsing JSON

// Define each encoder with their respective pins
Encoder stepEnc1(2, 3);
Encoder stepEnc2(4, 5);
Encoder stepEnc3(6, 7);
Encoder stepEnc4(10, 11);
Encoder stepEnc5(25, 26);
Encoder stepEnc6(27, 28);
Encoder stepEnc7(29, 30);
Encoder stepEnc8(31, 32);

// Array to hold the current position of each encoder
long encoderPositions[8];
// Array to hold button states as received from STATENANO
bool buttonStates[8];

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate for debug
  Serial1.begin(9600); // Start serial communication at 9600 baud rate for UART (change if different)
}

void loop() {
  // Read, adjust for the 4 counts per click, and store the position of each encoder
  for (int i = 0; i < 8; i++) {
    encoderPositions[i] = readEncoder(i) / 4;
  }
  
  // Check for incoming UART data
  if (Serial1.available() > 0) {
    String jsonData = Serial1.readStringUntil('\n'); // Read the JSON packet
    parseJSON(jsonData); // Custom function to parse JSON data
  }

  // Display encoder values and corresponding button states
  for (int i = 0; i < 8; i++) {
    Serial.print(encoderPositions[i]);
    Serial.print("\t");
    Serial.print(buttonStates[i] ? "ON" : "OFF");
    Serial.print("\t");
  }

  Serial.println(); // New line after each full display cycle
  delay(100); // Delay to reduce data flooding the serial monitor
}

// Function to parse JSON-like data
void parseJSON(const String& json) {
  StaticJsonDocument<200> doc; // Adjust size according to the expected JSON size
  DeserializationError error = deserializeJson(doc, json);
  if (error) {
    Serial.print("JSON parse error: ");
    Serial.println(error.c_str());
    return;
  }

  // Assuming JSON structure as {"device":"SN","states":[1,0,1,1,0,0,1,0]}
  JsonArray states = doc["states"];
  for (int i = 0; i < states.size(); i++) {
    buttonStates[i] = states[i]; // Store button state in global array
  }
}

long readEncoder(int index) {
  switch (index) {
    case 0: return stepEnc1.read();
    case 1: return stepEnc2.read();
    case 2: return stepEnc3.read();
    case 3: return stepEnc4.read();
    case 4: return stepEnc5.read();
    case 5: return stepEnc6.read();
    case 6: return stepEnc7.read();
    case 7: return stepEnc8.read();
    default: return 0;
  }
}
