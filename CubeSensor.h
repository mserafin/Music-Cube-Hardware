#pragma once

enum Gesture : byte {
  GESTURE_UP,
  GESTURE_DOWN,
  GESTURE_NEXT,
  GESTURE_PREV
};

class CubeSensor {
  public:
    virtual void begin(void (*callback)(Gesture gesture, byte *buffer, byte bufferSize));
    virtual void refresh();
};
