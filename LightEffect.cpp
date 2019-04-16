#include "LightEffect.h"

LightEffect::LightEffect(uint8_t pixels, uint8_t pin, uint8_t type) : Adafruit_NeoPixel(pixels, pin, type) { }

void LightEffect::turnOn(void) {
  story.effect = EFFECT_ON;
}

void LightEffect::turnOff(void) {
  story.effect = EFFECT_OFF;
}

void LightEffect::refresh(void) {
  if (!DateUtils::isDelaying(story.lastMillis, DELAY)) {
    return;
  }

  uint8_t count = numPixels();

  if (story.effect == EFFECT_ON && story.index >= 0 && story.index < count) {
    turnOnByIndex(story.index);
    story.index += 1;
  }

  if (story.effect == EFFECT_OFF && story.index > 0 && story.index <= count) {
    story.index -= 1;
    turnOffByIndex(story.index);
  }

  if (story.effect == EFFECT_ON && story.index == count) {
    active();
  }

  story.pixelHue += PIXEL_HUE_INCREMENT;
  story.lastMillis = DateUtils::now();
}

void LightEffect::turnOnByIndex(uint8_t index)
{
  setPixelColor(index, getColorRGB(index, numPixels()));
  show();
}

void LightEffect::turnOffByIndex(uint8_t index)
{
  setPixelColor(index, Color(0, 0, 0));
  show();
}

void LightEffect::active(void)
{
  for (uint8_t i = 0, l = numPixels(); i < l; i++) {
    setPixelColor(i, getColorRGB(i, l));
  }
  show();
}

uint32_t LightEffect::getColorRGB(uint8_t index, uint8_t num)
{
  uint16_t hue = story.pixelHue + (index * 65536L / num);
  return gamma32(ColorHSV(hue));
}
