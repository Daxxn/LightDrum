#include <Arduino.h>
#include <Wire.h>
#include "PCA9634.h"
#include "Registers.h"

PCA9634::PCA9634(
  TwoWire* wire,
  uint8_t address,
  int oePin,
  bool extDriver = false
)
{
  // if (CheckAddress(address)) return;
  this->wire = wire;
  this->address = address;
  this->oePin = oePin;
  this->state = new uint8_t[8];
  this->pwmStates = new PCAEnums::PWMState[8];
  memset(this->pwmStates, (int)PCAEnums::PWMState::PWM, sizeof(int) * 8);

  if (extDriver)
  {
    this->oeMode = PCAEnums::OutputEnMode::INVERT;
    this->driveMode = PCAEnums::Drive::TOTEM;
  }
}

PCA9634::~PCA9634()
{
  delete[] this->state;
  delete[] this->pwmStates;
}

bool PCA9634::CheckAddress(uint8_t &address)
{
  for (auto &&add : PCA9634Const::RESERVED_ADDRESSES)
  {
    if (add == address)
    {
      return true;
    }
  }
  return false;
}

bool PCA9634::Begin()
{
  pinMode(oePin, OUTPUT);
  digitalWrite(oePin, LOW);

  delay(10);

  this->ReadSettings();

  if (this->currentMode1Reg == 0b10010001) return false;

  this->opMode = PCAEnums::OpMode::NORM;

  this->SendSettings();
  return true;
}

void PCA9634::Update()
{
  if (this->opMode == PCAEnums::OpMode::NORM)
  {
    this->Send(
      PCAEnums::AutoIncOption::AUTO_INC_IND_REG,
      PCA9634Const::PWM0,
      this->state,
      PCA9634Const::OUTPUTCOUNT
    );
    this->SendLEDOutput();
    this->SendSettings();
  }
  else
  {
    this->SendSettings();
  }
}

void PCA9634::SetLEDOutput(PCAEnums::PWMState state)
{
  memset(this->pwmStates, (int)state, PCA9634Const::OUTPUTCOUNT);
}

void PCA9634::SetLEDOutput(int index, PCAEnums::PWMState state)
{
  if (index < 0 || index > PCA9634Const::OUTPUTCOUNT) return;
  this->pwmStates[index] = state;
}

void PCA9634::SetLEDOutput(PCAEnums::PWMState *states)
{
  memcpy(this->pwmStates, states, 8);
}

void PCA9634::ToggleEnable()
{
  this->outEnable = !this->outEnable;
  this->ToggleEnable(this->outEnable);
}

void PCA9634::ToggleEnable(bool en)
{
  digitalWrite(this->oePin, this->outEnable);
}

void PCA9634::ToggleMode(PCAEnums::OpMode mode)
{
  this->opMode = mode;
  this->settingsChanged = true;
}

void PCA9634::ToggleMode(bool mode)
{
  this->opMode = mode ? PCAEnums::OpMode::NORM : PCAEnums::OpMode::SLEEP;
  this->settingsChanged = true;
}

PCAEnums::OpMode PCA9634::GetMode()
{
  return this->opMode;
}

void PCA9634::ReadSettings()
{
  uint8_t ctrl = SetControlByte(
    PCAEnums::AutoIncOption::AUTO_INC_ALL,
    (uint8_t)PCA9634Const::MODE1
  );

  this->wire->beginTransmission(address);
  this->wire->write(ctrl);
  this->wire->endTransmission();

  this->wire->requestFrom(address, (uint8_t)2);
  if (this->wire->available() >= 2)
  {
    this->currentMode1Reg = this->wire->read();
    this->currentMode2Reg = this->wire->read();
  }
  else
  {
    Serial.println("Didnt receive enough bytes.");
  }
}

void PCA9634::SendSettings()
{
  if (!this->settingsChanged) return;
  
  uint8_t mode1Data = Registers::SetMask(
    0x00,
    PCA9634Const::M1_MODEMask,
    (uint8_t)this->opMode
  );
  uint8_t mode2Data = Registers::SetMask(
    0x00,
    PCA9634Const::M2_OUTDRIVEMask,
    (uint8_t)this->driveMode
  );
  mode2Data = Registers::SetMask(
    mode2Data,
    PCA9634Const::M2_INVERTMask,
    (uint8_t)this->oeMode
  );
  mode2Data = Registers::SetMask(
    mode2Data,
    PCA9634Const::M2_DMBLNKMask,
    (uint8_t)this->blinkMode
  );
  uint8_t data[2] = {
    mode1Data,
    mode2Data
  };
  this->Send(
    PCAEnums::AutoIncOption::AUTO_INC_ALL,
    PCA9634Const::MODE1,
    data, 2
  );
  this->settingsChanged = false;
}

void PCA9634::SendLEDOutput()
{
  uint8_t byte1 = 0;
  uint8_t byte2 = 0;
  uint8_t output[2] = {};
  
  for (size_t i = 0, j = 4; i < PCA9634Const::OUTPUTCOUNT / 2; i++, j++)
  {
    byte1 |= (uint8_t)this->pwmStates[i] << (i * 2);
    byte2 |= (uint8_t)this->pwmStates[j] << (i * 2);
  }
  output[0] = byte1;
  output[1] = byte2;
  
  this->Send(
    PCAEnums::AutoIncOption::AUTO_INC_ALL,
    PCA9634Const::LEDOUT0,
    output, 2
  );
}

void PCA9634::Send(
  PCAEnums::AutoIncOption incOpt,
  uint8_t reg,
  uint8_t data)
{
  uint8_t ctrl = this->SetControlByte(incOpt, reg);
  this->wire->beginTransmission(address);
  this->wire->write(ctrl);
  this->wire->write(data);
  this->wire->endTransmission();
}

void PCA9634::Send(
  PCAEnums::AutoIncOption incOpt,
  uint8_t startReg,
  uint8_t* data,
  uint8_t len)
{
  uint8_t ctrl = this->SetControlByte(incOpt, startReg);
  this->wire->beginTransmission(address);
  this->wire->write(ctrl);
  this->wire->write(data, len);
  this->wire->endTransmission();
}

void PCA9634::SetState(int index, uint8_t value)
{
  if (index >= 0 && index < PCA9634Const::OUTPUTCOUNT)
  {
    this->state[index] = value;
  }
}

void PCA9634::SetStates(uint8_t *buffer, int len)
{
  if (len > 8) return;
  for (size_t i = 0; i < 8; i++)
  {
    this->state[i] = buffer[i];
  }
}

uint8_t PCA9634::SetControlByte(PCAEnums::AutoIncOption incOpt, uint8_t reg)
{
  return ((uint8_t)incOpt << 5) | reg;
}

void PCA9634::Test()
{
  this->ReadSettings();
  Serial.print(this->currentMode1Reg);
  Serial.print(" : ");
  Serial.println(this->currentMode2Reg);
}