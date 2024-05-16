/*
 * LEDControl.cpp
 *
 *  Created on: Jun 2, 2023
 *      Author: Daxxn
 */

#include <LEDControl.h>

LEDControl::LEDControl(PCA9634 *drivers, StripControl *control)
{
	this->drivers = drivers;
	this->control = control;
	this->strips = new LEDStrip[8];
}

LEDControl::~LEDControl()
{
	this->control = NULL;
	delete[] this->strips;
}

HAL_StatusTypeDef LEDControl::Init()
{
	return HAL_OK;
}

void LEDControl::UpdateStrip(uint8_t strip, uint8_t red, uint8_t green, uint8_t blue)
{
	this->strips[strip].Red = red;
	this->strips[strip].Green = green;
	this->strips[strip].Blue = blue;
}

void LEDControl::Update()
{
//	for (i = 0; i < 8; ++i) {
//
//	}
}
