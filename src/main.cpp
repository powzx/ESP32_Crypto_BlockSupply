#include <Arduino.h>

#include "handler.h"

void setup() {
  Serial.begin(115200);

  initNetwork();
  initECCKeys();
  setTopics();

  start();
}

void loop() {
  mqttClient.loop();
  delay(500);
}
