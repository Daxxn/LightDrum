#include <Arduino.h>
#include <SPI.h>
#include "ADC0838.h"

ADC0838::ADC0838(int csPin, int sePin, int statusPin, ADC0838Enums::Signal signalType)
{
  this->csPin = csPin;
  this->sePin = sePin;
  this->statusPin = statusPin;
  this->signal = signalType;
  this->data = new uint8_t[ADC0838_CHANNEL_COUNT];
  this->sePinEnable = true;
}

ADC0838::ADC0838(int csPin, int statusPin, ADC0838Enums::Signal signalType)
{
  this->csPin = csPin;
  this->sePinEnable = false;
  this->statusPin = statusPin;
  this->signal = signalType;
  this->data = new uint8_t[ADC0838_CHANNEL_COUNT];
}

ADC0838::~ADC0838()
{
  delete[] this->data;
}

void ADC0838::Begin()
{
  SPI.begin();

  pinMode(this->csPin, OUTPUT);
  if (this->sePinEnable)
  {
    // Keeps the ADCs output as MSB first.
    pinMode(this->sePin, OUTPUT);
    digitalWrite(this->sePin, HIGH);
  }
  pinMode(this->statusPin, INPUT_PULLUP);
}

void ADC0838::Update()
{
  for (size_t i = 0; i < ADC0838Consts::SNGL_CH_COUNT; i++)
  {
    ReadChannel(i);
  }
}

void ADC0838::ReadChannel(int channel)
{
  this->ConfigureMUXBit(channel);
  if (this->sePinEnable)
  {
    digitalWrite(this->sePin, HIGH);
  }
  digitalWrite(this->csPin, LOW);
  SPI.beginTransaction(ADC0838Consts::SPI_SETTING);
  SPI.transfer(this->muxBit);
  SPI.transfer(0);
  if (digitalRead(this->statusPin) == HIGH)
  {
    for (size_t i = 0; i < 4; i++)
    {
      if (digitalRead(this->statusPin) == LOW)
      {
        break;
      }
    }
  }
  if (this->sePinEnable)
  {
    digitalWrite(this->sePin, LOW);
  }
  this->data[channel] = SPI.transfer(0);
  SPI.endTransaction();
  digitalWrite(this->csPin, HIGH);
}

void ADC0838::ConfigureMUXBit(int channel)
{
  this->muxBit = ADC0838Consts::MUX_LOOKUP[channel];
}

uint8_t ADC0838::GetValue(int channel)
{
  return this->data[channel];
}

#pragma region Debugging
void ADC0838::Test()
{
  
}

void ADC0838::Debug()
{
  
}
#pragma endregion