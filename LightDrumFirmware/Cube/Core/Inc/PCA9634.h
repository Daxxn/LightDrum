/*
 * PCA9634.h
 *
 *  Created on: Feb 11, 2023
 *      Author: Daxxn
 */

#ifndef INC_PCA9634_H_
#define INC_PCA9634_H_

#include "main.h"

#define RGB_CHANNELS 8

#define PCA9634_RESET 0x06
#define PCA9634_ALLCALL 0xE0

#define PCA9634_RST_HIGH 0xA5
#define PCA9634_RST_LOW  0x5A

#define ApplyAutoInc(inc, reg) ((uint8_t)reg | ((uint8_t)inc << 5))

typedef enum
{
	MODE1       = 0x00,
	MODE2       = 0x01,
	PWMStart    = 0x02,
	GRPPWM      = 0x0A,
	GRPFREQ     = 0x0B,
	LEDOUT0     = 0x0C,
	LEDOUT1     = 0x0D,
	SUBADDR1    = 0x0E,
	SUBADDR2    = 0x0F,
	SUBADDR3    = 0x10,
	ALLCALLADDR = 0x11,

} PCA9634_CTRL_REGISTER;

typedef enum
{
	FULL_OFF = 0b00,
	FULL_ON = 0b01,
	SINGLE = 0b10,
	GLOBAL = 0b11
} PCA9634_LEDOUT;

//typedef enum
//{
//	PWM0        = 0x02,
//	PWM1        = 0x03,
//	PWM2        = 0x04,
//	PWM3        = 0x05,
//	PWM4        = 0x06,
//	PWM5        = 0x07,
//	PWM6        = 0x08,
//	PWM7        = 0x09,
//} PCA9634_PWM_REGISTERS;

typedef enum
{
	NONE = 0,
	ALL_REGS = 0b100,
	BRGT_REGS = 0b101,
	GLOBAL_REGS = 0b110,
	LED_REGS = 0b111
} PCA9634_AUTO_INC;

typedef enum
{
	RUN = 0,
	SLEEP = 1
} PCA9634_SLEEP;

typedef enum
{
	DIMMING = 0,
	BLINKING = 1
} PCA9634_GROUP_CTRL;

typedef enum
{
	NOT_INVERTED = 0,
	INVERTED = 1
} PCA9634_OUTPUT_LOGIC;

typedef enum
{
	STOP = 0,
	ACK = 1
} PCA9634_OUTPUT_CHANGE;

typedef enum
{
	OPEN_DRAIN = 0,
	TOTEM_POLE = 1
} PCA9634_OUTPUT_DRIVER;

typedef enum
{
	PULL_LOW = 0b00,
	USE_LOGIC = 0b01,
	HIGH_Z
} PCA9634_OUTPUT_ENABLE;

struct LEDChannel
{
	LEDChannel() {};
	LEDChannel(uint8_t red, uint8_t green, uint8_t blue) {
		this->red = red;
		this->green = green;
		this->blue = blue;
	};

	void SetColor(uint8_t red, uint8_t green, uint8_t blue) {
		this->red = red;
		this->green = green;
		this->blue = blue;
	};
	void SetRed(uint8_t value)   { this->red = value;   };
	void SetGreen(uint8_t value) { this->green = value; };
	void SetBlue(uint8_t value)  { this->blue = value;  };
	void Invert() {
		red += 127;
		green += 127;
		blue += 127;
	};
	void White() {
		red = 255;
		green = 255;
		blue = 255;
	};
	void Black() {
		red = 0;
		green = 0;
		blue = 0;
	};
	void Off() { en = 0; };
	void On()  { en = 1; };

	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;
	bool en = 1;
};

struct PCA9634Settings
{
	PCA9634_SLEEP         Sleep;
	PCA9634_GROUP_CTRL    GroupCtrl;
	PCA9634_OUTPUT_LOGIC  Invert;
	PCA9634_OUTPUT_CHANGE Change;
	PCA9634_OUTPUT_DRIVER Driver;
	PCA9634_OUTPUT_ENABLE Enable;
	bool AllCallEnable = true;
	bool SubAddrEn1 = false;
	bool SubAddrEn2 = false;
	bool SubAddrEn3 = false;

	void ToBytes(uint8_t *buffer, size_t offset);
	static PCA9634Settings FromBytes(uint8_t *buffer, size_t offset);
};

/*
 *
 */
class PCA9634
{
public:
	PCA9634() {};
	PCA9634(FMPI2C_HandleTypeDef *i2cBus, Pin oePin);
	virtual ~PCA9634();

	/*
	 * @brief Initialize the PCA9634 IC with the provided settings.
	 * @param settings The settings to apply to the PCA9634.
	 * @retval HAL status
	 */
	HAL_StatusTypeDef Init(PCA9634Settings settings);
	HAL_StatusTypeDef InitTest();
	HAL_StatusTypeDef Reset();
	HAL_StatusTypeDef ChangeSettings(PCA9634Settings settings);
	PCA9634Settings ReadSettings();

	void ToggleLEDs(GPIO_PinState state);

	void SetChannel(uint8_t index, uint8_t pwm);
	void SetChannelState(uint8_t index, PCA9634_LEDOUT state);
	void ResetChannels(int8_t except);

//	LEDChannel* GetChannel(uint8_t index);
	uint8_t GetChannel(uint8_t index);

	HAL_StatusTypeDef Update();
private:
	uint8_t address;
	FMPI2C_HandleTypeDef *i2cBus;

	uint8_t *channels;
	PCA9634_LEDOUT *channelState;

	uint8_t globalBrightness = 127;

	PCA9634Settings settings;

	Pin oePin;

	HAL_StatusTypeDef WriteByte(PCA9634_CTRL_REGISTER reg, uint8_t byte);
	HAL_StatusTypeDef WriteBytes(PCA9634_AUTO_INC inc, PCA9634_CTRL_REGISTER reg, uint8_t *byte, size_t len);

	HAL_StatusTypeDef WriteLED(uint8_t index);
	HAL_StatusTypeDef WriteLEDs();

	HAL_StatusTypeDef SendSettings(PCA9634Settings settings);


	uint8_t CombineCommand(PCA9634_AUTO_INC inc, PCA9634_CTRL_REGISTER reg);
};

#endif /* INC_PCA9634_H_ */
