#pragma once

#include <Arduino.h>

class Registers
{
public:
    Registers(uint8_t mask[], uint8_t length);
    // Sets a register mask acording to an array.
    // Each index of the array is used as the mask.
    uint8_t GetMask(uint8_t data[]);
    // Sets the registers mask (registerInput) to the new value (state) at position specified (mask)
    static uint8_t SetMask(uint8_t registerInput, uint8_t mask, bool state);
    // Sets the registers mask (registerInput) to the new value (state) at position specified (mask)
    static uint8_t SetMask(uint8_t registerInput, uint8_t mask, uint8_t state);
    // Sets the registers mask (registerInput) to the new value (state) at position specified (mask)
    static uint8_t SetBit(uint8_t registerInput, uint8_t mask, bool state);
    // Sets the registers mask (registerInput) to the new value (state) at position specified (mask)
    static uint8_t SetBit(uint8_t registerInput, uint8_t mask, uint8_t state);
private:
    uint8_t _length;
    uint8_t _mask[];
};