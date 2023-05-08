/*
 * StripCurrent.cpp
 *
 *  Created on: Mar 10, 2023
 *      Author: Daxxn
 */

#include "main.h"
#include <StripCurrent.h>

StripCurrent::StripCurrent(ADC_HandleTypeDef *adcHandle, TIM_HandleTypeDef *timerHandle)
{
	this->adc = adcHandle;
	this->timer = timerHandle;
}

StripCurrent::~StripCurrent()
{
	delete[] this->buffer;
}

void StripCurrent::Init()
{
	this->buffer = new uint8_t[STRIP_CURR_BUFFER_LEN];
	HAL_ADC_Start(this->adc);
	HAL_ADC_Start_DMA(this->adc, (uint32_t *)this->buffer, STRIP_CURR_BUFFER_LEN);
	HAL_TIM_Base_Start(this->timer);
}

uint8_t StripCurrent::GetChannel(StripIndecies ch)
{
	return 0;
}

void StripCurrent::Calc()
{

}

void CalcAverage(uint8_t index)
{
	for (int i = 0; i < STRIP_CURR_BUFFER_LEN; ++i)
	{

	}
}
