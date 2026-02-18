#include "Config.h"
#include <Arduino.h>

Config bufferToConfig(const byte buffer[], int bufferSize) {
  Config config;

  if (bufferSize < CURRENT_CONFIG_SIZE) {
    return config;
  }

  int index = 0;

  config.windowCount = buffer[index++];

  config.key1 = buffer[index++];
  config.Key2 = buffer[index++];
  config.Key3 = buffer[index++];
  config.Key4 = buffer[index++];
  config.keyCode = buffer[index++];
  config.windowsSwapDelay = (buffer[index +1] << 8) | buffer[index];
  index += 2;
  config.spamDelay = (buffer[index + 1] << 8) | buffer[index];
  index += 2;
  config.delayAfterInput = (buffer[index + 1] << 8) | buffer[index];
  index += 2;
  config.statusWork = buffer[index++] != 0;
  config.statusSpam = buffer[index++] != 0;
  config.statusSwap = buffer[index++] != 0;

  return config;
}

int configToBuffer(const Config &config, byte buffer[], int bufferSize) {
  if (bufferSize < CURRENT_CONFIG_SIZE) { 
    return 0;
  }

  int index = 0;

  buffer[index++] = config.windowCount;

  buffer[index++] = config.key1;
  buffer[index++] = config.Key2;
  buffer[index++] = config.Key3;
  buffer[index++] = config.Key4;
  buffer[index++] = config.keyCode;
  buffer[index++] = config.windowsSwapDelay & 0xFF;        
  buffer[index++] = (config.windowsSwapDelay >> 8) & 0xFF; 

  buffer[index++] = config.spamDelay & 0xFF;        
  buffer[index++] = (config.spamDelay >> 8) & 0xFF; 

  buffer[index++] = config.delayAfterInput & 0xFF;      
  buffer[index++] = (config.delayAfterInput >> 8) & 0xFF;

  buffer[index++] = config.statusWork ? 1 : 0;
  buffer[index++] = config.statusSpam ? 1 : 0;
  buffer[index++] = config.statusSwap ? 1 : 0;

  return index; 
}