#include <Arduino.h>
#include <math.h>
#include "Audio.h"

Audio::Audio(int inputPin)
{
    this->_inputPin = inputPin;
}

void Audio::Begin()
{
    for (uint8_t i = 0; i < BUFFERSIZE; i++)
    {
        this->_raw[i] = 0;
        this->_values[i] = 0;
    }
}

void Audio::Calc()
{
    for (size_t i = 0; i < BUFFERSIZE - 2; i++)
    {
        this->_raw[i] = analogRead(this->_inputPin);
    }
    
}

void Audio::CalcFreq()
{
    for (size_t i = 0; i < BUFFERSIZE; i += 2)
    {
        uint8_t val = this->_raw[i] - this->_raw[i + 1];
    }
    
}