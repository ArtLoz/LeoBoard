#include "EEPROMConfig.h"

void EEPROMConfig::saveConfig(const Config &config) {
  int address = EEPROM_START_ADDRESS;

  EEPROM.write(address++, config.windowCount);
  EEPROM.write(address++, config.key1);
  EEPROM.write(address++, config.Key2);
  EEPROM.write(address++, config.Key3);
  EEPROM.write(address++, config.Key4);
  EEPROM.put(address, config.windowsSwapDelay), address += sizeof(uint16_t);
  EEPROM.put(address, config.spamDelay), address += sizeof(uint16_t);
  EEPROM.put(address, config.delayAfterInput), address += sizeof(uint16_t);
  EEPROM.write(address++, config.statusWork ? 1 : 0);
  EEPROM.write(address++, config.statusSpam ? 1 : 0);
  EEPROM.write(address++, config.statusSwap ? 1 : 0);
  EEPROM.write(address++, config.keyCode);
}

Config EEPROMConfig::loadConfig() {
  int address = EEPROM_START_ADDRESS;

  Config config;
  
  config.windowCount = EEPROM.read(address++);
  config.key1 = EEPROM.read(address++);
  config.Key2 = EEPROM.read(address++);
  config.Key3 = EEPROM.read(address++);
  config.Key4 = EEPROM.read(address++);
  EEPROM.get(address, config.windowsSwapDelay), address += sizeof(uint16_t);
  EEPROM.get(address, config.spamDelay), address += sizeof(uint16_t);
  EEPROM.get(address, config.delayAfterInput), address += sizeof(uint16_t);
  config.statusWork = EEPROM.read(address++) == 1;
  config.statusSpam = EEPROM.read(address++) == 1;
  config.statusSwap = EEPROM.read(address++) == 1;
  config.keyCode = EEPROM.read(address++);
  return config;
}