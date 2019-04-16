#include "CubeSensor.h"
#include "RFIDSensor.h"
#include "LightEffect.h"
#include "Convert.h"

const uint8_t SS_PIN = 8;
const uint8_t RST_PIN = 3;

const uint8_t LED_PIN = 4;
const uint8_t LED_COUNT = 24;
const uint8_t LED_BRIGHTNESS = 25;

RFIDPins pins = {SS_PIN, RST_PIN};
CubeSensor* cubeSensor = new RFIDSensor(&pins);
LightEffect* lightEffect = new LightEffect(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(115200);
  
  cubeSensor->begin(cubeSensorChange);
  
  lightEffect->begin();
  lightEffect->setBrightness(LED_BRIGHTNESS);
}

void loop()
{
  cubeSensor->refresh();
  lightEffect->refresh();
}

void cubeSensorChange(Gesture gesture, uint8_t *buffer, uint8_t bufferSize)
{
  String code = Convert::bytesToHex(buffer, bufferSize);
  Serial.print("Code: ");
  Serial.println(code);

  if (gesture == GESTURE_UP) {
    Serial.println("GESTURE_UP");
    lightEffect->turnOff();
  }

  if (gesture == GESTURE_DOWN) {
    Serial.println("GESTURE_DOWN");
    lightEffect->turnOn();
  }

  if (gesture == GESTURE_SKIP) {
    Serial.println("GESTURE_SKIP");
  }
}
