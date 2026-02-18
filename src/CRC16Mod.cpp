#include "CRC16Mod.h"

// Конструктор по умолчанию
CRC16Mod::CRC16Mod() {
  value = 0xFFFF;
}

// Обновление CRC с использованием байта
void CRC16Mod::update(byte aByte) {
  uint8_t tempByte = aByte;
  for (int count = 7; count >= 0; count--) {
    bool a = value & 0x0001;
    value >>= 1;
    bool b = tempByte & 0x0001;
    tempByte >>= 1;
    if ((a ^ b) == 1) {
      value ^= 0xA001;
    }
  }
}

// Сброс CRC значения в 0
void CRC16Mod::reset() {
  value = 0xFFFF;
}

// Получить текущее значение CRC
uint16_t CRC16Mod::getValue() {
  return value;
}
