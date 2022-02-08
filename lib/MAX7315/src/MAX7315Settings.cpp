#include <Arduino.h>
#include "MAX7315Settings.h"
#include "Registers.h"

// #region Definitions
#define MASK_BLINK_EN              0b1
#define MASK_BLINK_FL             0b10
#define MASK_GLOBAL              0b100
#define MASK_INT_EN             0b1000
#define MASK_INT_OUTPUT_CTRL  0b110000
// #endregion

MAX7315Settings::MAX7315Settings() { }

MAX7315Settings::MAX7315Settings(uint8_t address)
{
    this->address = address;
}

MAX7315Settings::MAX7315Settings(
    uint8_t address,
    bool blinkEnable,
    bool blinkFlip,
    bool globalMode,
    bool interruptEnable)
{
    this->address = address;
    this->blinkEnable = blinkEnable ? 1 : 0;
    this->blinkFlip = blinkFlip ? 1 : 0;
    this->globalMode = globalMode ? 1 : 0;
    this->interruptEnable = interruptEnable ? 1 : 0;
}

uint8_t MAX7315Settings::GetSettings()
{
    uint8_t output = 0;
    output = Registers::SetBit(output, MASK_INT_EN,   this->interruptEnable);
    output = Registers::SetBit(output, MASK_GLOBAL,   this->globalMode);
    output = Registers::SetBit(output, MASK_BLINK_FL, this->blinkFlip);
    output = Registers::SetBit(output, MASK_BLINK_EN, this->blinkEnable);
    return output;
}