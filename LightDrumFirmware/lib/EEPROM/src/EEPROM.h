#pragma once

#include <Arduino.h>

namespace EEPROMConsts
{
  const int MIN_LOCATION = 0x00;
  const int MAX_LOCATION = 0xFF;
}

class EEPROM
{
public:
  EEPROM(uint8_t &address);
  ~EEPROM();
  // Sequentially Read each page and write it to the Buffer
  uint8_t *ReadPage();
  // Read the page at the specified location
  uint8_t *ReadPage(uint8_t location);
  // Sequentially read each byte and write it to the Buffer
  uint8_t ReadByte();
  // Read the byte at the specified location
  uint8_t ReadByte(uint8_t location);

  void WritePage(uint8_t *data, int len);
  void WriteByte(uint8_t data);

  uint8_t *Buffer;
  uint8_t BufferSize;
private:
  uint8_t address;
  uint8_t currentLocation;
  void Send();
  void Read();
};