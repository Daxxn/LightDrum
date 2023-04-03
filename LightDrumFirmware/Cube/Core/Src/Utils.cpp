/*
 * Utils.cpp
 *
 *  Created on: Feb 12, 2023
 *      Author: Daxxn
 */


#include "Utils.h"

void Pin::Write(GPIO_PinState state)
{
	HAL_GPIO_WritePin(this->port, this->pin, (GPIO_PinState)(this->defaultState == GPIO_Default_State::ACTIVE_LOW ? !state : state));
}

GPIO_PinState Pin::Read()
{
	return HAL_GPIO_ReadPin(this->port, this->pin);
}

void Pin::Toggle()
{
	HAL_GPIO_TogglePin(this->port, this->pin);
}

void Pin::Clear()
{
	HAL_GPIO_WritePin(this->port, this->pin, (GPIO_PinState)this->defaultState);
}
