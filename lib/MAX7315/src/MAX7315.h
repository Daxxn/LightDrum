#pragma once

#include <Arduino.h>
#include <Wire.h>
#include "MAX7315Settings.h"

// #region Definitions
#define PIN_COUNT 8
#define HALF_PIN_COUNT 4
#define MAX_PWM 15
#define MIN_PWM 0
#define MAX_GL_PWM 254
#define LOGIC_OUT 0xFF

// #region Commands
// Read input register address
// 8-bits
#define CMD_READ_INPUT 0x00
// Turns on the PWM outputs??
#define CMD_BLINK_PHASE_0 0x01
#define CMD_BLINK_PHASE_1 0x09
// Individual port config register
#define CMD_PORTS_CONFIG 0x03
// Sets the global PWM intensity or the output 8 pin state.
#define CMD_MASTER 0x0E
// Main config register
#define CMD_CONFIG 0x0F

// Output intensity registers
// Note - The output intensity registers will auto-increment
#define CMD_OUTPUT_INTE_10 0x10
#define CMD_OUTPUT_INTE_32 0x11
#define CMD_OUTPUT_INTE_54 0x12
#define CMD_OUTPUT_INTE_76 0x13
// #endregion

// #region Config Register Masks
#define MASK_BLINK_EN        0b1
#define MASK_BLINK_FL        0b10
#define MASK_GLOBAL          0b100
#define MASK_INT_EN          0b1000
#define MASK_INT_OUTPUT_CTRL 0b110000
// #endregion

// #region Error Return Flags
#define OK 0
#define ERR_PWM_OUTSIDE_RANGE 1
#define ERR_INVALID_PIN 2
// #endregion

// #endregion

// #region Enums
enum PinMode
{
    IN = 0,
    OUT = 1,
    PWM = 2,
};
// #endregion

// #region Pin Struct

// Describes the pin used
struct Pin
{
public:
    // Creates a new pin for the MAX7315
    Pin() : number(INT16_MAX), mode(PinMode::IN) { }
    // Creates a new pin for the MAX7315
    Pin(int number, PinMode mode)
    {
        this->number = number;
        this->mode = mode;
    }
    static uint8_t GetState(Pin pins[PIN_COUNT])
    {
        uint8_t output = 0;
        for (size_t i = 0; i < PIN_COUNT; i++)
        {
            output |= pins[i].state << i;
        }

        return output;
    }
    // Pin number of the IC
    int number;
    // Mode of the pin
    PinMode mode;
    uint8_t pwm = 0;
    bool state = false;
};

// #endregion

// Interface library for the MAX7315 IO Expander
class MAX7315
{
public:
    // Creates the controller and activates all pins
    // Will set all pins to the provided mode
    MAX7315(PinMode mode, int address);
    MAX7315(MAX7315Settings settings, PinMode mode);
    // Creates the controller and activates the given pins
    MAX7315(Pin pins[PIN_COUNT], int address);
    MAX7315(MAX7315Settings settings, Pin pins[PIN_COUNT]);

    // Start up I2C bus and initialize the MAX7315
    void Begin();

    void End();

    // Resets the MAX7315 to its initial state.
    // !! Not Implemented Yet !!
    void Reset();

    // Re-send the config settings for the IC.
    void Reconfigure(MAX7315Settings settings);

    int ChangePinConfig(Pin pin);
    int ChangePinConfig(int pinNum, PinMode mode);

    // Send PWM data to MAX7315 pin
    int SetPWM(int pin, uint8_t pwm, uint8_t basePWM = 1);

    // Send PWM data to all MAX7315 pins
    void SetGlobalPWM(uint8_t pwm);

    // Send Output state to all pins
    void SetGlobalOutput(bool state);

    // Send Output state to all pins
    void SetGlobalOutput(uint8_t state);

    //Send Output signal to the pin
    int SetOutput(int pin, uint8_t state);
    //Send Output signal to the pin
    int SetOutput(int pin, bool state);

    //Send Output signals to ALL pins
    void SetAllOutputs(uint8_t states[PIN_COUNT]);
    //Send Output signals to ALL pins
    void SetAllOutputs(bool states[PIN_COUNT]);

    void SetAllPWM(uint8_t pwms[PIN_COUNT], uint8_t basePWM = 1);

    // Reads the state of all the pins.
    // Can be performed at ANY time. Not sure if that will break anything yet..
    uint8_t* Read();

    // Only for testing functions.
    void Test();
private:
    Pin _pins[PIN_COUNT];
    int _address;
    uint8_t _portStates;
    uint8_t _globalPWM = 0;
    uint8_t _basePWM = 0;
    bool _globalState = false;
    // uint8_t _pwmStates[8];
    // bool _digitalStates[8];
    uint8_t _pwmBuffer[HALF_PIN_COUNT];
    bool _outputBuffer[PIN_COUNT];
    MAX7315Settings _settings;

    // Sets the MAX7315s config register
    void SetConfig();

    // Sets the MAX7315s pin config register
    void SetPinConfig();

    // Sets the provided register to the passed state.
    // Mostly used by SetConfig and other setup tasks.
    void SetRegister(uint8_t address, uint8_t state);

    // Sends the state of the GPIO outputs to the MAX7315 output registers.
    void SetOutputRegisters();

    // Sends the PWM state of the outputs to the MAX7315 output registers.
    //
    // Because the PWM signal is only 4 bits and they combine tie 2 pins together in one register, the method first combines them from the state array.
    void SetPWMRegisters();

    // Sets the global PWM baseline
    //
    // Required for individual PWM outputs.
    void SetBasePWM(uint8_t pwm);

    // Sets the GPIO Pins
    void SetPins();

    // #region Helper Methods

    // Checks the provided PWM signal for a valid 4-bit value.
    bool CheckPWM(uint8_t pwm);

    bool CheckGlobalPWM(uint8_t pwm);
    // #endregion
};