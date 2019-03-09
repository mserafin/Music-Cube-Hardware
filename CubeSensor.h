#pragma once

enum Gesture : uint8_t {
  GESTURE_UP,
  GESTURE_DOWN,
  GESTURE_SKIP
};

typedef void (*CubeSensorChangeCallback)(Gesture gesture, uint8_t *buffer, uint8_t bufferSize);

class CubeSensor {
  public:
    virtual void begin(CubeSensorChangeCallback callback);
    virtual void refresh();
};
