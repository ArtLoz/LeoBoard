#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

const int CURRENT_CONFIG_SIZE = 15;

struct Config {
  byte windowCount;       
  char key1;          
  char Key2;         
  char Key3;          
  char Key4;         
  byte keyCode;
  uint16_t windowsSwapDelay;       
  uint16_t spamDelay;      
  uint16_t delayAfterInput;     
  bool statusWork;            
  bool statusSpam;             
  bool statusSwap;           
};

Config bufferToConfig(const byte buffer[], int bufferSize);

int configToBuffer(const Config &config, byte buffer[], int bufferSize);

#endif // CONFIG_H