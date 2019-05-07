#ifndef CONFIG_H
#define CONFIG_H

struct GENConfig {
  const char* DEVICE_NAME = "cube_a6y1be1y6u";
  const char* AP_NAME = "MusicCubeAP";
  const char* AP_PASSWORD = "";
};

struct RFIDConfig {
  const uint8_t SS_PIN = D8;
  const uint8_t RST_PIN = D3;
};

struct LEDConfig {
  const uint8_t PIN = D4;
  const uint8_t COUNT = 24;
  const uint8_t BRIGHTNESS = 25;
};

struct APIConfig {
  const char* HOST = "192.168.0.8";
  const uint16_t PORT = 3000;
};

#endif
