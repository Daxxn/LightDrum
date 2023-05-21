/*
 * StripCurrent.cpp
 *
 *  Created on: Mar 10, 2023
 *      Author: Daxxn
 */

#include "main.h"
#include <StripCurrent.h>

StripCurrent::StripCurrent(ADC_HandleTypeDef *adcHandle, TIM_HandleTypeDef *timer)
{
	this->buffer = new uint8_t[STRIP_CURR_BUFFER_LEN];
	this->adc = adcHandle;
	this->timer = timer;
//	HAL_ADC_RegisterCallback(adc, HAL_ADC_CONVERSION_COMPLETE_CB_ID, callback);
}

StripCurrent::~StripCurrent()
{
	delete[] this->buffer;
}

HAL_StatusTypeDef StripCurrent::Init()
{
	if (HAL_ADC_Start_DMA(this->adc, (uint32_t *)this->buffer, STRIP_CURR_BUFFER_LEN) != HAL_OK)
	{
		return HAL_ERROR;
	}
	return HAL_TIM_Base_Start(this->timer);
}

uint8_t StripCurrent::GetChannel(StripIndecies ch)
{
	return buffer[ch];
}

void StripCurrent::Calc()
{
	// Get each channels value from the DMA buffer
	// and calc the average.
	for (int i = 0; i < ADC_CHANNELS; ++i) {
//		averages[i] += *buffer + (i * 8);
		averages[i] += buffer[i * SAMPLE_SIZE];
	}
}

void CalcAverage(uint8_t *index)
{
//	for (int i = 0; i < STRIP_CURR_BUFFER_LEN; ++i)
//	{
//
//	}
}
