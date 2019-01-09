#pragma once
#include "Arduino.h"

class DateUtils
{
  public:
    static bool isDelaying(unsigned long timeInMillis, int interval);
};
