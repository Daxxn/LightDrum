#include <Arduino.h>
#include <Wire.h>
#include "MAX7315.h"
#include "Algorythms.h"
#include "PrintUtils.h"

#pragma region Constructors
MAX7315::MAX7315(PinMode mode, int address)
{
    this->_settings = MAX7315Settings(address);
    this->_address = address;
    for (uint8_t i = 0; i < PIN_COUNT; i++)
    {
        this->_pins[i] = Pin(i, mode);
    }
}

MAX7315::MAX7315(MAX7315Settings settings, PinMode mode)
{
    this->_settings = settings;
    this->_address = settings.address;
    for (uint8_t i = 0; i < PIN_COUNT; i++)
    {
        this->_pins[i] = Pin(i, mode);
    }
}

MAX7315::MAX7315(Pin pins[PIN_COUNT], int address)
{
    this->_address = address;
    this->_settings = MAX7315Settings(address);
    for (uint8_t i = 0; i < PIN_COUNT; i++)
    {
        this->_pins[i] = pins[i];
    }
}

MAX7315::MAX7315(MAX7315Settings settings, Pin pins[PIN_COUNT])
{
    this->_address = settings.address;
    this->_settings = settings;
    for (uint8_t i = 0; i < PIN_COUNT; i++)
    {
        this->_pins[i] = pins[i];
    }
}
#pragma endregion

void MAX7315::Begin()
{
    Wire.begin();

    this->SetConfig();
    this->SetPinConfig();
}

void MAX7315::End()
{
    Wire.end();
}

#pragma region Pin Controls
int MAX7315::SetPWM(int pin, uint8_t pwm, uint8_t basePWM)
{
    if (!this->CheckPWM(pwm))
    {
        return ERR_PWM_OUTSIDE_RANGE;
    }

    if (pin < 0 || pin > PIN_COUNT)
    {
        return ERR_INVALID_PIN;
    }
    
    this->_pins[pin].pwm = pwm;
    this->SetBasePWM(basePWM);
    this->SetPWMRegisters();

    return OK;
}

void MAX7315::SetGlobalPWM(uint8_t pwm)
{
    if (this->CheckGlobalPWM(pwm))
    {
        if (this->_settings.globalMode)
        {
            this->_globalPWM = pwm;
            this->SetRegister(CMD_MASTER, pwm << 4);
        }
        else
        {
            for (size_t i = 0; i < PIN_COUNT; i++)
            {
                this->_pins[i].pwm = pwm;
            }
            this->SetPWMRegisters();
        }
    }
}

void MAX7315::SetGlobalOutput(bool state)
{
    if (this->_settings.globalMode)
    {
        if (this->_globalState != state)
        {
            this->_globalState = state;
            this->SetRegister(CMD_MASTER, state ? 0xF0 : 0);
        }
    }
    else
    {
        bool output[PIN_COUNT] = {};
        for (size_t i = 0; i < PIN_COUNT; i++)
        {
            output[i] = state;
        }
        
        this->SetAllOutputs(output);
    }
}

void MAX7315::SetGlobalOutput(uint8_t state)
{
    this->SetGlobalOutput(state == 0 ? false : true);
}

int MAX7315::SetOutput(int pin, uint8_t state)
{
    int output = ERR_INVALID_PIN;
    for (byte i = 0; i < PIN_COUNT; i++)
    {
        if (pin == i)
        {
            this->_pins[i].state = state;
            output = OK;
            break;
        }
    }
    
    this->SetOutputRegisters();
    return output;
}

int MAX7315::SetOutput(int pin, bool state)
{
    int output = ERR_INVALID_PIN;
    for (byte i = 0; i < PIN_COUNT; i++)
    {
        if (pin == i)
        {
            this->_pins[i].state = state;
            output = OK;
            break;
        }
    }
    
    this->SetOutputRegisters();
    return output;
}

void MAX7315::SetAllOutputs(uint8_t states[PIN_COUNT])
{
    for (size_t i = 0; i < PIN_COUNT; i++)
    {
        this->_pins[i].state = states[i];
    }
    this->SetOutputRegisters();
}

void MAX7315::SetAllOutputs(bool states[PIN_COUNT])
{
    for (size_t i = 0; i < PIN_COUNT; i++)
    {
        this->_pins[i].state = states[i];
    }
    this->SetRegister(CMD_BLINK_PHASE_0, Pin::GetState(this->_pins));
}

void MAX7315::SetAllPWM(uint8_t pwms[PIN_COUNT], uint8_t basePWM)
{
    for (size_t i = 0; i < PIN_COUNT; i++)
    {
        this->_pins[i].pwm = pwms[i];
    }
    Serial.println("Pins:");
    PrintArray(pwms, PIN_COUNT);
    Serial.println();
    this->SetBasePWM(basePWM);
    this->SetPWMRegisters();
}

void MAX7315::SetBasePWM(uint8_t pwm)
{
    if (this->CheckPWM(pwm))
    {
        if (this->_basePWM != pwm)
        {
            this->_basePWM = pwm;
            this->SetRegister(CMD_MASTER, pwm << 4);
        }
    }
}
#pragma endregion

#pragma region Config
void MAX7315::SetConfig()
{
    #if !NO_CONFIG
    uint8_t settingsReg = this->_settings.GetSettings();
    // PrintBinary(settingsReg, 8);
    this->SetRegister(CMD_CONFIG, settingsReg);
    #else
    Serial.println("No Config option active.");
    #endif
}

void MAX7315::SetPinConfig()
{
    uint8_t output = 0;
    for (size_t i = 0; i < PIN_COUNT; i++)
    {
        if (this->_pins[i].mode == PinMode::IN)
        {
            output |= 1 << i;
        }
    }

    this->SetRegister(CMD_PORTS_CONFIG, output);
}

int MAX7315::ChangePinConfig(int pinNum, PinMode mode)
{
    int output = ERR_INVALID_PIN;
    if (pinNum > 16)
    {
        return output;
    }

    for (uint8_t i = 0; i < PIN_COUNT; i++)
    {
        if (pinNum == this->_pins[i].number)
        {
            this->_pins[i] = Pin(pinNum, mode);
            output = OK;
            break;
        }
    }

    this->SetPinConfig();
    return output;
}

int MAX7315::ChangePinConfig(Pin pin)
{
    int output = ERR_INVALID_PIN;
    if (pin.number > 16)
    {
        return output;
    }
    
    for (uint8_t i = 0; i < PIN_COUNT; i++)
    {
        if (pin.number == this->_pins[i].number)
        {
            this->_pins[i] = pin;
            output = OK;
            break;
        }
    }

    this->SetPinConfig();
    return output;
}

void MAX7315::Reconfigure(MAX7315Settings settings)
{
    this->_settings = settings;
    this->_address = settings.address;

    this->SetConfig();
    this->SetPinConfig();
}
#pragma endregion

#pragma region (Internal) Sending Data
void MAX7315::SetRegister(uint8_t reg, uint8_t state)
{
    Wire.beginTransmission(this->_address);
    Wire.write(reg);
    Wire.write(state);
    Wire.endTransmission();
}

void MAX7315::SetOutputRegisters()
{
    uint8_t output = 0;
    for (size_t i = 0; i < PIN_COUNT; i++)
    {
        output |= this->_pins[i].state << i;
    }
    
    Wire.beginTransmission(this->_address);
    Wire.write(CMD_BLINK_PHASE_0);
    Wire.write(output);
    Wire.endTransmission();
}

void MAX7315::SetPWMRegisters()
{
    // Sets up the array of data:
    uint8_t temp[HALF_PIN_COUNT];
    uint8_t output[HALF_PIN_COUNT];
    for (uint8_t i = 0; i < PIN_COUNT; i++)
    {
        if (i % 2 == 0)
        {
            temp[i / 2] = (this->_pins[i].pwm << 4) | this->_pins[i + 1].pwm;
        }
    }

    ReverseByte(temp, output, ByteLength::HALF_BYTE);
    Serial.println("Output:");
    PrintArray(output, 4);
    Serial.println();

    Wire.beginTransmission(this->_address);
    Wire.write(CMD_OUTPUT_INTE_10);
    for (uint8_t i = 0; i < HALF_PIN_COUNT; i++)
    {
        Wire.write(output[i]);
    }
    Wire.endTransmission();
}

void MAX7315::SetPins()
{
    for (size_t i = 0; i < PIN_COUNT; i++)
    {
        if (this->_pins[i].mode == PinMode::OUT)
        {
            this->_pins[i].pwm = this->_pins[i].state ? 0xF : 0;
        }
    }

    this->SetPWMRegisters();
}
#pragma endregion

uint8_t* MAX7315::Read()
{
    static uint8_t buffer[PIN_COUNT] = {0,0,0,0,0,0,0,0};
    Wire.beginTransmission(this->_address);
    Wire.write(CMD_READ_INPUT);
    Wire.endTransmission(false);
    Wire.requestFrom(this->_address, 1);
    byte result = Wire.read();
    for (byte i = 0; i < PIN_COUNT; i++)
    {
        buffer[i] = bitRead(result, i);
    }
    return buffer;
}

#pragma region Helper Methods
bool MAX7315::CheckPWM(uint8_t pwm)
{
    return pwm < MAX_PWM && pwm > MIN_PWM;
}

bool MAX7315::CheckGlobalPWM(uint8_t pwm)
{
    return pwm < MAX_GL_PWM && pwm > MIN_PWM;
}

void MAX7315::Test()
{
    uint8_t sett = this->_settings.GetSettings();
    PrintBinary(sett, 8, ByteOrder::MSB);

    Serial.print("BlinkEn ");
    Serial.println(this->_settings.blinkEnable);

    Serial.print("BlinkFl ");
    Serial.println(this->_settings.blinkFlip);

    Serial.print("Global ");
    Serial.println(this->_settings.globalMode);

    Serial.print("interEn ");
    Serial.println(this->_settings.interruptEnable);
}
#pragma endregion