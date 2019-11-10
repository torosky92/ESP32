#include <Arduino.h>

#include <mqtt.h>

mqtt Iot = mqtt();

void setup() {
  Serial.begin(9600);
  Iot.begin("IOT-ESP32","DISPLAY/A");
  delay(500);
}

void loop() {
  Iot.sending("DISPLAY/A/C", "Aguila", 3);
  Serial.println("-------------");
}