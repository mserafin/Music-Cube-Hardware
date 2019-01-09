#pragma once
#include <SPI.h>
#include <MFRC522.h>
#include "Arduino.h"
#include "CubeSensor.h"
#include "DateUtils.h"

struct RFIDPins
{
  byte SS;
  byte RST;
};

class RFIDSensor : public CubeSensor {
  public:
    RFIDSensor(RFIDPins* pins);
    void begin(void (*callback)(Gesture gesture, byte *buffer, byte bufferSize)) override;
    void refresh() override;

  protected:
    MFRC522 sensor;

  private:
    const int DELAY = 500; //[ms]

    const RFIDPins* pins;

    struct Store {
      bool lastStatus = true;
      unsigned long lastReadMillis = 0L;
      unsigned long lastIntervalMillis = 0L;
    } story;

    void (*onChange)(Gesture gesture, byte *buffer, byte bufferSize);

    Gesture getGestureByStatus(bool status);
};
