#include "Convert.h"

unsigned long Convert::bytesToInt(byte *buffer, byte bufferSize)
{
  unsigned long accum = 0L;
  for (byte i = 0; i < bufferSize; i++) {
    accum <<= 8;
    accum |= (buffer[i] & 0xFF);
  }
  return accum;
}

String Convert::intToHex(unsigned long value) {
  return String(value, HEX);
}

String Convert::bytesToHex(byte *buffer, byte bufferSize) {
  String accum;
  for (byte i = 0; i < bufferSize; i++) {
    accum += buffer[i] < 0x10 ? "0" : "";
    accum += String(buffer[i], HEX);
  }
  return accum;
}

String Convert::bytesToDec(byte *buffer, byte bufferSize) {
  String accum;
  for (byte i = 0; i < bufferSize; i++) {
    accum += buffer[i] < 0x10 ? "0" : "";
    accum += String(buffer[i], DEC);
  }
  return accum;
}

