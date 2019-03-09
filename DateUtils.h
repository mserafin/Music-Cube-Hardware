#pragma once
#include "Arduino.h"

class DateUtils
{
  public:
    static uint8_t isDelaying(uint32_t timeInMillis, uint16_t interval);
};
