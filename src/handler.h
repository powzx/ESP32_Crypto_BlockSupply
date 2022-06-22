#include <Arduino.h>

#include "epoch.h"
#include "ecc.h"

// Will be implemented to load this value using Bluetooth
char serialNum[5] = "1792";

char PREFIX[200] = "/topic/";
char INIT_TOPIC[200] = "/topic/dispatch/init";
char POST_TOPIC[200] = "/topic/dispatch/post";
char TXN_HASH_TOPIC[200] = "";
char BATCH_HASH_TOPIC[200] = "";
char TXN_SIG_TOPIC[200] = "";
char BATCH_SIG_TOPIC[200] = "";

void setTopics() {
    Serial.println("Initializing topics...");

    strcat(PREFIX, (char *)pubKeyHex);
    Serial.print("Prefix set: ");
    Serial.println(PREFIX);

    strcpy(TXN_HASH_TOPIC, PREFIX);
    strcat(TXN_HASH_TOPIC, "/txnHash");
    Serial.print("Txn Hash topic set: ");
    Serial.println(TXN_HASH_TOPIC);

    strcpy(BATCH_HASH_TOPIC, PREFIX);
    strcat(BATCH_HASH_TOPIC, "/batchHash");
    Serial.print("Batch Hash topic set: ");
    Serial.println(BATCH_HASH_TOPIC);

    strcpy(TXN_SIG_TOPIC, PREFIX);
    strcat(TXN_SIG_TOPIC, "/txnSig");
    Serial.print("Txn Sig topic set: ");
    Serial.println(TXN_SIG_TOPIC);

    strcpy(BATCH_SIG_TOPIC, PREFIX);
    strcat(BATCH_SIG_TOPIC, "/batchSig");
    Serial.print("Batch Sig topic set: ");
    Serial.println(BATCH_SIG_TOPIC);

    if (mqttClient.subscribe(TXN_HASH_TOPIC) && mqttClient.subscribe(BATCH_HASH_TOPIC)) {
        Serial.println("Subscribed to hash topics");
    } else {
        Serial.println("Subscription error, please restart");
    }
}

void handleMessage(const char* topic, uint8_t* payload, unsigned int length) {
    char *payloadHex = (char *)malloc(150);
    char *sigHex = (char *)malloc(150);
    memset(sigHex, 0, 150);
    memset(payloadHex, 0, 150);

    if (strcmp(topic, TXN_HASH_TOPIC) == 0) {
        Serial.print("Received transaction hash: ");
        Serial.println(payloadHex);
        signHash(payload, sigHex);
        mqttClient.publish(TXN_SIG_TOPIC, sigHex);
        Serial.print("Published transaction signature: ");
        Serial.println(sigHex);
    } else if (strcmp(topic, BATCH_HASH_TOPIC) == 0) {
        Serial.print("Received batch hash: ");
        Serial.println(payloadHex);
        signHash(payload, sigHex);
        mqttClient.publish(BATCH_SIG_TOPIC, sigHex);
        Serial.print("Published batch signature: ");
        Serial.println(sigHex);
    } else {
        Serial.println("No known handler for received message");
    }

    free(payloadHex);
    free(sigHex);
}

void initChip() {
    Serial.println("Initializing chip with its public key...");

    char payload[200] = "{\"publicKey\":\"";
    strcat(payload, (char *)pubKeyHex);
    strcat(payload, "\",\"key\":\"");
    strcat(payload, (char *)pubKeyHex);
    strcat(payload, "\",\"data\":\"esp32-1 test\"}"); 

    mqttClient.publish(INIT_TOPIC, payload);
}

void sendSensedData() {
    Serial.println("Sending new sensed data...");

    int temp = random(0, 20);
    char tempBuf[3];
    itoa(temp, tempBuf, 10);

    int humidity = random(20, 80);
    char humidityBuf[3];
    itoa(humidity, humidityBuf, 10);

    unsigned long currentTime = getTimeSinceEpoch();
    char currentTimeBuffer[11];
    ltoa(currentTime, currentTimeBuffer, 10);

    char payload[200] = "{\"publicKey\":\"";
    strcat(payload, (char *)pubKeyHex);
    strcat(payload, "\",\"key\":\"");
    strcat(payload, serialNum);
    strcat(payload, "\",\"data\":{\"time\":\"");
    strcat(payload, currentTimeBuffer);
    strcat(payload, "\",\"temp\":\"");
    strcat(payload, tempBuf);
    strcat(payload, "\",\"humidity\":\"");
    strcat(payload, humidityBuf);
    strcat(payload, "\"}}");

    mqttClient.publish(POST_TOPIC, payload);
}

void start() {
    mqttClient.setCallback(handleMessage);
    initChip();
}
