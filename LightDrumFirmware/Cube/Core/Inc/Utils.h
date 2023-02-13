/*
 * Utils.h
 *
 *  Created on: Feb 12, 2023
 *      Author: Daxxn
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include "main.h"

typedef enum
{
	ACTIVE_HIGH = 0,
	ACTIVE_LOW = 1,
}GPIO_Default_State;

#if __cplusplus


struct Pin
{
	Pin() {};
	Pin(GPIO_TypeDef *port, uint16_t pin)
	{
		this->port = port;
		this->pin = pin;
		this->defaultState = ACTIVE_HIGH;
		HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
	};
	Pin(GPIO_TypeDef *port, uint16_t pin, GPIO_Default_State defaultState)
	{
		this->port = port;
		this->pin = pin;
		this->defaultState = defaultState;
		HAL_GPIO_WritePin(port, pin, (GPIO_PinState)defaultState);
	}
	GPIO_TypeDef *port;
	uint16_t pin;
	GPIO_Default_State defaultState;

	void Write(GPIO_PinState state);
	GPIO_PinState Read();
	void Toggle();
	void Clear();
};

#endif /* __cplusplus */
#endif /* INC_UTILS_H_ */
