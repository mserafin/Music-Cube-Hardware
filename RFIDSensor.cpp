#include "RFIDSensor.h"

RFIDSensor::RFIDSensor(RFIDPins* pins)
{
  this->pins = pins;
}

void RFIDSensor::begin(CubeSensorChangeCallback callback)
{
  SPI.begin();
  MFRC522 sensor(pins->SS, pins->RST);
  sensor.PCD_Init();

  _cubeSensorChangeCallback = callback;
}

void RFIDSensor::refresh()
{
  if (!DateUtils::isDelaying(story.lastIntervalMillis, DELAY)) {
    return;
  }

  story.lastIntervalMillis = millis();

  if (sensor.PICC_IsNewCardPresent() && sensor.PICC_ReadCardSerial()) {
    story.lastReadMillis = millis();
  }

  Gesture gesture = getGestureByStatus(!DateUtils::isDelaying(story.lastReadMillis, DELAY << 1));
  if (isCubeSensorChange(gesture))
  {
    _cubeSensorChangeCallback(gesture, sensor.uid.uidByte, sensor.uid.size);

    uint8_t isSkip = !DateUtils::isDelaying(story.lastChangeMillis, DELAY << 2);
    if (isSkip && gesture == GESTURE_DOWN)
    {
      _cubeSensorChangeCallback(GESTURE_SKIP, sensor.uid.uidByte, sensor.uid.size);
    }

    story.lastGesture = gesture;
    story.lastChangeMillis = millis();
  }
}

uint8_t RFIDSensor::isCubeSensorChange(Gesture gesture)
{
  return story.lastReadMillis >= (DELAY << 2) && story.lastGesture != gesture;
}

Gesture RFIDSensor::getGestureByStatus(uint8_t status)
{
  return !status ? GESTURE_UP : GESTURE_DOWN;
}
