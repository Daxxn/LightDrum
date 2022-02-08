#pragma once
#include <Arduino.h>

class MAX7315Settings
{
private:
public:
    // The MAX7315s I2C Address
    uint8_t address = 0;
    // Enable blink mode. (See Datasheet)
    uint8_t blinkEnable = 0;
    // Flip blink mode. (See Datasheet)
    uint8_t blinkFlip = 0;
    // Enable Global PWM commands. (See Datasheet)
    uint8_t globalMode = 1;
    // Enable Interrupt.
    // !! Not Implemented Yet !!
    //  ---- Need to add an interrupt handler.
    uint8_t interruptEnable = 1;
    // Default Constructor
    // Address is all address lines tied to ground
    MAX7315Settings();
    MAX7315Settings(uint8_t address);

    // IC Settings:
    // I2C Address
    // Blink Enable
    // Blink Flip
    // Global Mode
    // Interrupt Enable
    MAX7315Settings(
        uint8_t address,
        bool blinkEnable,
        bool blinkFlip,
        bool globalMode,
        bool interruptEnable
    );

    // Gets the settings ready to be sent to the MAX7315
    uint8_t GetSettings();
};