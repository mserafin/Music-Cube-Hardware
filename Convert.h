#pragma once
#include "Arduino.h"

class Convert
{
  public:
    static uint32_t bytesToInt(uint8_t *buffer, uint8_t bufferSize);
    static String intToHex(uint32_t value);
    static String bytesToHex(uint8_t *buffer, uint8_t bufferSize);
    static String bytesToDec(uint8_t *buffer, uint8_t bufferSize);
};
