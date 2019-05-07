#pragma once
#include "Arduino.h"
#include "DateUtils.h"
#include "WiFiClient.h"
#include "ESP8266HTTPClient.h"

struct HTTPApi
{
  String HOST;
  uint16_t PORT;
  String DEVICE_NAME;
};

class HttpManager {
  public:
    HttpManager(HTTPApi* api);
    void play(String tag);
    void pause();
    void next();

  protected:
    const HTTPApi* api;
    WiFiClient client;
    HTTPClient http;
    String fetch(String url);
    String getUrl(String endpoint);
};
