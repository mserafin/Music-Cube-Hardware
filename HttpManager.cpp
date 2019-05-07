#include "HttpManager.h"

HttpManager::HttpManager(HTTPApi* api)
{
  WiFiClient client;
  HTTPClient http;

  this->api = api;
}

void HttpManager::play(String tag)
{
  fetch(getUrl("/player/play?device=" + this->api->DEVICE_NAME + "&tag=" + tag));
}

void HttpManager::pause()
{
  fetch(getUrl("/player/pause?device=" + this->api->DEVICE_NAME));
}

void HttpManager::next()
{
  fetch(getUrl("/player/next?device=" + this->api->DEVICE_NAME));
}

String HttpManager::getUrl(String endpoint) {
  return "http://" + this->api->HOST + ":" + this->api->PORT + endpoint;
}

String HttpManager::fetch(String url) {
  if (http.begin(client, url))
  {
    uint32_t httpCode = http.GET();
    if (httpCode > 0)
    {
      if (httpCode == HTTP_CODE_OK ||
          httpCode == HTTP_CODE_ACCEPTED ||
          httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String response = http.getString();
        Serial.print("[HTTP] GET ");
        Serial.print(url);
        Serial.print(" (");
        Serial.print(httpCode);
        Serial.print("): ");
        Serial.println(response);

        return response;
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.println("[HTTP} Unable to connect");
  }

  return "";
}
