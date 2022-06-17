#pragma once

#include <Arduino.h>

#define DEBOUNCE_TIME 60

class Button
{
public:
  Button();
  Button(int pin, void (*click)());
  Button(int pin, void (*click)(), uint8_t mode);

  void (*Click)();

  void Update();
private:
  unsigned long _lastPressTime;
  unsigned long _currentPressTime;
  int _pin;
  uint8_t _state;
  uint8_t _prevState;
  uint8_t _mode;

  static bool Debounce(unsigned long current, unsigned long last);
};