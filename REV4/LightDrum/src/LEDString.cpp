#include <Arduino.h>
#include "LEDString.h"
#include "PCA9634.h"

LEDString::LEDString(
  PCA9634 *pwm0,
  PCA9634 *pwm1,
  PCA9634 *pwm2,
  LEDs *red,
  LEDs *green,
  LEDs *blue,
  int channels
)
{
  this->pwm = new PCA9634[3];
  this->pwm[0] = *pwm0;
  this->pwm[1] = *pwm1;
  this->pwm[2] = *pwm2;
  this->redStrips = red;
  this->greenStrips = green;
  this->blueStrips = blue;
  this->channels = channels;
}

LEDString::~LEDString()
{
  delete[] this->pwm;
}

void LEDString::SetRGB(unsigned int channel, uint8_t r, uint8_t g, uint8_t b)
{
  if (channel > this->channels) return;
  this->redStrips[channel].value = r;
  this->greenStrips[channel].value = g;
  this->blueStrips[channel].value = b;
}

void LEDString::SetColor(unsigned int channel, Color color, uint8_t value)
{
  if (channel > this->channels) return;
  if (color == Color::RED)
  {
    this->redStrips[channel].value = value;
  }
  else if (color == Color::GREEN)
  {
    this->greenStrips[channel].value = value;
  }
  else if (color == Color::BLUE)
  {
    this->blueStrips[channel].value = value;
  }
}

void LEDString::SetGlobalPWM(uint8_t pwm)
{
  for (size_t i = 0; i < this->ctrlCount; i++)
  {
    this->pwm[i].SetGroupPWM(pwm);
  }
}
#pragma endregion

#pragma region Update
void LEDString::Update()
{
  for (size_t i = 0; i < this->channels; i++)
  {
    this->pwm[this->redStrips[i].controller]
      .SetState(this->redStrips[i].index, this->redStrips[i].value);
    this->pwm[this->greenStrips[i].controller]
      .SetState(this->greenStrips[i].index, this->greenStrips[i].value);
    this->pwm[this->blueStrips[i].controller]
      .SetState(this->blueStrips[i].index, this->blueStrips[i].value);
  }

  for (size_t i = 0; i < this->ctrlCount; i++)
  {
    this->pwm[i].Update();
  }
}
#pragma endregion