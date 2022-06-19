#pragma once

#include <Arduino.h>

class CurrentSense
{
public:
    CurrentSense(int sensePin, float resistor, int multiplier);

    // Starts the Monitor.
    // Theres not much to begin at the moment.
    void Begin();
    // Read and calculate the actual current in Amps.
    float Read();

    // For debugging only.
    // Requires a serial monitor.
    void Debug();
    // Gets the raw current value.
    int GetRaw();

    uint8_t ToByte();
private:
    int _pin;
    float _resistor;
    int _multiplier;

    int _raw;
    float _inputVoltage;
    float _current;

    void Calc();
};