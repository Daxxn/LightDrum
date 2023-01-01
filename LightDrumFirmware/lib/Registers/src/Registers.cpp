#include <Arduino.h>
#include "Registers.h"

Registers::Registers(uint8_t mask[], uint8_t length)
{
    this->_length = length;
    this->_mask[length] = *mask;
}

uint8_t Registers::GetMask(uint8_t data[])
{
    uint8_t output = 0;
    for (uint8_t i = 0; i < this->_length; i++)
    {
        output = (output << 1) | (data[i] & this->_mask[i]);
    }
    return output;
}

uint8_t Registers::SetMask(uint8_t registerInput, uint8_t mask, bool state)
{
    return registerInput | (uint8_t(state) & mask);
}

uint8_t Registers::SetMask(uint8_t registerInput, uint8_t mask, uint8_t state)
{
    return registerInput | (state & mask);
}

uint8_t Registers::SetBit(uint8_t registerInput, uint8_t mask, bool state)
{
    if (state)
    {
        return registerInput | (0xFF & mask);
    }
    return registerInput;
    
}

uint8_t Registers::SetBit(uint8_t registerInput, uint8_t mask, uint8_t state)
{
    if (state == 1)
    {
        return registerInput | (0xFF & mask);
    }
    return registerInput;
    
}