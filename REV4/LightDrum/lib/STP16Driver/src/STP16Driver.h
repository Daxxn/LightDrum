#pragma once
#include <Arduino.h>

// #region Definitions
#define STP16_LED_COUNT 16
#define STP16_LED_COUNT_HALF 8
// #endregion

#pragma region Enums
enum LEDState
{
    ON = 1,
    OFF = 0,
};
#pragma endregion

class STP16Driver
{
private:
    // Serial Data Pin
    int _dataPin;
    // Clock Pin
    int _clockPin;
    // Latch Pin
    int _latchPin;
    // LED Enable Pin
    // (OE Pin in Datasheet)
    int _enablePin;

    bool _enable;

    // LED Internal States
    LEDState _states[16];

    // Send States to the shift register
    void SendState();

    void Send(uint8_t state);
public:
    STP16Driver(int dataPin, int clockPin, int latchPin, int enablePin);

    void Begin();

    void Clear();

    void SetLEDs(LEDState states[STP16_LED_COUNT]);
    void SetLEDs(uint8_t states[STP16_LED_COUNT]);
    void SetLEDs(bool states[STP16_LED_COUNT]);

    void SetLED(int index, LEDState state);

    void Enable();
    void Enable(bool en);
};
