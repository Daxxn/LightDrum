/*
 * StripControl.h
 *
 *  Created on: May 21, 2023
 *      Author: Daxxn
 */

#ifndef SRC_STRIPCONTROL_H_
#define SRC_STRIPCONTROL_H_

#include "main.h"
#include "StripCurrent.h"
#include "Utils.h"

/*
 *
 */
class StripControl
{
public:
	StripControl() {};
	StripControl(StripCurrent *stripCurrent);
	virtual ~StripControl();

	HAL_StatusTypeDef Init();

	void Power(GPIO_PinState enable);

	void Check();
private:
	StripCurrent *stripCurrent;
	GPIO_PinState enable;
	uint8_t stripPGood;
	uint8_t vddPGood;
	uint8_t vaaPGood;
	uint8_t pGood;
	Pin stripPowerPin;
	Pin stripPGoodPin;
	Pin stripEShdnPin;
	Pin vddPGoodPin;
	Pin vaaPGoodPin;
	Pin pwmOEPin;
};

#endif /* SRC_STRIPCONTROL_H_ */
