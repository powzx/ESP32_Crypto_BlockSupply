#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#include "data.h"

WiFiClientSecure secureClient;
PubSubClient mqttClient(secureClient);

void initNetwork() {
    Serial.print("Connecting to ");
    Serial.println(SSID);

    WiFi.begin(SSID, PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    
    Serial.print("Connected to ");
    Serial.println(SSID);
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP().toString());

    secureClient.setCACert(CA_CRT);
    secureClient.setCertificate(CLIENT_CRT);
    secureClient.setPrivateKey(CLIENT_KEY);

    mqttClient.setServer(MQTT_SERVER, 8883);
    mqttClient.connect(id);
    Serial.print("Connected to MQTT Broker ");
    Serial.println(MQTT_SERVER);

    mqttClient.setBufferSize(300);
}
