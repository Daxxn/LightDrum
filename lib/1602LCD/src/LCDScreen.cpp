#include "LCDScreen.h"
#include <Arduino.h>
#include <string.h>

LCDScreen::LCDScreen(int dataPins[8], int rsPin, int rwPin, int enPin)
{
    this->_dataPins = dataPins;
    this->_rsPin = rsPin;
    this->_rwPin = rwPin;
    this->_enPin = enPin;
    this->_charCount = 0;
}

LCDScreen::LCDScreen(int dataPins[8], int rsPin, int rwPin, int enPin, DataLength dataLength)
{
    this->_dataPins = dataPins;
    this->_rsPin = rsPin;
    this->_rwPin = rwPin;
    this->_enPin = enPin;
    this->_dataLength = dataLength;
    this->_charCount = 0;
}

void LCDScreen::Begin()
{
    Serial.println("Init Pins");
    pinMode(this->_enPin, OUTPUT);
    pinMode(this->_rsPin, OUTPUT);
    pinMode(this->_rwPin, OUTPUT);

    digitalWrite(this->_enPin, LOW);
    digitalWrite(this->_rsPin, LOW);
    digitalWrite(this->_rwPin, LOW);

    this->_charCount = 0;

    for (byte i = 0; i < this->_dataLength; i++)
    {
        pinMode(this->_dataPins[i], OUTPUT);
    }

    delay(200);
    Serial.println("Starting Screen Init");

    this->InitFunctionSet();
    delayMicroseconds(50);
    this->InitScreen(true, true, false);
    delayMicroseconds(50);
    this->InitEntryMode();
    delayMicroseconds(50);
}

void LCDScreen::InitByInstruction()
{
    Serial.println("Initializing Manually...");
    delay(15);
    // First Init Signal
    this->InitResetSignal();
    delay(5);
    // Second Init Signal
    this->InitResetSignal();
    delayMicroseconds(105);
    // Third Init Signal
    this->InitResetSignal();
    // Then initialize in a specific order
    // Specify the bus size and font size
    this->InitFunctionSet();
    this->WaitForScreen();
    // Turn the screen OFF
    this->InitScreen(false, false, true);
    this->WaitForScreen();
    // Clear the screen
    this->Clear();
    this->WaitForScreen();
    // Set the entry mode (direction & screen shift)
    this->InitEntryMode();
    this->WaitForScreen();
    // Initialization Complete

    // Turn the screen ON
    this->InitScreen(true, true, true);
    this->WaitForScreen();
}

void LCDScreen::InitResetSignal()
{
    this->SetDataLines(0b00110000);
    this->SendEnable();
}

void LCDScreen::End()
{
    this->InitScreen(false, true, true);
}

void LCDScreen::Test()
{
    this->InitEntryMode(false, true);
}

void LCDScreen::InitScreen(bool enable, bool cursor, bool blink)
{
    digitalWrite(this->_rsPin, LOW);
    digitalWrite(this->_rwPin, LOW);
    byte initState = 
        0b1000
            | this->SetState(LCD_ENABLE_OFFSET, enable)
            | this->SetState(LCD_CURSOR_DIR_OFFSET, cursor)
            | this->SetState(LCD_CURSOR_BLINK_OFFSET, blink);
    Serial.println(initState);
    this->SetDataLines(initState);
    this->SendEnable();
}

void LCDScreen::InitEntryMode(bool writeDir, bool screenShift)
{
    digitalWrite(this->_rsPin, LOW);
    digitalWrite(this->_rwPin, LOW);
    uint8_t initState = 0b100
        | this->SetState(LCD_CURSOR_DIR_OFFSET, writeDir)
        | this->SetState(LCD_SCREEN_SHIFT_OFFSET, screenShift);
    this->SetDataLines(initState);
    this->SendEnable();
}

void LCDScreen::InitFunctionSet(bool twoLineMode, bool bigFont)
{
    // if (!this->_busy)
    // {
        digitalWrite(this->_rsPin, LOW);
        digitalWrite(this->_rwPin, LOW);
        uint8_t initState =
            0b100000
                // bitor this->SetState(LCD_DATA_LEN_OFFSET, (this->_dataLength == DataLength::FULL ? 1 : 0))
                | this->SetState(LCD_DATA_LEN_OFFSET, 1)
                | this->SetState(LCD_LINE_NUM_OFFSET, twoLineMode)
                | this->SetState(LCD_FONT_SIZE_OFFSET, bigFont);
        this->SetDataLines(initState);
        this->SendEnable();
        delayMicroseconds(37);
    // }
    // this->ReadBusy();
}

void LCDScreen::Clear()
{
    // Serial.println("Clear Screen");
    digitalWrite(this->_rsPin, LOW);
    digitalWrite(this->_rwPin, LOW);
    this->SetDataLines(1);
    this->SendEnable();
    this->_charCount = 0;
}

void LCDScreen::Return()
{
    // if (!this->_busy)
    // {
        // Serial.println("Return Home");
        digitalWrite(this->_rsPin, LOW);
        digitalWrite(this->_rwPin, LOW);
        this->SetDataLines(0b10);
        this->SendEnable();
        delay(2);
        this->_charCount = 0;
    // }
    // this->ReadBusy();
}

void LCDScreen::Print(String str)
{
    // Serial.println(str);
    digitalWrite(this->_rsPin, HIGH);
    digitalWrite(this->_rwPin, LOW);
    for (uint16_t i = 0; i < str.length(); i++)
    {
        // byte code = toAscii(str.charAt(i));
        // Serial.print(code);
        // Serial.print(" ");
        // this->SetDataLines(code);
        // this->SendEnable();
        this->Print(str.charAt(i));
        // delayMicroseconds(37);
    }
}

void LCDScreen::Print(char c)
{
    // Serial.println(c);
    digitalWrite(this->_rsPin, HIGH);
    digitalWrite(this->_rwPin, LOW);
    this->SetDataLines(byte(c));
    this->SendEnable();
    this->_charCount++;
    delayMicroseconds(40);
}

// void LCDScreen::print(int value)
// {
//     Serial.println(value);
//     digitalWrite(this->_rsPin, HIGH);
//     digitalWrite(this->_rwPin, LOW);
//     String str = String(value);
//     this->print(str);
// }

void LCDScreen::Println(String str)
{
    this->Print(str);
    this->ShiftLine();
}

void LCDScreen::ShiftLine()
{
    int diff = LCD_LINE_COUNT - this->_charCount;
    if (diff >= 0)
    {
        String blank = "";
        for (int i = 0; i < diff; i++)
        {
            blank += " ";
        }
        this->Print(blank);
    } else {
        for (int i = 0; i < diff; i++)
        {
            this->SetDataLines(0b100);
        }
    }
    delayMicroseconds(40);
}

void LCDScreen::SetDataLines(uint8_t b)
{
    for (uint8_t i = 0; i < this->_dataLength; i++)
    {
        digitalWrite(this->_dataPins[i], bitRead(b, i));
    }
}

uint8_t LCDScreen::SetState(uint8_t offset, bool state)
{
    return offset & (state ? 0xFF : 0x0);
}

void LCDScreen::SendEnable()
{
    delayMicroseconds(10);
    digitalWrite(this->_enPin, HIGH);
    delayMicroseconds(LCD_WRITE_DELAY);
    digitalWrite(this->_enPin, LOW);
    this->SetDataLines(0);
}

void LCDScreen::ReadBusy()
{
    uint8_t data = 0;
    digitalWrite(this->_rsPin, LOW);
    digitalWrite(this->_rwPin, HIGH);
    digitalWrite(this->_enPin, HIGH);
    delayMicroseconds(20);
    for (uint8_t i = 0; i < 8; i++)
    {
        data = data | (digitalRead(this->_dataPins[i]) << i);
    }
    this->_busy = data & 0b10000000;
    this->_ac =   data &  0b1111111;
}

void LCDScreen::WaitForScreen()
{
    this->ReadBusy();
    if (this->_busy)
    {
        for (uint8_t i = 0; i < this->_waitTimeout; i++)
        {
            this->ReadBusy();
            Serial.println("Waiting For Screen");
            if (!this->_busy)
            {
                break;
            }
            
            delayMicroseconds(10);
        }
    }
}

void LCDScreen::WaitForScreen(int (*func)())
{
    this->ReadBusy();
    if (this->_busy)
    {
        for (uint8_t i = 0; i < this->_waitTimeout; i++)
        {
            this->ReadBusy();
            if (!this->_busy)
            {
                break;
            }
            
            delayMicroseconds(10);
        }
        if (!this->_busy)
        {
            func();
        }
    }
}