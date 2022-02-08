#include <Arduino.h>
#include "Button.h"

Button::Button() {
  this->_pin = 0;
}

Button::Button(int pin, void (*click)())
{
  this->_pin = pin;
  this->Click = click;
  pinMode(pin, INPUT_PULLUP);
}

Button::Button(int pin, void (*click)(), uint8_t mode)
{
  this->_pin = pin;
  this->Click = click;
  this->_mode = mode;
  pinMode(pin, mode);
}

void Button::Update()
{
  if (digitalRead(this->_pin) == 1)
  {
    this->Click();
  }
}