#include "WiFiManager.h"
#include "HttpManager.h"
#include "CubeSensor.h"
#include "RFIDSensor.h"
#include "LightEffect.h"
#include "Convert.h"
#include "Config.h"

GENConfig   configGen;
APIConfig   configApi;
LEDConfig   configLed;
RFIDConfig  configRfid;

HTTPApi api = {configApi.HOST, configApi.PORT, configGen.DEVICE_NAME};
HttpManager* httpManager = new HttpManager(&api);

RFIDPins pins = {configRfid.SS_PIN, configRfid.RST_PIN};
CubeSensor* cubeSensor = new RFIDSensor(&pins);

LightEffect* lightEffect = new LightEffect(configLed.COUNT, configLed.PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(115200);
  Serial.println("CubeSensor:setup");

  WiFiManager wifiManager;
  wifiManager.autoConnect(configGen.AP_NAME, configGen.AP_PASSWORD);

  cubeSensor->begin(cubeSensorChange);

  lightEffect->begin();
  lightEffect->setBrightness(configLed.BRIGHTNESS);
}

void loop()
{
  cubeSensor->refresh();
  lightEffect->refresh();
}

void cubeSensorChange(Gesture gesture, uint8_t *buffer, uint8_t bufferSize)
{
  String tag = Convert::bytesToHex(buffer, bufferSize);
  Serial.print("Tag: ");
  Serial.println(tag);

  if (gesture == GESTURE_UP) {
    Serial.println("GESTURE_UP");
    lightEffect->turnOff();
    httpManager->pause();
  }

  if (gesture == GESTURE_DOWN) {
    Serial.println("GESTURE_DOWN");
    lightEffect->turnOn();
    httpManager->play(tag);
  }

  if (gesture == GESTURE_SKIP) {
    Serial.println("GESTURE_SKIP");
    httpManager->next();
  }
}
