#pragma once
#include "Arduino.h"
#include "DateUtils.h"
#include "PololuLedStrip.h"

template<uint8_t T> class LightEffect : public PololuLedStrip<T>
{
  public:
    LightEffect(uint8_t count)
    {
      countLEDs = count;
      delete[] colors;
      colors = new rgb_color[countLEDs];
    };
    
    void turnOn() {
      story.effect = EFFECT_ON;
    };

    void turnOff() {
      story.effect = EFFECT_OFF;
    }

    void refresh() {
      if (!DateUtils::isDelaying(story.lastMillis, DELAY)) {
        return;
      }

      if (story.effect == EFFECT_ON && story.index >= 0 && story.index < countLEDs) {
        turnOnByIndex(story.index);
        story.index += 1;
      }

      if (story.effect == EFFECT_OFF && story.index > 0 && story.index <= countLEDs ) {
        story.index -= 1;
        turnOffByIndex(story.index);
      }

      if (story.effect == EFFECT_ON && story.index == countLEDs) {
        active();
      }

      story.lastMillis = millis();
    };

  private:
    const uint8_t DELAY = 10;
    uint8_t countLEDs = 0;
    rgb_color * colors;

    enum Effect : uint8_t {
      EFFECT_ON,
      EFFECT_OFF
    };

    struct Store {
      uint32_t lastMillis = 0L;
      uint8_t index = 0;
      Effect effect;
    } story;

    void turnOnByIndex(uint8_t index)
    {
      uint32_t time = millis() >> 2;
      colors[index] = calculateToRgb(story.index, time);
      this->write(colors, countLEDs);
    }

    void turnOffByIndex(uint8_t index)
    {
      colors[index] = hsvToRgb(0, 0, 0);
      this->write(colors, countLEDs);
    }

    void active()
    {
      uint32_t time = millis() >> 2;
      for (uint8_t i = 0; i < countLEDs; i++)
      {
        colors[i] = calculateToRgb(i, time);
      }

      this->write(colors, countLEDs);
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

    rgb_color calculateToRgb(uint8_t i, uint32_t time) {
      uint8_t x = (time >> 2) - (i << 3);
      return hsvToRgb((uint32_t)x * 359 / 256, 255, 255);
    }
};
