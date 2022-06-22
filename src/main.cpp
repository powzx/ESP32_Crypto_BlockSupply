#include <Arduino.h>

#include "handler.h"

int lastPostTime = millis();

void setup() {
  Serial.begin(115200);

  initNetwork();
  initECCKeys();
  setTopics();
  initNtp();

  start();
}

void loop() {
  mqttClient.loop();

  // send temperature data every 20 seconds
  if (millis() - lastPostTime > 20000) {
    sendSensedData();
    lastPostTime = millis();
  }

  delay(500);
}
