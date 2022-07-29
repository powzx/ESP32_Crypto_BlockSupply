## Introduction
This guide will bring you through the setting up of the ESP32 microcontroller for the BlockSupply application.

## Development Environment
VS Code with PlatformIO extension installed.

## Hardware
DOIT ESP32 DEVKIT V1 on the Arduino framework.

## Key Generation

1. Generate a random valid private key on the secp256k1 ECDSA elliptic curve [here](https://paulmillr.com/noble/).

![](docs/images/key_generation.png)

2. Copy the 64-character hexadecimal representation of the private key as an array of bytes `privKey` as shown in data.h below.

3. Take note of the 66-character hexadecimal representation of the public key as shown in the '33b hex' field as you may need it to set policies as on-chain settings on the Sawtooth network later on.

## Setting up and getting started
1. Fork the repository and clone into your computer.
2. Navigate to the ESP32_Crypto_BlockSupply directory.
3. Open the project on VS Code.
4. Under the src folder, create a new file "data.h".
5. Set the following constants in data.h:
- `static const char *SSID`: SSID of the network it should connect to
- `static const char *PASSWORD`: Password of the network
- `static const char *MQTT_SERVER`: IP address of the machine running the MQTT broker
- `static const char *id`: Identifier for the ESP32
- `static const uint8_t privKey[]`: Valid private key on the secp256k1 elliptic curve
- `static const char *serialNum`: Serial number which its sensed data will be sent from
- `static const char *CA_CRT`: Certificate Authority of the MQTT broker
- `static const char *CLIENT_KEY`: Client private key of the MQTT broker
- `static const char *CLIENT_CRT`: Client certificate of the MQTT broker

Below shows a sample of data.h:
```
#pragma once

static const char *SSID = "SIOT_TEST";
static const char *PASSWORD = "yFly@S10T";
static const char *MQTT_SERVER = "192.168.11.109";

static const char *id = "ESP32-1";

static const uint8_t privKey[] = {
    0xee, 0x7f, 0x7f, 0x2e, 0xa6, 0x3f, 0x66, 0x10,
    0xef, 0xdd, 0x52, 0x24, 0xea, 0x7b, 0x80, 0xf1,
    0xfd, 0xe7, 0x96, 0x8a, 0x70, 0x3d, 0x04, 0xd8,
    0xf2, 0xaa, 0x2f, 0xbb, 0x9d, 0x28, 0x87, 0xe7
};

static const char *serialNum = "8874";

static const char *CA_CRT = "-----BEGIN CERTIFICATE-----\n" \
"MIID2zCCAsOgAwIBAgIUQPVEvqYdUiCmwf6hOHRrGzBcO18wDQYJKoZIhvcNAQEL\n" \
"BQAwfTELMAkGA1UEBhMCU0cxEjAQBgNVBAgMCVNpbmdhcG9yZTESMBAGA1UEBwwJ\n" \
"U2luZ2Fwb3JlMRAwDgYDVQQKDAdHb3ZUZWNoMRswGQYDVQQLDBJTSU9UX0Jsb2Nr\n" \
"Y2hhaW5fQ0ExFzAVBgNVBAMMDjE5Mi4xNjguMTEuMTA5MB4XDTIyMDYxMzAxNDky\n" \
"MFoXDTMyMDYxMDAxNDkyMFowfTELMAkGA1UEBhMCU0cxEjAQBgNVBAgMCVNpbmdh\n" \
"cG9yZTESMBAGA1UEBwwJU2luZ2Fwb3JlMRAwDgYDVQQKDAdHb3ZUZWNoMRswGQYD\n" \
"VQQLDBJTSU9UX0Jsb2NrY2hhaW5fQ0ExFzAVBgNVBAMMDjE5Mi4xNjguMTEuMTA5\n" \
"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA67FbVcNie2o7R+XlvuRH\n" \
"qM4cqCYb1cVRVZi03ilF9WRs1zKeWQZz+ry4s1o3zHAgfpksk540jORahpqqIiQE\n" \
"e1UXc3Jx+UdxwIDHmlD5g40D5FNxH/h6Q/P5VscytBqbEme0DAT9tLsqgwNWFNqU\n" \
"1BKvttBE/YdAHjl1FSnCAptFBmViPFmrGciBz9Psaq/0mivZ2AVC5vCkiI9X7hLz\n" \
"X9W4gqoqcxmKel4Bf9gMBqqIP45QVuH1R4Ax58HEeVA9k0rBdfRd407jeK6rzQju\n" \
"8La2zspYXkcgdWs/dzH3d1me0+6cLH3Cj9bs2fLTa8eMbymRvybR8E680K8AA9YU\n" \
"nwIDAQABo1MwUTAdBgNVHQ4EFgQU8eGOTnDk9XxXff+al/q7BNI+Ll0wHwYDVR0j\n" \
"BBgwFoAU8eGOTnDk9XxXff+al/q7BNI+Ll0wDwYDVR0TAQH/BAUwAwEB/zANBgkq\n" \
"hkiG9w0BAQsFAAOCAQEAUml2UcOg6P9jKvw6z18+CJN49qGoogsXKn+sZwG9jhW3\n" \
"bZSeCjZGqmcAs8a8tbBv9Cy/yFEHB9qohbiM6loX0Bh6OH78ierd0Txirrzi0eiV\n" \
"DLbhfLZe12dGLxMZ1ay00YBA7OzlNY2JufJ0lAce6q1o/mXwKUh2Qb6ODwb10c27\n" \
"H8a2YvajFdTM2XZXR9WyI7l+1j/UQjDt96DHHS8vEIiouyDZtqgXFHJmjrCILNBy\n" \
"+s+THfm1+awNa2utT7sqevGguqu2JcOp7XEkHZkNmRphy8Qb3p4zxNfeK7Dde9dT\n" \
"0rVpRDt00jrcRB91/zT0aW93J6W6CALLArRcDbmOQg==\n" \
"-----END CERTIFICATE-----\n";

static const char *CLIENT_KEY = "-----BEGIN PRIVATE KEY-----\n" \
"MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDl5MjX8SVW33Gf\n" \
"xgAtmj8/88VPOr7IKFny7OkcEYiSN+vOylvBYTturWC3/9s1UXbVp4cz+S3b7/Ee\n" \
"yaZImUSPMRm9Q85rrSB63VN+2C8/R0QenA+0/nycDzfSjqZsfF3ajuys4EpjhmO7\n" \
"hPQblXR4WuePHeyqlpZqCM/zXewOODuhEu0T9jOnBmbBH6dNlB3YLpRhKRjf4l1G\n" \
"XXK5nCz1gIEL4yyq3zUDqsuNIPxglNtHqVsJgSN60QjHL6VcCjiOSXpP+8ByOeWM\n" \
"Jqq+RjWkC+JjKtmDNy1jeSyaSD33oVSWuEiHJwEC/PPT7xErXhw+I3xm7jJ5WxPh\n" \
"F2zSQu3DAgMBAAECggEAAiLjHuaVwz3mT2bGn6XcSprYTYktNqzxUQmUjPc4vqsY\n" \
"XN6ShbSCmd+wk2UkQ1WTdh7NadU58N5E7lVPX0NVWMNLCvAzXdrI/3tJCFe38K2X\n" \
"23T1zGfE/qpBiYpbz4xETwCfAGhBKLWZ/acZoZv87hViK3lKtrcZhLi6Pfe0dtlY\n" \
"ai/2R0kRafIyX/PDY6DA01Jd/CXbjcBpKOPz3k9IrIQT6KrUT48EUfk8LBop/6AR\n" \
"gpoCEsekoUC5eIqU0T8gTxo1pGMzMVRkhJLVxrwsLEY+RGVqIDjlQAQvECGi9Hqb\n" \
"SDQiGX63Fpa5/uy0aW/duGLzTnL77rLKQ0xNU87YoQKBgQD1tIijUl/ukn9RKGZO\n" \
"UGunstKLMefdEE5P8eQiE+bpBoxSGcz7384UrYjzbYomPZHFSfEhEsg+ov2HnERj\n" \
"XeWA7XylA5euhYjId1iK5WNHLDD3ooUSXYwy31klxMAn5Y7ePNJnTgsJnqayCCYD\n" \
"iwYJ9s7bpuf6BOiyQjU6cDMN0QKBgQDvhqeEgLSpimR610zAO7tluGetVFASW/5w\n" \
"1DdrcK20rKQi3MIgqAoH9aLVdZ8zi6dj5YqLLr/eKTowWLdnDo+tBeOj3XtdyY5J\n" \
"p1zmcDztcIi4Clg2RnJzngFOlVe1VsZ6NtVbtFpa48jFGGrAOGXgkd956K1dKOX/\n" \
"OBP09swDUwKBgFY5x+XA58eag7Gggt6i3FTarYaJufvbWBA4LD5FS7ilQqMhSM1v\n" \
"iiu5hqEe5OdsnfZlb4iSxdEtc9meXmWcswjezuo964IkfI8VSu5bd86nVHvi/d4n\n" \
"FCdaODfH50NZDR0yrQfx3G/AzHEX6Pc/V5wxkACHf0s/Y8YC9BkQ/OmxAoGBAO7m\n" \
"qTKZhJgNNobnMuARM6oTMSVKEMsfAjrbD6OTsU2hW9yBvwX/VHH3579sH6uzwPL8\n" \
"QSDtMeWNzUHnWpXpihgS5afNAnzayZZg3WHh1IMmWNbnSnBn90Ol9rvAbMirki7X\n" \
"fhqHWg+JXfhnkCHEnqhMFk9raW6fmjbiYdVUSsuNAoGAHLgJbHnxlmer9RJB+2NP\n" \
"jbYcHlCVt07+kauj27/D0cVAaP5GN0V53aUGXo+CNrO5gAWZD8SDKgayg+CnwzFO\n" \
"ef5WGXy4z4GMfgvGC1QTogVpGIEkGGugm9EhqHi1xCmI9A9s83iTWV2+K4/YIEiR\n" \
"NQK/sTf1e1h4Ty0c3NgniwQ=\n" \
"-----END PRIVATE KEY-----\n";

static const char *CLIENT_CRT = "-----BEGIN CERTIFICATE-----\n" \
"MIIDhjCCAm4CFA83U/X4+T5w3p0GbuQKMjSit1C9MA0GCSqGSIb3DQEBCwUAMH0x\n" \
"CzAJBgNVBAYTAlNHMRIwEAYDVQQIDAlTaW5nYXBvcmUxEjAQBgNVBAcMCVNpbmdh\n" \
"cG9yZTEQMA4GA1UECgwHR292VGVjaDEbMBkGA1UECwwSU0lPVF9CbG9ja2NoYWlu\n" \
"X0NBMRcwFQYDVQQDDA4xOTIuMTY4LjExLjEwOTAeFw0yMjA2MTMwMTUyNDdaFw0z\n" \
"MjA2MTAwMTUyNDdaMIGBMQswCQYDVQQGEwJTRzESMBAGA1UECAwJU2luZ2Fwb3Jl\n" \
"MRIwEAYDVQQHDAlTaW5nYXBvcmUxEDAOBgNVBAoMB0dvdlRlY2gxHzAdBgNVBAsM\n" \
"FlNJT1RfQmxvY2tjaGFpbl9DbGllbnQxFzAVBgNVBAMMDjE5Mi4xNjguMTEuMTA5\n" \
"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA5eTI1/ElVt9xn8YALZo/\n" \
"P/PFTzq+yChZ8uzpHBGIkjfrzspbwWE7bq1gt//bNVF21aeHM/kt2+/xHsmmSJlE\n" \
"jzEZvUPOa60get1TftgvP0dEHpwPtP58nA830o6mbHxd2o7srOBKY4Zju4T0G5V0\n" \
"eFrnjx3sqpaWagjP813sDjg7oRLtE/YzpwZmwR+nTZQd2C6UYSkY3+JdRl1yuZws\n" \
"9YCBC+Msqt81A6rLjSD8YJTbR6lbCYEjetEIxy+lXAo4jkl6T/vAcjnljCaqvkY1\n" \
"pAviYyrZgzctY3ksmkg996FUlrhIhycBAvzz0+8RK14cPiN8Zu4yeVsT4Rds0kLt\n" \
"wwIDAQABMA0GCSqGSIb3DQEBCwUAA4IBAQDPPEWMgiZYugIASELOSRYF4CVOIhwW\n" \
"XoXDvaJ4BPWqpNZEadGqTkFa8hT9+rujiI8Qil9jb7pDtHNgdsyG34XSweykZOvo\n" \
"6wGsCTnkXZ0JROgIl2RLO5PG8mJl/t690tY3uzXPahujAxmNZdFHsFo+uIobE3aq\n" \
"bNp9UlOXh+YeW8bjsSayDRFxwBZ5mA1sijAcZ/DOzjsrPfruatDwA7HpagI/YrXx\n" \
"KcpcGnh7/CvtoWVAh5NJlTy3gzH31lyeYc8O8J9pciz1gvJ3jj0LS282k7FoZgyq\n" \
"xINwMfrTN3UEa5lLdpCZ3PlsvSRJzBULN11Bw8dP2M0kVRuH7lLzuvDJ\n" \
"-----END CERTIFICATE-----\n";
```

4. Build the project.
5. Connect the ESP32 to your computer and start the serial monitor.
6. Upload the project to the ESP32 and observe the serial monitor. You may view the expected output below:

```
Connected to MQTT Broker 192.168.11.109
Initializing Elliptic Curve ...
SECP256K1 context preallocated with size 704 bytes
SECP256K1 context created
Private key: bdb51a16eb6460ec16f84d7b6f19e20d9b9ab558fa0e9ae4bb493ef779f14055
Public key: 020c4a51e895deb4903ca0641b28f9887b8013604310654a34b35407d336d85c8d
Key is valid
Elliptic curve initialized.
Initializing topics...
Prefix set: /topic/020c4a51e895deb4903ca0641b28f9887b8013604310654a34b35407d336d85c8d
Txn Hash topic set: /topic/020c4a51e895deb4903ca0641b28f9887b8013604310654a34b35407d336d85c8d/txnHash
Batch Hash topic set: /topic/020c4a51e895deb4903ca0641b28f9887b8013604310654a34b35407d336d85c8d/batchHash
Txn Sig topic set: /topic/020c4a51e895deb4903ca0641b28f9887b8013604310654a34b35407d336d85c8d/txnSig
Batch Sig topic set: /topic/020c4a51e895deb4903ca0641b28f9887b8013604310654a34b35407d336d85c8d/batchSig
Subscribed to hash topics
Initializing chip with its public key...
```

## Useful Links
[Setting up PlatformIO for ESP32](https://randomnerdtutorials.com/vs-code-platformio-ide-esp32-esp8266-arduino/)

[Secp256k1 ECDSA Key Generator](https://paulmillr.com/noble/)