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
//	this->stripEShdnPin = Pin(STRIP_ESHDN_GPIO_Port, STRIP_ESHDN_Pin);
	this->stripEShdnPin = Pin(STRIP_ESHDN_GPIO_Port, STRIP_ESHDN_Pin, ACTIVE_LOW);
	this->stripPGoodPin = Pin(STRIP_PG_GPIO_Port, STRIP_PG_Pin);
	this->stripPowerPin = Pin(STRIP_PWR_GPIO_Port, STRIP_PWR_Pin);
	this->vddPGoodPin = Pin(VDD_PG_GPIO_Port, VDD_PG_Pin);
	this->vaaPGoodPin = Pin(VAA_PG_GPIO_Port, VAA_PG_Pin);
	this->pwmOEPin = Pin(PWM_OE_GPIO_Port, PWM_OE_Pin);
}

StripControl::~StripControl()
{
	this->stripCurrent = NULL;
}

HAL_StatusTypeDef StripControl::Init()
{
	this->stripPowerPin.Clear();
	this->stripEShdnPin.Clear();
	this->pwmOEPin.Clear();
	this->vddPGood   = this->vddPGoodPin.Read();
	this->vaaPGood   = this->vaaPGoodPin.Read();
	this->stripPGood = this->stripPGoodPin.Read();
	this->stripEShdnPin.Write(GPIO_PIN_RESET);
	return HAL_OK;
}

void StripControl::Power(GPIO_PinState enable)
{
	if (this->enable == enable)
	{
		return;
	}

//	this->pGood = this->stripPGoodPin.Read() == GPIO_PIN_SET;
	this->enable = enable;
	this->stripPowerPin.Write(enable);
}

void StripControl::Check()
{
	StripCurrentStatus status = this->stripCurrent->CheckCurrents();
	this->stripPGood = this->stripPGoodPin.Read();
	if (status == OCP_CUT || this->stripPGood == 0)
	{
		this->stripEShdnPin.Write(GPIO_PIN_RESET);
		this->stripPowerPin.Write(GPIO_PIN_RESET);
	}
}
