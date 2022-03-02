#include <Arduino.h>
#include "STP16Driver.h"
#include "Logger.h"

#pragma region Constructors
STP16Driver::STP16Driver(
    int dataPin,
    int clockPin,
    int latchPin,
    int enablePin
)
{
    this->_dataPin = dataPin;
    this->_clockPin = clockPin;
    this->_latchPin = latchPin;
    this->_enablePin = enablePin;
    this->_states = new uint8_t[STP16Constants::LED_COUNT];
    this->_enable = true;
}

STP16Driver::~STP16Driver()
{
    delete[] this->_states;
}
#pragma endregion

#pragma region Initialization
void STP16Driver::Begin()
{
    pinMode(this->_dataPin, OUTPUT);
    pinMode(this->_clockPin, OUTPUT);
    pinMode(this->_latchPin, OUTPUT);
    pinMode(this->_enablePin, OUTPUT);

    memset(this->_states, 0, STP16Constants::LED_COUNT);

    this->SendStates();
}
#pragma endregion

#pragma region Enable/Disable
void STP16Driver::Enable()
{
    this->_enable = !this->_enable;
    digitalWrite(this->_enablePin, this->_enable);
}
void STP16Driver::Enable(bool en)
{
    if (this->_enable == en)
    {
        this->_enable = !en;
        digitalWrite(this->_enablePin, this->_enable);
    }
}

bool STP16Driver::IsEnabled()
{
    return !this->_enable;
}
#pragma endregion

#pragma region Setting State
void STP16Driver::SetLEDs(LEDState* states)
{
    memcpy(this->_states, states, 16);
    // for (size_t i = 0; i < STP16Constants::LED_COUNT; i++)
    // {
    //     if (this->_states[i] != states[i])
    //     {
    //         this->_states[i] = states[i];
    //         if (!change)
    //         {
    //             change = true;
    //         }
    //     }
    // }

    this->SendStates();
}

void STP16Driver::SetLEDs(uint8_t* states)
{
    static bool change = false;
    for (size_t i = 0; i < STP16Constants::LED_COUNT; i++)
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
        this->SendStates();
    }
}

void STP16Driver::SetLEDs(bool* states)
{
    static bool change = false;
    for (size_t i = 0; i < STP16Constants::LED_COUNT; i++)
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
        this->SendStates();
    }
}

void STP16Driver::SetLED(uint8_t& index, uint8_t state)
{
    if (state < 0 || state > 1) return;

    if (index > 0 && index < STP16Constants::LED_COUNT)
    {
        if (this->_states[index] != state)
        {
            this->_states[index] = state;
            this->SendStates();
        }
    }
}

void STP16Driver::ToggleLED(uint8_t& index)
{
    if (index > 0 && index < STP16Constants::LED_COUNT)
    {
        this->SetLED(index, !this->_states[index]);
    }
}

void STP16Driver::Clear()
{
    for (size_t i = 0; i < STP16Constants::LED_COUNT; i++)
    {
        this->_states[i] = OFF;
    }
    this->SendStates();
}
#pragma endregion

#pragma region Sending Data
void STP16Driver::SendStates()
{
    static uint8_t highBits = 0;
    static uint8_t lowBits = 0;

    digitalWrite(this->_latchPin, HIGH);
    digitalWrite(this->_enablePin, HIGH);

    Logger::LogArr((uint8_t*)this->_states, STP16Constants::LED_COUNT);

    // for (size_t i = 0; i < STP16Constants::LED_COUNT_HALF; i++)
    // {
    //     lowBits |= (int)this->_states[i] ? 1 << i : 0;
    // }

    // for (size_t i = STP16Constants::LED_COUNT_HALF; i < STP16Constants::LED_COUNT; i++)
    // {
        
    //     highBits |= (int)this->_states[i] ? 1 << (i - 8) : 0;
    // }

    for (size_t h = STP16Constants::LED_COUNT_HALF, l = 0; h < STP16Constants::LED_COUNT; h++, l++)
    {
        lowBits |= ((int)this->_states[l] << l);
        highBits |= ((int)this->_states[h] << l);
    }

    Logger::LogByte("LO By", lowBits);
    Logger::LogByte("HI By", highBits);
    
    this->Send(lowBits);
    this->Send(highBits);

    digitalWrite(this->_latchPin, LOW);
    digitalWrite(this->_enablePin, this->_enable);
}

void STP16Driver::Send(uint8_t& state)
{
    shiftOut(
        this->_dataPin,
        this->_clockPin,
        LSBFIRST, state);
}
#pragma endregion