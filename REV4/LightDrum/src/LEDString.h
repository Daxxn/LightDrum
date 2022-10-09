#pragma once

#include <Arduino.h>
#include "PCA9634.h"

struct LEDs
{
  LEDs() {};
  LEDs(uint8_t ctrl, uint8_t index) {
    this->controller = ctrl;
    this->index = index;
  };
  LEDs(uint8_t ctrl, uint8_t index, uint8_t def) {
    this->controller = ctrl;
    this->index = index;
    this->value = def;
  };
  uint8_t controller = 99;
  uint8_t index = 99;
  uint8_t value = 0;
};

enum class Color
{
  RED = 0,
  GREEN = 1,
  BLUE = 2
};

class LEDString
{
public:
  LEDString(
    PCA9634 *pwm0,
    PCA9634 *pwm1,
    PCA9634 *pwm2,
    LEDs *red,
    LEDs *green,
    LEDs *blue,
    int channels
  );
  ~LEDString();

  void SetRGB(unsigned int channel, uint8_t r, uint8_t g, uint8_t b);
  void SetColor(unsigned int channel, Color color, uint8_t value);

  void SetGlobalPWM(uint8_t pwm);

  void Update();
private:
  bool hasChanged = false;
  PCA9634 *pwm;
  LEDs *redStrips;
  LEDs *greenStrips;
  LEDs *blueStrips;
  unsigned int channels;
  unsigned int ctrlCount;
};