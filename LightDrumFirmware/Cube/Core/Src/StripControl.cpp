/*
 * StripControl.cpp
 *
 *  Created on: May 21, 2023
 *      Author: Daxxn
 */

#include "StripControl.h"

StripControl::StripControl(StripCurrent *stripCurrent)
{
	this->stripCurrent = stripCurrent;
	this->stripEShdnPin = Pin(STRIP_ESHDN_GPIO_Port, STRIP_ESHDN_Pin, ACTIVE_LOW);
	this->stripPGoodPin = Pin(STRIP_PG_GPIO_Port, STRIP_PG_Pin);
	this->stripPowerPin = Pin(STRIP_PWR_GPIO_Port, STRIP_PWR_Pin);
}

StripControl::~StripControl()
{
	this->stripCurrent = NULL;
}

HAL_StatusTypeDef StripControl::Init()
{
	this->stripPowerPin.Clear();
	this->stripEShdnPin.Clear();
	this->pGood = this->stripPGoodPin.Read() == GPIO_PIN_SET;
	return HAL_OK;
}

void StripControl::Power(GPIO_PinState enable)
{
	if (this->enable == enable) {
		return;
	}

	this->pGood = this->stripPGoodPin.Read() == GPIO_PIN_SET;
	if (enable == GPIO_PIN_SET && this->pGood == 0)
	{
		this->enable = GPIO_PIN_RESET;
		this->stripPowerPin.Write(this->enable);
	}
	else {
		this->enable = enable;
		this->stripPowerPin.Write(enable);
	}
}

void StripControl::Check()
{
	StripCurrentStatus status = this->stripCurrent->CheckCurrents();
	if (status == OCP_CUT)
	{
		this->stripEShdnPin.Write(GPIO_PIN_SET);
		this->stripPowerPin.Write(GPIO_PIN_RESET);
	}
}
