#pragma once
#include "Arduino.h"
#include "DateUtils.h"
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
 #include <avr/power.h>
#endif

enum Effect : uint8_t {
  EFFECT_ON,
  EFFECT_OFF
};

class LightEffect : public Adafruit_NeoPixel
{
  public:
    LightEffect(uint8_t pixels, uint8_t pin, uint8_t type);
    void turnOn(void);
    void turnOff(void);
    void refresh(void);

  private:
    const uint8_t DELAY = 10;
    const uint8_t PIXEL_HUE_INCREMENT = 128;
    struct Store {
      uint32_t pixelHue = 0L;
      uint32_t lastMillis = 0L;
      uint8_t index = 0;
      Effect effect;
    } story;

    void turnOnByIndex(uint8_t index);
    void turnOffByIndex(uint8_t index);
    void active(void);
    
    uint32_t getColorRGB(uint8_t index, uint8_t num);
};
