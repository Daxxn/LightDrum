#ifndef LCDScreen_h
#define LCDScreen_h

#include <Arduino.h>

// #region Define Constants
enum DataLength
{
    HALF = 4,
    FULL = 8
};

#define LCD_WRITE_DELAY 10

// #region Options Offsets
#define LCD_CLEAR_DISPLAY 0b1
#define LCD_RETURN_HOME 0b10

// Cursor Address for both `Cursor Enable` and `Cursor Direction`.
#define LCD_CURSOR_DIR_OFFSET   0b10
#define LCD_SCREEN_SHIFT_OFFSET  0b0

#define LCD_ENABLE_OFFSET     0b100
#define LCD_CURSOR_OFFSET      0b10
#define LCD_CURSOR_BLINK_OFFSET 0b1

#define LCD_DATA_LEN_OFFSET  0b10000
#define LCD_LINE_NUM_OFFSET   0b1000
#define LCD_FONT_SIZE_OFFSET   0b100

#define LCD_CGRAM_OFFSET  0b1000000
#define LCD_DDRAM_OFFSET 0b10000000

#define LCD_LINE_COUNT 40
// #endregion
// #endregion

class LCDScreen
{
private:
    // Parallel Data Pins numbers
    int *_dataPins;
    // 4-bit or 8-bit mode
    // !! DONT USE !!
    DataLength _dataLength = DataLength::FULL;
    // Register Select Pin
    int _rsPin;
    // Read / Write Pin
    int _rwPin;
    // Enable Pin
    int _enPin;

    // Screen busy flag - [1 || 0]
    uint8_t _busy;
    // The Screens 7-bit Adress Counter
    uint8_t _ac;

    uint8_t _charCount;

    // Timeout when waiting for the screen to be available
    uint8_t _waitTimeout = 255;

    // uint8_t DisplayMode(bool displayON, bool controlON, bool blinkON);

    // Sets the 8 individual data lines
    void SetDataLines(uint8_t byte);

    // Shouldnt be needed. The screen should init on its own...
    void InitByInstruction();

    // Sends the specific init signal during an Init-By-Instruction
    void InitResetSignal();

    // Sets the display mode and activates the LCD Screen
    void InitScreen(bool enable = true, bool cursor = true, bool blink = true);

    // Sets the cursors behavior
    void InitEntryMode(bool writeDir = true, bool screenShift = false);

    void InitFunctionSet(bool twoLineMode = true, bool bigFont = false);

    // sets the binary value at an address offset
    uint8_t SetState(uint8_t offset, bool state);

    // Pulses the enable line to send data to the screen.
    void SendEnable();

    // Reads the busy flag from the read register.
    void ReadBusy();

    // Waits for the screen to set its busy flag to 0 before continuing.
    // Also has a timeout as well.
    void WaitForScreen();

    // Waits for the screen to be available, then calls the passed function.
    void WaitForScreen(int (*func)());

    void ShiftLine();

public:

    // Normal 8-bit control mode constructor
    LCDScreen(int dataPins[8], int rsPin, int rwPin, int enPin);

    // Only used in 4-bit mode. This is not complete.
    // !! DONT USE !!
    LCDScreen(int dataPins[8], int rsPin, int rwPin, int enPin, DataLength dataLength);

    // Initializes the LCD screen
    void Begin();

    // Turns the screen OFF and clears the RAM.
    void End();

    // Clears the LCD screen
    void Clear();

    // Returns the cursor to the start of the screen.
    void Return();

    // Print to the LCD screen
    void Print(char c);

    // Print to the LCD screen
    void Print(uint8_t c);

    // Print to the LCD screen
    void Print(String str);

    // Print to the LCD screen
    void Print(int num);

    // Print to the LCD screen
    void Print(long num);

    // Print to the LCD screen and wraps to the next line
    void Println(String str);

    void Println(uint8_t* str, unsigned int len);

    void Println(char* str, unsigned int len);
    // Wraps the screen to the next line
    void Println();

    // !!! Only for testing !!!
    void Test();
};

#endif