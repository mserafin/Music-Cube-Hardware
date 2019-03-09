#pragma once
#include <SPI.h>
#include <MFRC522.h>
#include "Arduino.h"
#include "CubeSensor.h"
#include "DateUtils.h"

struct RFIDPins
{
  uint8_t SS;
  uint8_t RST;
};

class RFIDSensor : public CubeSensor {
  public:
    RFIDSensor(RFIDPins* pins);
    void begin(CubeSensorChangeCallback callback) override;
    void refresh() override;

  protected:
    MFRC522 sensor;

  private:
    const uint16_t DELAY = 250; //[ms]

    const RFIDPins* pins;

    struct Store {
      Gesture lastGesture = NULL;
      uint32_t lastReadMillis = 0L;
      uint32_t lastChangeMillis = 0L;
      uint32_t lastIntervalMillis = 0L;
    } story;

    CubeSensorChangeCallback _cubeSensorChangeCallback;

    Gesture getGestureByStatus(uint8_t status);

    uint8_t isCubeSensorChange(Gesture gesture);
};
