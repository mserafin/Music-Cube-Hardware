#pragma once
#include "Arduino.h"
#include "DateUtils.h"
#include "PololuLedStrip.h"

template<unsigned char T> class LightEffect : public PololuLedStrip<T>
{
  public:
    LightEffect(unsigned int count)
    {
      ledCount = count;
      delete[] colors;
      colors = new rgb_color[ledCount];
    };

    void turnOn() {
      story.effect = EFFECT_ON;
    };

    void turnOff() {
      story.effect = EFFECT_OFF;
    }

    void refresh() {
      if (!DateUtils::isDelaying(story.lastMillis, delay)) {
        return;
      }

      if (story.effect == EFFECT_ON && story.index >= 0 && story.index < ledCount) {
        turnOnByIndex();
        story.index += 1;
      }

      if (story.effect == EFFECT_OFF && story.index > 0 && story.index <= ledCount ) {
        story.index -= 1;
        turnOffByIndex();
      }

      if (story.effect == EFFECT_ON && story.index == ledCount) {
        active();
      }

      story.lastMillis = millis();
    };

  private:
    unsigned int delay = 10;
    unsigned int ledCount;
    rgb_color * colors;

    enum Effect : byte {
      EFFECT_ON,
      EFFECT_OFF
    };

    struct Store {
      unsigned long lastMillis = 0L;
      byte index;
      Effect effect;
    } story;

    void turnOnByIndex()
    {
      unsigned long time = millis() >> 2;
      colors[story.index] = calculateToRgb(story.index, time);
      this->write(colors, ledCount);
    }

    void turnOffByIndex()
    {
      colors[story.index] = hsvToRgb(0, 0, 0);
      this->write(colors, ledCount);
    }

    void active()
    {
      unsigned long time = millis() >> 2;
      for (byte i = 0; i < ledCount; i++)
      {
        colors[i] = calculateToRgb(i, time);
      }

      this->write(colors, ledCount);
    }

    rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v) {
      uint8_t f = (h % 60) * 255 / 60;
      uint8_t p = (255 - s) * (uint16_t)v / 255;
      uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
      uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
      uint8_t r = 0, g = 0, b = 0;
      switch ((h / 60) % 6) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
      }
      return rgb_color(r, g, b);
    }

    rgb_color calculateToRgb(byte i, unsigned long time) {
      byte x = (time >> 2) - (i << 3);
      return hsvToRgb((uint32_t)x * 359 / 256, 255, 255);
    }
};
