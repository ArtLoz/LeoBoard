#ifndef CRC16MOD_H
#define CRC16MOD_H

#include <Arduino.h>

class CRC16Mod {
  public:
    // Конструктор по умолчанию
    CRC16Mod();

    // Обновление CRC с использованием байта
    void update(byte aByte);

    // Сброс CRC значения в 0
    void reset();

    // Получить текущее значение CRC
    uint16_t getValue();

  private:
    // Текущее значение CRC
    uint16_t value;
};

#endif
