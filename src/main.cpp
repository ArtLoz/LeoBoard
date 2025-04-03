#include <Arduino.h>



void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello, loop ESP32!");
  delay(1000);
}
