/*
Library for communicating with the TI ADC0838 8 channel
Successive Approximation A/D converter IC.

Its a relatively simple library currently. Would like to add the
ability to read differentailly in the future. It shouldnt be too
hard. It will require alot of changes to the way data is read and
stored. Will also need to add some methods to convert the
differential reading and add them to a uint16_t array.
*/

#pragma once

#include <Arduino.h>
#include <SPI.h>

#pragma region Definitions
#define ADC0838_CHANNEL_COUNT 8
#pragma endregion

namespace ADC0838Consts
{
  // CONST Single channel count
  const int SNGL_CH_COUNT = 8;
  // CONST Differential channel count
  const int DIFF_CH_COUNT = 4;

  const uint8_t MUX_LOOKUP[8] = {
    0b11000,
    0b11100,
    0b11001,
    0b11101,
    0b11010,
    0b11110,
    0b11011,
    0b11111
  };

  const SPISettings SPI_SETTING(100000, MSBFIRST, SPI_MODE0);
} // namespace ACD0838Consts


namespace ADC0838Enums
{
  enum class Signal
  {
    SINGLE = 1,
    DIFF = 0,
  };

  enum class OddEven
  {
    EVEN = 0,
    ODD = 1,
  };
} // namespace ADC0838Enums


class ADC0838
{
public:
  // Used when the MC is set up to control the SE pin.
  ADC0838(int csPin, int sePin, int statusPin, ADC0838Enums::Signal signalType);
  // Used when the SE pin is strapped externally.
  ADC0838(int csPin, int statusPin, ADC0838Enums::Signal signalType);
  ~ADC0838();

  void Begin();

  // Reads all 8 ADC channels and saves the data to the array.
  void Update();

  // Get an individual value from the data array.
  uint8_t GetValue(int channel);

  // Only used to test functionality.
  void Test();
  // Sends debug data.
  void Debug();
private:
  // Chip select pin
  // OUTPUT
  int csPin;
  // Selects either MSB or LSB first modes.
  // HIGH = MSB First
  // OUTPUT
  int sePin;
  // ADC conversion status pin
  // INPUT
  int statusPin;

  // Set by the SE Pin. The SE pin doesnt have to be controlled by the MC.
  // TRUE = MC Controlled
  bool sePinEnable;

  // Conversion status of the ADC
  // 1 = Conversion in progress
  uint8_t convStatus;

  // ADC data
  // 8 bytes
  uint8_t *data;

  // Not sure anymore. Its not used anywere.
  uint8_t selectBit;
  // ADC channel Signal type
  // SINGLE = single pin per channel
  // DIFF = 2 pins per channel in a differential signal configuration
  ADC0838Enums::Signal signal;
  // Set when reading a channel. Byte mask sent to configure the ADC before a read.
  // Internal ONLY.
  uint8_t muxBit;

  // Reads the provided channel from the ADC and stores the result in the data array.
  void ReadChannel(int channel);

  // Configures the byte to be sent to the ADC.
  // sets the type of read and what channel to read.
  void ConfigureMUXBit(int channel);
};