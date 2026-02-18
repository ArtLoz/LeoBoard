#ifndef HELPER_H
#define HELPER_H

#include <Arduino.h>

void uint16ToBuffer(const uint16_t value, byte buffer[2]);
String toHexString(const uint8_t *data, size_t length);
void createConfigPayload(const byte sourceBuffer[], size_t sourceSize, byte resultBuffer[]);
uint16_t bytesToUint16t(byte byteOne, byte byteTwo);
uint16_t calculateCRC(const byte *data, size_t length);
void createOutputData(const uint16_t command, const byte *payload, const size_t payloadSize, byte resultBuffer[]);
void cratePolingOutputData(const uint16_t command, const byte statusWork, const byte statusSwap, const byte statusSpam, byte resultBuffer[]);
#endif // COMMANDHELPER_H