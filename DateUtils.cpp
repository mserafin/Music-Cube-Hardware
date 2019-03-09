#include "DateUtils.h"

uint8_t DateUtils::isDelaying(uint32_t timeInMillis, uint16_t interval)
{
  return (millis() - timeInMillis) > interval;
}
