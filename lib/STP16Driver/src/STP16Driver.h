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
    const int* _dataPin;
    // Clock Pin
    int _clockPin;
    // Latch Pin
    int _latchPin;
    // LED Enable Pin
    // (OE Pin in Datasheet)
    int _enablePin;

    bool _enable;

    // LED Internal States
    LEDState* _states;
    uint8_t _state;

    // Send States to the shift register
    void SendState();

    void Send(uint8_t& state);
public:
    STP16Driver(
        const int dataPin,
        const int clockPin,
        const int latchPin,
        const int enablePin
    );
    ~STP16Driver();

    void Begin();

    void Clear();

    void SetLEDs(LEDState* states);
    void SetLEDs(uint8_t* states);
    void SetLEDs(bool* states);

    void SetLED(int& index, LEDState state);

    void Enable();
    void Enable(bool en);
};
