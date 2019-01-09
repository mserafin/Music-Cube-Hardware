#include <SPI.h>
#include <MFRC522.h>
#include "RFIDSensor.h"

RFIDSensor::RFIDSensor(RFIDPins* pins)
{
  this->pins = pins;
}

void RFIDSensor::begin(void (*callback)(Gesture gesture, byte *buffer, byte bufferSize))
{
  SPI.begin();
  MFRC522 sensor(pins->SS, pins->RST);
  sensor.PCD_Init();

  onChange = callback;
}

void RFIDSensor::refresh()
{
  if (!DateUtils::isDelaying(story.lastIntervalMillis, DELAY)) {
    return;
  }

  story.lastIntervalMillis = millis();

  if (sensor.PICC_IsNewCardPresent() &&
      sensor.PICC_ReadCardSerial()) {
    story.lastReadMillis = millis();
  }

  bool status = !DateUtils::isDelaying(story.lastReadMillis, DELAY * 2);
  if (status != story.lastStatus) {
    story.lastStatus = status;
    onChange(getGestureByStatus(status), sensor.uid.uidByte, sensor.uid.size);
  }
}

Gesture RFIDSensor::getGestureByStatus(bool status)
{
  return !status ? GESTURE_UP : GESTURE_DOWN;
}

