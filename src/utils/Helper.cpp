#include "Helper.h"
#include <CRC16Mod.h>

CRC16Mod crc;

void uint16ToBuffer(const uint16_t value, byte buffer[2])
{
    buffer[1] = value & 0xFF;
    buffer[0] = (value >> 8) & 0xFF;
}
String toHexString(const uint8_t *data, size_t length)
{
    String result = "";
    for (size_t i = 0; i < length; i++)
    {
        if (data[i] < 0x10)
            result += "0"; // ведущий 0
        result += String(data[i], HEX);
        if (i < length - 1)
            result += ""; // пробел между байтами
    }
    return result;
}
void createConfigPayload(const byte sourceBuffer[], size_t sourceSize, byte resultBuffer[]) {
    const size_t zeroBufferSize = 40-sourceSize;
    for (size_t i = 0; i < sourceSize; i++) {
      resultBuffer[i] = sourceBuffer[i];
    }
    for (size_t i = 0; i < zeroBufferSize; i++) {
      resultBuffer[sourceSize + i] = 0x00;
    }
  }
uint16_t bytesToUint16t(byte byteOne, byte byteTwo)
  {
    return (byteOne << 8) | byteTwo;
  }
uint16_t calculateCRC(const byte *data, size_t length){
    crc.reset();
    for (size_t i = 0; i < length; i++)
    {
        crc.update(data[i]);
    }
    return crc.getValue();
}
void createOutputData(const uint16_t command, const byte *payload, const size_t payloadSize, byte resultBuffer[])
{
    byte commandBuffer[2];
    byte crcBuffer[2];
    uint16ToBuffer(command, commandBuffer);
    uint16ToBuffer(calculateCRC(payload, payloadSize), crcBuffer);
    size_t index = 0;
    for (size_t i = 0; i < 2; i++)
    {
        resultBuffer[index++] = commandBuffer[i];
    }
    for (size_t i = 0; i < payloadSize; i++)
    {
        resultBuffer[index++] = payload[i];
    }
    for (size_t i = 0; i < 2; i++)
    {
        resultBuffer[index++] = crcBuffer[i];
    }
}

void cratePolingOutputData(const uint16_t command, const byte statusWork, const byte statusSwap, const byte statusSpam, byte resultBuffer[]){
    byte commandBuffer[2];
    uint16ToBuffer(command, commandBuffer);
    size_t index = 0;
    for (size_t i = 0; i < 2; i++)
    {
        resultBuffer[index++] = commandBuffer[i];
    }
    resultBuffer[index++] = statusWork;
    resultBuffer[index++] = statusSwap;
    resultBuffer[index++] = statusSpam;

}