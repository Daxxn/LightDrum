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
  // Serial.println("In Update");
  this->_state = digitalRead(this->_pin);
  this->_currentPressTime = millis();
  if (this->_state == 0 && this->Debounce(this->_currentPressTime, this->_lastPressTime))
  {
    this->Click();
  }
  this->_lastPressTime = this->_currentPressTime;
}

bool Button::Debounce(unsigned long current, unsigned long last)
{
  return (current - last) > DEBOUNCE_TIME;
}