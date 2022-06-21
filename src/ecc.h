#include <Arduino.h>
#include <secp256k1.h>
#include <secp256k1_preallocated.h>

#include "data.h"

secp256k1_context *ctx = NULL;

uint8_t pubKey[33];
secp256k1_pubkey pubKeyObject;

void *privKeyHex;
void *pubKeyHex;

void bytesToHex(const uint8_t *data, size_t data_len, char *hex) {
    int i = 0;
    int j = 0;

    while (j < data_len) {
        hex[i] = "0123456789abcdef"[data[j] / 16];
        i++;

        hex[i] = "0123456789abcdef"[data[j] % 16];
        i++;
        j++;
    }
}

// void printHex(const uint8_t *data, size_t data_len) {
//     for(int i = 0; i < data_len; i++){
//         if (data[i] < 0x10) { 
//             Serial.print("0");
//         }
//         Serial.print(data[i], HEX);
//     }
// }

// void printlnHex(const uint8_t *data, size_t data_len) {
//     printHex(data, data_len);
//     Serial.println();
// }

void printError(const char *message) {
    Serial.print("ERROR: ");
    Serial.println(message);
    while (1) {
        // hang forever
        delay(1000);
    }
}

void initECCKeys() {

    Serial.println("Initializing Elliptic Curve ...");

    privKeyHex = malloc(100);
    pubKeyHex = malloc(100);
    memset(privKeyHex, 0, 100);
    memset(pubKeyHex, 0, 100);

    int res;
    size_t len;

    size_t contextSize = secp256k1_context_preallocated_size(SECP256K1_CONTEXT_VERIFY | SECP256K1_CONTEXT_SIGN);
    Serial.print("SECP256K1 context preallocated with size ");
    Serial.print(contextSize);
    Serial.println(" bytes");

    ctx = secp256k1_context_create(SECP256K1_CONTEXT_VERIFY | SECP256K1_CONTEXT_SIGN);
    Serial.println("SECP256K1 context created");

    bytesToHex(privKey, sizeof(privKey), (char *)privKeyHex);
    Serial.print("Private key: ");
    Serial.println((char*)privKeyHex);
    // printlnHex(privKey, sizeof(privKey));

    res = secp256k1_ec_seckey_verify(ctx, privKey);
    if (!res) { 
        printError("Private key is invalid");
    }

    res = secp256k1_ec_pubkey_create(ctx, &pubKeyObject, privKey);
    if (!res) { 
        printError("Public key computation failed");
    }

    len = sizeof(pubKey);
    secp256k1_ec_pubkey_serialize(ctx, pubKey, &len, &pubKeyObject, SECP256K1_EC_COMPRESSED);
    bytesToHex(pubKey, len, (char *)pubKeyHex);
    Serial.print("Public key: ");
    Serial.println((char *)pubKeyHex);
    // printlnHex(pubKey, len);

    res = secp256k1_ec_pubkey_parse(ctx, &pubKeyObject, pubKey, 33);
    if (res) {
        Serial.println("Key is valid");
    } else {
        Serial.println("Invalid key");
    }

    Serial.println("Elliptic curve initialized.");
}

void signHash(uint8_t *hash, char *rsHex) {
    
    Serial.println("Generating signature...");

    int res;
    size_t len;

    secp256k1_ecdsa_signature sig;
    res = secp256k1_ecdsa_sign(ctx, &sig, hash, privKey, NULL, NULL);
    if (!res) { 
        printError("Signature generation failed");
    }

    uint8_t rs[64];
    len = sizeof(rs);
    res = secp256k1_ecdsa_signature_serialize_compact(ctx, rs, &sig);
    if (!res) {
        printError("Signature serialization failed");
    }
    bytesToHex(rs, len, rsHex);
    Serial.print("Signature: ");
    Serial.println(rsHex);
    // printlnHex(rs, len);

    Serial.println("Verifying signature...");
    res = secp256k1_ecdsa_verify(ctx, &sig, hash, &pubKeyObject);
    if (res) {
        Serial.println("Signature is valid");
    } else {
        Serial.println("Invalid signature");
    }
}

void cleanContext() {
    free(privKeyHex);
    free(pubKeyHex);
    secp256k1_context_destroy(ctx);
}
