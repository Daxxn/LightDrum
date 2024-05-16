/*
 * RotaryEncoder.cpp
 *
 *  Created on: May 28, 2023
 *      Author: Daxxn
 */

#include <RotaryEncoder.h>

RotaryEncoder::RotaryEncoder(GPIO_TypeDef *portA, uint16_t pinA, GPIO_TypeDef *portB, uint16_t pinB, Pin switchPin)
{
	this->portA = portA;
	this->portB = portB;
	this->pinA = pinA;
	this->pinB = pinB;
	this->switchPin = switchPin;
}

RotaryEncoder::~RotaryEncoder()
{
}

HAL_StatusTypeDef RotaryEncoder::Init()
{
	prevStateA = HAL_GPIO_ReadPin(portA, pinA);
	prevStateB = HAL_GPIO_ReadPin(portB, pinB);
	return HAL_OK;
}

void RotaryEncoder::Decode()
{
	this->currStateA = HAL_GPIO_ReadPin(this->portA, this->pinA);
	this->currStateB = HAL_GPIO_ReadPin(this->portB, this->pinB);

	if (this->currStateA == 1)
	{
		if (this->currStateA != this->prevStateA)
		{
			if (this->currStateB == 0)
			{
				this->position++;
				this->direction = CW;
			}
			else
			{
				this->position--;
				this->direction = CCW;
			}
		}
	}

	this->prevStateA = this->currStateA;
	this->prevStateB = this->currStateB;
}

uint16_t RotaryEncoder::GetPosition()
{
	return this->position;
}

Direction RotaryEncoder::GetDirection()
{
	return this->direction;
}

