void setup() {
  Serial1.begin(9600);  // Initialize communication with Arduino Nano
  Serial.begin(9600);   // Initialize the serial monitor to print states
}

void loop() {
  // Process all available serial data
  while (Serial1.available() > 0) {
    byte stateByte = Serial1.read();  // Read the byte from Nano

    // Immediately process and display each button state
    Serial.println("Button States:");
    for (int i = 0; i < 8; i++) {
      Serial.print("Button ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(stateByte & (1 << i) ? "ON" : "OFF");
    }
  }
  // No delay here, remove or keep it very minimal if necessary
  delay(10); // Short delay to stabilize output and avoid serial monitor flooding
}
