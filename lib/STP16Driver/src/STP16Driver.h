#pragma once
#include <Arduino.h>

// #region Definitions
namespace STP16Constants
{
    const int LED_COUNT = 16;
    const int LED_COUNT_HALF = 8;
}

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

    // Enables all LEDs.
    // -- Inverted --
    bool _enable;

    // LED Internal States
    uint8_t* _states;
    uint8_t _state;

    // Send States to the shift register
    void SendStates();

    void Send(uint8_t& state);
public:
    STP16Driver(
        int dataPin,
        int clockPin,
        int latchPin,
        int enablePin
    );
    ~STP16Driver();

    // Start the driver and set initial state.
    void Begin();

    // Turn all LEDs off
    void Clear();

    // Send an array of ON/OFF states to the LED driver
    void SetLEDs(LEDState* states);
    // Send an array of 1/0 states to the LED driver
    void SetLEDs(uint8_t* states);
    // Send an array of true/false states to the LED driver
    void SetLEDs(bool* states);

    // Send an int representing the LED states to the driver
    void SetLEDs(uint16_t& states);

    // Set an individual LEDs ON/OFF state
    void SetLED(uint8_t& index, uint8_t state);

    void ToggleLED(uint8_t& index);

    // Toggle all LEDs ON or OFF
    void Enable();
    // Set all LEDs ON or OFF
    void Enable(bool en);

    // Get all enable state
    bool IsEnabled();
};
