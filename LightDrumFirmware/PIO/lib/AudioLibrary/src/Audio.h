#pragma once

#include <Arduino.h>

#define BUFFERSIZE 16

class Audio
{
public:
    Audio(int inputPin);

    void Begin();
    void Calc();
private:
    int _inputPin;
    uint8_t _raw[BUFFERSIZE];
    uint8_t _values[BUFFERSIZE];


    void CalcFreq();
};