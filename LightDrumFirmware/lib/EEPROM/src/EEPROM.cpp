#include <Arduino.h>
#include "EEPROM.h"

EEPROM::EEPROM(uint8_t &address)
{
  this->address = address;

}

EEPROM::~EEPROM()
{
  
}

uint8_t EEPROM::ReadByte()
{
  
  this->currentLocation++;
}

uint8_t EEPROM::ReadByte(uint8_t location)
{
  this->currentLocation = location;
}

uint8_t *EEPROM::ReadPage()
{
  
}

uint8_t *EEPROM::ReadPage(uint8_t location)
{
  
}