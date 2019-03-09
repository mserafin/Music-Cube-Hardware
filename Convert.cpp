#include "Convert.h"

uint32_t Convert::bytesToInt(uint8_t *buffer, uint8_t bufferSize)
{
  uint32_t accum = 0L;
  for (uint8_t i = 0; i < bufferSize; i++) {
    accum <<= 8;
    accum |= (buffer[i] & 0xFF);
  }
  return accum;
}

String Convert::intToHex(uint32_t value) {
  return String(value, HEX);
}

String Convert::bytesToHex(uint8_t *buffer, uint8_t bufferSize) {
  String accum;
  for (uint8_t i = 0; i < bufferSize; i++) {
    accum += buffer[i] < 0x10 ? "0" : "";
    accum += String(buffer[i], HEX);
  }
  return accum;
}

String Convert::bytesToDec(uint8_t *buffer, uint8_t bufferSize) {
  String accum;
  for (uint8_t i = 0; i < bufferSize; i++) {
    accum += buffer[i] < 0x10 ? "0" : "";
    accum += String(buffer[i], DEC);
  }
  return accum;
}
