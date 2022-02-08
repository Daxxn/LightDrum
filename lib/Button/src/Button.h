#pragma once

#include <Arduino.h>

class Button
{
public:
  Button();
  Button(int pin, void (*click)());
  Button(int pin, void (*click)(), uint8_t mode);

  void (*Click)();

  void Update();
private:
  int _pin;
  uint8_t _mode;
};