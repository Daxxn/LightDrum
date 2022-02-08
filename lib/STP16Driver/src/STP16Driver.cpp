#include <Arduino.h>
#include "STP16Driver.h"
#include "PrintUtils.h"

#pragma region Constructors
STP16Driver::STP16Driver(int dataPin, int clockPin, int latchPin, int enablePin)
{
    this->_dataPin = dataPin;
    this->_clockPin = clockPin;
    this->_latchPin = latchPin;
    this->_enablePin = enablePin;
}
#pragma endregion

#pragma region Initialization
void STP16Driver::Begin()
{
    this->_states[STP16_LED_COUNT] = {};
    pinMode(this->_dataPin, OUTPUT);
    pinMode(this->_clockPin, OUTPUT);
    pinMode(this->_latchPin, OUTPUT);
    pinMode(this->_enablePin, OUTPUT);

    this->SendState();
    this->_enable = true;
}
#pragma endregion

#pragma region Enable/Disable
void STP16Driver::Enable()
{
    this->_enable = !this->_enable;
    digitalWrite(this->_enablePin, !this->_enable);
}
void STP16Driver::Enable(bool en)
{
    if (this->_enable != en)
    {
        this->_enable = en;
        digitalWrite(this->_enablePin, !this->_enable);
    }
}
#pragma endregion

#pragma region Setting State
void STP16Driver::SetLEDs(LEDState states[STP16_LED_COUNT])
{
    bool change = false;
    for (size_t i = 0; i < STP16_LED_COUNT; i++)
    {
        if (this->_states[i] != states[i])
        {
            this->_states[i] = states[i];
            if (!change)
            {
                change = true;
            }
        }
    }

    if (change)
    {
        this->SendState();
    }
}

void STP16Driver::SetLEDs(uint8_t states[STP16_LED_COUNT])
{
    bool change = false;
    for (size_t i = 0; i < STP16_LED_COUNT; i++)
    {
        if (this->_states[i] != states[i])
        {
            this->_states[i] = (LEDState)states[i];
            if (!change)
            {
                change = true;
            }
        }
    }

    if (change)
    {
        this->SendState();
    }
}

void STP16Driver::SetLEDs(bool states[STP16_LED_COUNT])
{
    bool change = false;
    for (size_t i = 0; i < STP16_LED_COUNT; i++)
    {
        if (this->_states[i] != states[i])
        {
            this->_states[i] = (LEDState)states[i];
            if (!change)
            {
                change = true;
            }
        }
    }

    if (change)
    {
        this->SendState();
    }
}

void STP16Driver::SetLED(int index, LEDState state)
{
    if (index > 0 && index < STP16_LED_COUNT)
    {
        if (this->_states[index] != state)
        {
            this->_states[index] = state;
            this->SendState();
        }
    }
}

void STP16Driver::Clear()
{
    for (size_t i = 0; i < STP16_LED_COUNT; i++)
    {
        this->_states[i] = OFF;
    }
    this->SendState();
}
#pragma endregion

#pragma region Sending Data
void STP16Driver::SendState()
{
    byte highBits = 0;
    byte lowBits = 0;

    digitalWrite(this->_latchPin, HIGH);
    digitalWrite(this->_enablePin, HIGH);

    for (size_t i = 0; i < STP16_LED_COUNT / 2; i++)
    {
        lowBits |= (int)this->_states[i] ? 1 << i : 0;
    }

    for (size_t i = STP16_LED_COUNT / 2; i < STP16_LED_COUNT; i++)
    {
        
        highBits |= (int)this->_states[i] ? 1 << (i - 8) : 0;
    }

    Serial.println("Low");
    PrintBinary(lowBits, 8, LSB);
    Serial.println("High");
    PrintBinary(highBits, 8, LSB);
    
    this->Send(lowBits);
    this->Send(highBits);

    digitalWrite(this->_latchPin, LOW);
    digitalWrite(this->_enablePin, LOW);
}

void STP16Driver::Send(uint8_t state)
{
    shiftOut(this->_dataPin, this->_clockPin, LSBFIRST, state);
}
#pragma endregion