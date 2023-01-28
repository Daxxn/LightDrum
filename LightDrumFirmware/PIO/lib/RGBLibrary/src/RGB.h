#pragma once

#include <Arduino.h>

class RGB
{
public:
    RGB(int rPin, int gPin, int bPin);

    void SetRGB(uint8_t r, uint8_t g, uint8_t b);
    void SetRGB(uint8_t *rgbArr);
    void Send();
private:
    int rgbPins[3];
    uint8_t states[3];

    void SendRGB();
};