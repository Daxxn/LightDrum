#include <Arduino.h>
#include "RGB.h"

RGB::RGB(int rPin, int gPin, int bPin)
{
    this->rgbPins[0] = rPin;
    this->rgbPins[1] = gPin;
    this->rgbPins[2] = bPin;
}

void RGB::SetRGB(uint8_t r, uint8_t g, uint8_t b)
{
    this->states[0] = r;
    this->states[1] = g;
    this->states[2] = b;
    this->SendRGB();
}

void RGB::SetRGB(uint8_t *rgb)
{
    this->SetRGB(rgb[0], rgb[1], rgb[2]);
}

void RGB::SendRGB()
{
    for (uint8_t i = 0; i < 3; i++)
    {
        analogWrite(this->rgbPins[i], this->states[i]);
    }
}