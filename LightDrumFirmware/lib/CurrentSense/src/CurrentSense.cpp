#include <Arduino.h>
#include "CurrentSense.h"

CurrentSense::CurrentSense(int pin, float resistor, int multiplier)
{
    this->_pin = pin;
    this->_resistor = resistor;
    this->_multiplier = multiplier;
}

void CurrentSense::Begin()
{
    this->Read();
}

float CurrentSense::Read()
{
    this->_raw = analogRead(this->_pin);
    this->Calc();
    return this->_current;
}

void CurrentSense::Calc()
{
    this->_inputVoltage = this->_raw * (5.0 / 1023.0);
    this->_current = this->_inputVoltage * this->_multiplier;
}

int CurrentSense::GetRaw()
{
    return this->_raw;
}

uint8_t CurrentSense::ToByte()
{
    return (uint8_t)(this->_raw / 4);
}

void CurrentSense::Debug()
{
    Serial.print("Raw: ");
    Serial.print(this->_raw);
    Serial.print("  Volt: ");
    Serial.print(this->_inputVoltage);
    Serial.print("  Current: ");
    Serial.println(this->_current);
}