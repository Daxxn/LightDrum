/*
 * RotaryEncoder.h
 *
 *  Created on: May 28, 2023
 *      Author: Daxxn
 */

#ifndef INC_ROTARYENCODER_H_
#define INC_ROTARYENCODER_H_

#include "main.h"

typedef enum
{
	CCW = -1,
	CW = 1
} Direction;

/*
 *
 */
class RotaryEncoder
{
public:
	RotaryEncoder() {};
	RotaryEncoder(GPIO_TypeDef *portA, uint16_t pinA, GPIO_TypeDef *portB, uint16_t pinB, Pin switchPin);
	virtual ~RotaryEncoder();

	HAL_StatusTypeDef Init();

	void Decode();

	uint16_t GetPosition();
	Direction GetDirection();
private:
	GPIO_TypeDef *portA;
	GPIO_TypeDef *portB;
	uint16_t pinA;
	uint16_t pinB;
	Pin switchPin;

	uint8_t prevStateA = 0;
	uint8_t prevStateB = 0;
	uint8_t currStateA = 0;
	uint8_t currStateB = 0;

	uint16_t position;
	Direction direction;
	uint8_t switchState;

};

#endif /* INC_ROTARYENCODER_H_ */
