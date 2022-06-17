#pragma once

#include <Arduino.h>

class CurrentSense
{
public:
    CurrentSense(int sensePin, float resistor, int multiplier);

    void Begin();

    float Read();

    void Debug();
private:
    int _pin;
    float _resistor;
    int _multiplier;

    int _raw;
    float _inputVoltage;
    float _current;

    void Calc();
};