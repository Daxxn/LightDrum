#pragma once

#include <Arduino.h>

namespace LCDConstants
{
  const uint8_t CLEAR_DISPLAY =           0b1;
  const uint8_t RETURN_HOME =            0b10;
  const uint8_t CURSOR_EN_OFFSET =       0b10;
  const uint8_t CURSOR_DIR_OFFSET =      0b10;
  const uint8_t SCREEN_SHIFT_OFFSET =     0b0;
  const uint8_t ENABLE_OFFSET =         0b100;
  const uint8_t CURSOR_OFFSET =          0b10;
  const uint8_t CURSOR_BLINK_OFFSET =     0b1;
  const uint8_t DATA_LEN_OFFSET =     0b10000;
  const uint8_t LINE_NUM_OFFSET =      0b1000;
  const uint8_t FONT_SIZE_OFFSET =      0b100;
  const uint8_t CGRAM_OFFSET =      0b1000000;
  const uint8_t DDRAM_OFFSET =     0b10000000;
  const uint8_t SHIFT_LOWER_LINE = 0b11000000;
  const uint8_t BUFFER_LIMIT =             40;
  const uint8_t BUFFER_SIZE =              16;
  const uint8_t WRITE_DELAY =              10;
  const uint8_t BLANK_CHAR =             0x20;
  const uint8_t DATA_BIT_LENGTH =           8;
};

enum Line {
  TOP = 0,
  BOT = 1
};

class LCDScreen2
{
public:
  LCDScreen2(
    const int dataPins[8],
    int rsPin,
    int rwPin,
    int enPin
  );

  ~LCDScreen2();
  LCDScreen2(const LCDScreen2& other) = delete;

  void Begin();
  void End();

  void Clear();
  void ReturnHome();

  void SetBuffers(const uint8_t* top, const uint8_t* bot);
  void SetBuffers(String top, String bot);
  
  void SetBuffer(Line line, uint8_t* data);
  void SetBuffer(Line line, String data);


  void Test();
private:
  // Parallel Data Pins
  const int* dataPins;
  // Register Select Pin
  int rsPin;
  // Read / Write Pin
  int rwPin;
  // Enable Pin
  int enPin;

  bool screenEnable = true;
  bool cursor = true;
  bool cursorBlink = false;
  bool direction = true;
  bool shiftScreen = false;
  bool twoLineMode = true;
  bool bigFont = false;

  // Screen busy flag - [1 || 0]
  uint8_t _busy;
  // The Screens 7-bit Adress Counter
  uint8_t _ac;

  // Timeout when waiting for the screen to be available
  const uint8_t waitTimeout = 255;

  uint8_t* topBuffer;
  uint8_t* botBuffer;
  const uint8_t bufferSize = 16;

  // Sets the 8 individual data lines
  void SetDataLines(uint8_t byte);
  //Resets and initializes the screen manually.
  // Shouldnt be needed. The screen should init on its own...
  void InitByInstruction();
  // Sends the specific init signal during an Init-By-Instruction
  void InitResetSignal();
  // Sets the display mode and activates the LCD Screen
  void InitScreen();
  // Sets the display mode and activates the LCD Screen
  void InitScreen(bool enable, bool cursor, bool blink);
  // Sets the cursors behavior
  void InitEntryMode();
  // Sets the cursors behavior
  void InitEntryMode(bool writeDir, bool screenShift);
  // Sets the line mode and font size
  void InitFunctionSet();
  // Sets the line mode and font size
  void InitFunctionSet(bool twoLineMode, bool bigFont);

  // sets the binary value at an address offset
  uint8_t SetState(uint8_t offset, bool state);
  // sets the binary value at an address offset
  uint8_t SetState(uint8_t offset, uint8_t state);

  // Pulses the enable line to send data to the screen.
  void SendEnable();

  // Reads the busy flag from the read register.
  void ReadBusy();

  // Waits for the screen to set its busy flag to 0 before continuing.
  // Also has a timeout as well.
  void WaitForScreen();

  // Shifts the buffer to the next line
  void ShiftLine();

  // Prepare the line buffer but dont send yet
  void PrepareBuffer(Line line, const uint8_t* data);

  // Sends an individual character to the screen
  void SendChar(uint8_t ch);

  // Sends a full line to the screen.
  void SendLine(Line line);
};