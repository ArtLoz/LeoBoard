#include <Arduino.h>
#include "Constants.h"
#include "Keyboard.h"
#include "config/Config.h"
#include "config/EEPROMConfig.h"
#include "utils/Helper.h"

void spamKey();
void serialReciver();
void updateConfig(byte *inputBuffer, int size);
void loadConfig();
void SendConfig();
void sendPolling();
void swapWindows();

const int BUFFER_SIZE = 44;
unsigned long disableSwapWindowsTime = 0;
boolean workStateRealTime = true;
boolean workKeyPressRealTime = false;
boolean swapRealTime = false;

EEPROMConfig eepromConfig;
Config deviceConfig = {
    .windowCount = 2,
    .key1 = '1',
    .Key2 = '2',
    .Key3 = '3',
    .Key4 = '4',
    .keyCode = 0xC4,
    .windowsSwapDelay = 1000,
    .spamDelay = 1000,
    .delayAfterInput = 1000,
    .statusWork = false,
    .statusSpam = false,
    .statusSwap = false};

void setup()
{
  Serial.begin(115200);
  loadConfig();
}

void loop()
{
  sendPolling();
  serialReciver();
  spamKey();
  swapWindows();
}

void serialReciver()
{
  if (Serial.available() > 0)
  {
    byte bufferRead[BUFFER_SIZE];
    int index = 0;
    while (Serial.available() > 0 && index < BUFFER_SIZE)
    {
      byte byteRead = Serial.read();
      bufferRead[index] = byteRead;
      index++;
    }
    if (index < 2)
      return;
    disableSwapWindowsTime = millis();
    uint16_t command = bytesToUint16t(bufferRead[0], bufferRead[1]);
    switch (command)
    {
    case DISABLE_SWAP_WINDOWS_INPUT:
      disableSwapWindowsTime = millis();
      break;
    case SWAP_WORK_STATE_REAL_TIME:
      workStateRealTime = !workStateRealTime;
      break;
    case SWAP_KEY_PRESS_REAL_TIME:
      workKeyPressRealTime = !workKeyPressRealTime;
      break;
    case SWAP_KEY_SWAP_REAL_TIME:
      swapRealTime = !swapRealTime;
      break;
    case UPDATE_CONFIG:
      updateConfig(bufferRead, sizeof(bufferRead));
      byte answer[2];
      uint16ToBuffer(UPDATE_CONFIG, answer);
      Serial.write(answer, sizeof(answer));
      break;
    case GET_CONFIG:
      SendConfig();
      break;
    default:
      break;
    }
  }
}

void loadConfig()
{
  Config config = eepromConfig.loadConfig();
  if (config.windowCount == 255)
    return;
  deviceConfig = config;
}

void sendPolling()
{
  static unsigned long lastSendTimePolling = 0;
  unsigned long currentMillis = millis();
  byte buffer[POLLING_BUFFER_SIZE];
  uint16ToBuffer(POLLING, buffer);
  if (currentMillis - lastSendTimePolling >= 1000)
  {
    lastSendTimePolling = currentMillis;
    cratePolingOutputData(POLLING, workStateRealTime, swapRealTime, workKeyPressRealTime, buffer);
    Serial.write(buffer, sizeof(buffer));
  }
}
void updateConfig(byte *inputBuffer, int size)
{
  int payloadSize = size - 4;
  byte payload[payloadSize];
  memcpy(payload, &inputBuffer[2], payloadSize);
  uint16_t crcInputBuffer = calculateCRC(payload, payloadSize);
  if (bytesToUint16t(inputBuffer[size - 2], inputBuffer[size - 1]) != crcInputBuffer)
    return;
  Config newConfig = bufferToConfig(payload, payloadSize);
  eepromConfig.saveConfig(newConfig);
  loadConfig();
}
void SendConfig()
{
  byte bufferConfig[CURRENT_CONFIG_SIZE];
  byte payload[40];
  byte outputBuffer[size_t(sizeof(payload)) + 4];
  configToBuffer(deviceConfig, bufferConfig, sizeof(bufferConfig));
  createConfigPayload(bufferConfig, sizeof(bufferConfig), payload);
  createOutputData(GET_CONFIG, payload, sizeof(payload), outputBuffer);
  Serial.write(outputBuffer, size_t(sizeof(outputBuffer)));
}

void swapWindows()
{
  static unsigned long lastActionTime = 0;

  static int step = 0;
  static int currentWindow = 0;
  unsigned long currentMillis = millis();
  const char keys[] = {
    deviceConfig.key1,
    deviceConfig.Key2,
    deviceConfig.Key3,
    deviceConfig.Key4
  };
  if (currentMillis - disableSwapWindowsTime < deviceConfig.delayAfterInput || !swapRealTime) {
    step = 0;
    Keyboard.releaseAll();
    currentWindow = 0;
    lastActionTime = currentMillis;
    return;
  }

  if (deviceConfig.windowCount < 1 || deviceConfig.windowCount > 4) return;

  switch (step)
  {
  case 0:
    if (currentMillis - lastActionTime >= deviceConfig.windowsSwapDelay)
    {
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(keys[currentWindow]);
      lastActionTime = currentMillis;
      step = 1;
    }
    break;

  case 1:
    if (currentMillis - lastActionTime >= 50)
    {
      Keyboard.releaseAll();
      lastActionTime = currentMillis;
      currentWindow++;
      if (currentWindow < deviceConfig.windowCount)
      {
        step = 0;
      }
      else
      {
        step = 2;
      }
    }
    break;

  case 2:
    if (currentMillis - lastActionTime >= deviceConfig.windowsSwapDelay)
    {
      step = 0;
      currentWindow = 0;
    }
    break;
  }
}

void spamKey()
{
  static unsigned long lastPressTime = 0;
  static unsigned long lastReleaseTime = 0;
  static bool isKeyPressed = false;

  unsigned long currentMillis = millis();

  if (!isKeyPressed && currentMillis - lastReleaseTime >= deviceConfig.spamDelay && workKeyPressRealTime)
  {
    Keyboard.press(deviceConfig.keyCode);
    isKeyPressed = true;
    lastPressTime = currentMillis;
  }

  if (isKeyPressed && currentMillis - lastPressTime >= 10)
  {
    Keyboard.release(deviceConfig.keyCode);
    isKeyPressed = false;
    lastReleaseTime = currentMillis;
  }
}