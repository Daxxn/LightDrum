#include <Arduino.h>
#include <SPI.h>
#include "SpectrumFilterPinout.h"

#define SPI_BUFFER_SIZE 8

uint8_t *spectrum;
int spectrumPins[8] = {
  Anlg::AudioPins::A0_PIN,
  Anlg::AudioPins::A1_PIN,
  Anlg::AudioPins::A2_PIN,
  Anlg::AudioPins::A3_PIN,
  Anlg::AudioPins::A4_PIN,
  Anlg::AudioPins::A5_PIN,
  Anlg::AudioPins::A6_PIN,
  Anlg::AudioPins::A7_PIN,
};

volatile boolean received;
volatile byte Slavereceived, Slavesend;

int bufferPos;
uint8_t buffer[SPI_BUFFER_SIZE];

ISR(SPI_STC_vect)
{
  byte c = SPDR;

  if (c == '\n')
  {
    received = true;
  }
}

void LoadBuffer()
{
  for (size_t i = 0; i < SPI_BUFFER_SIZE; i++)
  {
    buffer[i] = spectrum[i];
  }
}

void SendData()
{
  if (received)
  {
    SPDR = buffer[bufferPos];
    if (bufferPos >= SPI_BUFFER_SIZE)
    {
      bufferPos = 0;
      LoadBuffer();
    }
    else
    {
      bufferPos++;
    }
    received = false;
  }
}

void setup() {
  pinMode(Digitl::TestPins::OUT_PIN, OUTPUT);
  
  pinMode(MISO, OUTPUT);
  // pinMode(MOSI, INPUT);
  pinMode(SS, INPUT_PULLUP);
  pinMode(SCK, INPUT);

  received = false;

  SPCR |= _BV(SPE);
  SPI.attachInterrupt();

  spectrum = new uint8_t[8];
}

void loop() {
  for (size_t i = 0; i < 8; i++)
  {
    spectrum[i] = analogRead(spectrumPins[i]);
  }
}