#include <Arduino.h>
#include "LCDScreen2.h"
#include "Logger.h"

LCDScreen2::LCDScreen2(
  const int dataPins[],
  int rsPin,
  int rwPin,
  int enPin
)
{
  this->dataPins = dataPins;
  this->rsPin = rsPin;
  this->rwPin = rwPin;
  this->enPin = enPin;

  this->topBuffer = new uint8_t[LCDConstants::BUFFER_SIZE];
  this->botBuffer = new uint8_t[LCDConstants::BUFFER_SIZE];

  memset(
    this->topBuffer,
    LCDConstants::BLANK_CHAR,
    LCDConstants::BUFFER_SIZE
  );
  memset(
    this->botBuffer,
    LCDConstants::BLANK_CHAR,
    LCDConstants::BUFFER_SIZE
  );
}

LCDScreen2::~LCDScreen2()
{
  this->End();
  delete[] this->topBuffer;
  delete[] this->botBuffer;
}

void LCDScreen2::Begin()
{
  pinMode(this->enPin, OUTPUT);
  pinMode(this->rsPin, OUTPUT);
  pinMode(this->rwPin, OUTPUT);

  digitalWrite(this->enPin, LOW);
  digitalWrite(this->rsPin, LOW);
  digitalWrite(this->rwPin, LOW);

  for (size_t i = 0; i < 8; i++)
  {
    pinMode(this->dataPins[i], OUTPUT);
    digitalWrite(this->dataPins[i], LOW);
  }
  
  delay(100);

  this->InitFunctionSet();
  delayMicroseconds(50);
  this->InitScreen();
  delayMicroseconds(50);
  this->InitEntryMode();
  delayMicroseconds(50);
}

#pragma region Initialization Methods
void LCDScreen2::InitFunctionSet()
{
  this->InitFunctionSet(this->twoLineMode, this->bigFont);
}

void LCDScreen2::InitFunctionSet(bool twoLineMode, bool bigFont)
{
  digitalWrite(this->rsPin, LOW);
  digitalWrite(this->rwPin, LOW);
  uint8_t initState =
    0b100000
    // This is for the parallel port. 4 or 8 bit modes.
    // Im just going to use 8 bit mode for now.
    | this->SetState(LCDConstants::DATA_LEN_OFFSET, true)
    | this->SetState(LCDConstants::LINE_NUM_OFFSET, twoLineMode)
    | this->SetState(LCDConstants::FONT_SIZE_OFFSET, bigFont);
  this->SetDataLines(initState);
  this->SendEnable();
  delayMicroseconds(37);
}

void LCDScreen2::InitScreen()
{
  this->InitScreen(this->screenEnable, this->cursor, this->cursorBlink);
}

void LCDScreen2::InitScreen(bool enable, bool cursor, bool blink)
{
  digitalWrite(this->rsPin, LOW);
  digitalWrite(this->rwPin, LOW);
  byte state =
    0b1000
    | this->SetState(LCDConstants::ENABLE_OFFSET, enable)
    | this->SetState(LCDConstants::CURSOR_EN_OFFSET, cursor)
    | this->SetState(LCDConstants::CURSOR_BLINK_OFFSET, blink);
  
  this->SetDataLines(state);
  this->SendEnable();
}

void LCDScreen2::InitEntryMode()
{
  this->InitEntryMode(this->direction, this->shiftScreen);
}

void LCDScreen2::InitEntryMode(bool writeDir, bool screenShift)
{
  digitalWrite(this->rsPin, LOW);
  digitalWrite(this->rwPin, LOW);
  uint8_t initState =
    0b100
    | this->SetState(LCDConstants::CURSOR_DIR_OFFSET, writeDir)
    | this->SetState(LCDConstants::SCREEN_SHIFT_OFFSET, screenShift);
  this->SetDataLines(initState);
  this->SendEnable();
}

void LCDScreen2::End()
{
  this->InitScreen(false, true, true);
}
#pragma endregion

#pragma region Util Methods
void LCDScreen2::Test()
{
  Logger::LogArr("Top Buffer", this->topBuffer, 16);
}

uint8_t LCDScreen2::SetState(uint8_t offset, bool state)
{
  return offset & (state ? 0xFF : 0x0);
}

uint8_t LCDScreen2::SetState(uint8_t offset, uint8_t state)
{
  return offset & state;
}

void LCDScreen2::SetDataLines(uint8_t b)
{
  for (uint8_t i = 0; i < LCDConstants::DATA_BIT_LENGTH; i++)
  {
    digitalWrite(this->dataPins[i], bitRead(b, i));
  }
}

void LCDScreen2::SendEnable()
{
  delayMicroseconds(12);
  digitalWrite(this->enPin, HIGH);
  delayMicroseconds(LCDConstants::WRITE_DELAY);
  digitalWrite(this->enPin, LOW);
  this->SetDataLines(0);
}
#pragma endregion

#pragma region General Screen Control
void LCDScreen2::Clear()
{
  digitalWrite(this->rsPin, LOW);
  digitalWrite(this->rwPin, LOW);
  this->SetDataLines(1);
  this->SendEnable();
  delay(2);

  memset(this->topBuffer, 0x20, LCDConstants::BUFFER_SIZE);
  memset(this->botBuffer, 0x20, LCDConstants::BUFFER_SIZE);
  // this->ReturnHome();
}

void LCDScreen2::ReturnHome()
{
  digitalWrite(this->rsPin, LOW);
  digitalWrite(this->rwPin, LOW);
  this->SetDataLines(2);
  this->SendEnable();
  delay(2);
}

void LCDScreen2::ShiftLine()
{
  digitalWrite(this->rsPin, LOW);
  digitalWrite(this->rwPin, LOW);
  this->SetDataLines(LCDConstants::SHIFT_LOWER_LINE);
  this->SendEnable();
  delay(10);
}
#pragma endregion

#pragma region Screen Buffer Control
void LCDScreen2::SetBuffers(const uint8_t* top, const uint8_t* bot)
{
  this->PrepareBuffer(Line::TOP, top);
  this->PrepareBuffer(Line::BOT, bot);
  this->SendLine(Line::TOP);
  this->SendLine(Line::BOT);
}

void LCDScreen2::SetBuffer(Line line, uint8_t* data)
{
  Serial.println("Prep Bfr");
  this->PrepareBuffer(line, data);
  this->SendLine(line);
}

void LCDScreen2::PrepareBuffer(Line line, const uint8_t* data)
{
  if (line == Line::TOP)
  {
    memcpy(
      this->topBuffer,
      data,
      LCDConstants::BUFFER_SIZE
    );
  }
  else
  {
    memcpy(
      this->botBuffer,
      data,
      LCDConstants::BUFFER_SIZE
    );
  }
}

void LCDScreen2::SendLine(Line line)
{
  this->ReturnHome();
  if (line == Line::BOT)
  {
    this->ShiftLine();
    for (size_t i = 0; i < LCDConstants::BUFFER_SIZE; i++)
    {
      this->SendChar(this->botBuffer[i]);
    }
  }
  else
  {
    for (size_t i = 0; i < LCDConstants::BUFFER_SIZE; i++)
    {
      this->SendChar(this->topBuffer[i]);
    }
  }
}

void LCDScreen2::SendChar(uint8_t ch)
{
  digitalWrite(this->rsPin, HIGH);
  digitalWrite(this->rwPin, LOW);
  this->SetDataLines(ch);
  this->SendEnable();
  delayMicroseconds(50);
}
#pragma endregion