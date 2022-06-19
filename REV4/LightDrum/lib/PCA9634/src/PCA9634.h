#pragma once

#include <Arduino.h>
#include <Wire.h>

#pragma region Registers
namespace PCA9634Const
{
  const uint8_t MODE1 =   0x00;
  const uint8_t MODE2 =   0x01;
  const uint8_t PWM0 =    0x02;
  const uint8_t GRPPWM =  0x0A;
  const uint8_t GRPFREQ = 0x0B;
  const uint8_t LEDOUT0 = 0x0C;
  const uint8_t LEDOUT1 = 0x0D;
  const uint8_t SUBADR2 = 0x0F;
  const uint8_t SUBADR3 = 0x10;
  const uint8_t ALLCALL = 0x11;

  #pragma region Mode2 Register Masks
  const uint8_t M1_MODEMask =      0b00010000;
  const uint8_t M1_AutoINC =       0b10000000;
  const uint8_t M2_INVERTMask =    0b00010000;
  const uint8_t M2_OUTCHANGEMask = 0b00001000;
  const uint8_t M2_OUTDRIVEMask =  0b00000100;
  const uint8_t M2_DMBLNKMask =    0b00100000;
  #pragma endregion

  #pragma region Control Register Flags
  #pragma endregion

  const uint8_t SOFTRESETADDRESS = 0b0000011;
  const uint8_t OUTPUTCOUNT =              8;

  #pragma region Enums
  #pragma endregion

  #pragma region Reserved Addresses
  const uint8_t RESERVED_ADDRESSES[] = {
    0x00,
    0x03,
    0x04,
    0x05,
    0x06,
    0x07,
    0x70,
    0x78,
    0x79,
    0x7A,
    0x7B,
    0x7C,
    0x7D,
    0x7E,
    0x7F,
  };
  const int RESERVED_ADDRESS_LEN = 15;
  #pragma endregion
}

namespace PCAEnums
{
  enum OpMode
  {
    NORM = 0,
    // Put IC into sleep mode
    // This turns off the LED drivers and the internal oscillator
    SLEEP = 1,
  };

  enum Drive
  {
    // Sets the LED drivers to OPEN-DRAIN config
    OPEN = 0,
    // Sets the LED drivers to TOTEM POLE config
    TOTEM = 1,
  };

  enum BlinkMode
  {
    DIMMING = 0,
    BLINKING = 1
  };

  enum class OutputEnMode
  {
    // OE pin NOT Inverted: Use with no external drivers
    NORM = 0,
    // OE pin Inverted: Use with external drivers
    INVERT = 1
  };

  enum AutoIncOption
  {
    // Dont Auto-Increment
    NO_AUTO_INC         =   0b00,
    // Auto-Increment over ALL registers
    AUTO_INC_ALL        =   0b100,
    // Auto-Increment over individual brightness registers
    AUTO_INC_IND_REG    =   0b101,
    // Auto-Increment over global control registers
    AUTO_INC_GL_REG     =   0b110,
    // Auto-Increment over both individual and global registers
    AUTO_INC_IND_GL_REG =   0b111,
  };

  enum PWMState
  {
    // Driver is OFF
    OFF    = 0b00,
    // Driver is fully ON
    ON     = 0b01,
    // Driver is controlled through its individual PWM register
    PWM    = 0b10,
    // Driver is controlled through either its individual PWM register or the global PWM register
    GRP_PWM = 0b11,
  };
}

#pragma endregion


class PCA9634
{
public:
  PCA9634(
    TwoWire* wire,
    uint8_t address,
    int oePin
  );
  ~PCA9634();

  // Start device and set config options:
  //
  // drive: Totem Pole or Open-Collector
  // blinkMode: See Datasheet
  // oeMode: Normal or inverted OE pin config
  void Begin(
    PCAEnums::Drive drive,
    PCAEnums::BlinkMode blinkMode,
    PCAEnums::OutputEnMode oeMode
  );

  void Update();

  void SetState(int index, uint8_t value);

  void SetStates(uint8_t *buffer, int len);

  // Configure all LED output modes.
  void SetLEDOutput(PCAEnums::PWMState state);

  // Condifure individual LED output mode.
  void SetLEDOutput(int index, PCAEnums::PWMState state);

  // Condifure LED output modes.
  void SetLEDOutput(PCAEnums::PWMState *states);

  void SetGroupControl(PCAEnums::BlinkMode mode);

  void SetGroupFrequency(uint8_t freq);
  void SetGroupPWM(uint8_t pwm);

  // Read MODE1 & MODE2 Registers
  void ReadSettings();

  void ToggleEnable();
  void ToggleEnable(bool en);

  // Toggle device to sleep or normal mode
  void ToggleMode(PCAEnums::OpMode mode);
  // Toggle device to sleep or normal mode
  void ToggleMode(bool mode);
  PCAEnums::OpMode GetMode();

  void Test();

private:
  int oePin;
  bool outEnable = false;
  bool settingsChanged;
  bool LEDCtrlChanged;

  uint8_t groupFreq;
  uint8_t groupPWM;

  uint8_t address;
  PCAEnums::OpMode opMode = PCAEnums::OpMode::SLEEP;
  PCAEnums::Drive driveMode = PCAEnums::Drive::TOTEM;
  PCAEnums::BlinkMode blinkMode = PCAEnums::BlinkMode::DIMMING;
  PCAEnums::OutputEnMode oeMode = PCAEnums::OutputEnMode::NORM;

  TwoWire* wire;

  // RGB* pwmValues;
  uint8_t* state;
  PCAEnums::PWMState* pwmStates;

  //Testing ONLY
  uint8_t currentMode1Reg;
  uint8_t currentMode2Reg;

  void SendSettings();
  void SendLEDOutput();
  void SendGroup();

  void Send(PCAEnums::AutoIncOption incOpt, uint8_t reg, uint8_t data);
  void Send(PCAEnums::AutoIncOption incOpt, uint8_t startReg, uint8_t* data, uint8_t len);

  uint8_t SetControlByte(PCAEnums::AutoIncOption incOpt, uint8_t reg);

  // Checks the given address to make sure it's not reserved.
  // Returns TRUE if address is reserved.
  bool CheckAddress(uint8_t &address);
};