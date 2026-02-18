#ifndef EEPROMCONFIG_H
#define EEPROMCONFIG_H

#include <EEPROM.h>
#include "Config.h" 
const int EEPROM_START_ADDRESS = 0;

class EEPROMConfig {
public:
  EEPROMConfig() {}

  void saveConfig(const Config &config);

  Config loadConfig();
};

#endif // EEPROMCONFIG_H