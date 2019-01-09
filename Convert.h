#pragma once
#include "Arduino.h"

class Convert
{
  public:
    static unsigned long bytesToInt(byte *buffer, byte bufferSize);
    static String intToHex(unsigned long value);
    static String bytesToHex(byte *buffer, byte bufferSize);
    static String bytesToDec(byte *buffer, byte bufferSize);
};
