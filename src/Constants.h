#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>


const uint16_t POLLING_BUFFER_SIZE = 5;
// Команды
const uint16_t DISABLE_SWAP_WINDOWS_INPUT = 0x0010;
const uint16_t SWAP_WORK_STATE_REAL_TIME      = 0x0011;
const uint16_t SWAP_KEY_PRESS_REAL_TIME      = 0x0012;
const uint16_t SWAP_KEY_SWAP_REAL_TIME      = 0x0013;
const uint16_t POLLING              = 0x0001;
const uint16_t GET_CONFIG           = 0x0002;
const uint16_t UPDATE_CONFIG        = 0x0003;


//ключи
const int KEY_WINDWOWS_COUNT = 0;
const int KEY_WINDWOWS_FIRST = 1;
const int KEY_WINDWOWS_SECOND = 2;
const int KEY_WINDWOWS_THIRD = 3;
const int KEY_WINDWOWS_FOURTH = 4;
const int KEY_WINDOWS_SWAP_DELAY = 5;
const int KEY_SPAM_DELAY = 6;
const int KEY_DELEY_AFTER_INPUT = 7;
const int KEY_STATUS_WORK = 8;
const int KEY_STATUS_SPAM = 9;
const int KEY_STATUS_SWAP = 10;



#endif // CONSTANTS_H
