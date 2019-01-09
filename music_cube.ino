#include "CubeSensor.h"
#include "RFIDSensor.h"
#include "Convert.h"

const byte SS_PIN = 10;
const byte RST_PIN = 9;

RFIDPins pins = {SS_PIN, RST_PIN};
CubeSensor* cubeSensor = new RFIDSensor(&pins);

void setup()
{
  Serial.begin(9600);
  Serial.println("Odczytywanie kodu RFID");
  cubeSensor->begin(cubeChangeState);
}

void loop()
{
  cubeSensor->refresh();
}

void cubeChangeState(Gesture gesture, byte *buffer, byte bufferSize)
{
  String code = Convert::bytesToHex(buffer, bufferSize);
  Serial.print("Code: ");
  Serial.println(code);

  Serial.print("GESTURE_UP: ");
  Serial.println(gesture == GESTURE_UP);

  Serial.print("GESTURE_DOWN: ");
  Serial.println(gesture == GESTURE_DOWN);
}
