#include "DateUtils.h"

bool DateUtils::isDelaying(unsigned long timeInMillis, int interval)
{
  return (millis() - timeInMillis) > interval;
}
