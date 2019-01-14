#include "CubeSensor.h"
#include "RFIDSensor.h"
#include "LightEffect.h"
#include "Convert.h"

const byte SS_PIN = 10;
const byte RST_PIN = 9;

const byte LED_PIN = 2;
const byte LED_COUNT = 24;

RFIDPins pins = {SS_PIN, RST_PIN};
CubeSensor* cubeSensor = new RFIDSensor(&pins);
LightEffect<LED_PIN>* lightEffect = new LightEffect<LED_PIN>(LED_COUNT);

bool first = true;

void setup()
{
  PololuLedStripBase::interruptFriendly = true;

  Serial.begin(9600);
  Serial.println("Odczytywanie kodu RFID");
  cubeSensor->begin(cubeChangeState);
}

void loop()
{
  cubeSensor->refresh();
  lightEffect->refresh();
}

void cubeChangeState(Gesture gesture, byte *buffer, byte bufferSize)
{
  String code = Convert::bytesToHex(buffer, bufferSize);
  Serial.print("Code: ");
  Serial.println(code);

  if (!first) {
    Serial.print("GESTURE_UP: ");
    Serial.println(gesture == GESTURE_UP);
    if (gesture == GESTURE_UP) {
      lightEffect->turnOff();
    }

    Serial.print("GESTURE_DOWN: ");
    Serial.println(gesture == GESTURE_DOWN);
    if (gesture == GESTURE_DOWN) {
      lightEffect->turnOn();
    }
  } else {
    first = false;
  }
}
