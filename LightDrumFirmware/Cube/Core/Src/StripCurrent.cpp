/*
 * StripCurrent.cpp
 *
 *  Created on: Mar 10, 2023
 *      Author: Daxxn
 */

#include "main.h"
#include "string.h"
#include "StripCurrent.h"

StripCurrent::StripCurrent(ADC_HandleTypeDef *adcHandle, TIM_HandleTypeDef *timer, pStripCurrentAlertTypeDef callback)
{
	this->buffer = new uint8_t[STRIP_CURR_BUFFER_LEN];
	this->adc = adcHandle;
	this->timer = timer;
	this->averages = new uint8_t[ADC_CHANNELS];
	memset(this->averages, 0, ADC_CHANNELS);
	this->alertCallback = callback;
//	HAL_ADC_RegisterCallback(adc, HAL_ADC_CONVERSION_COMPLETE_CB_ID, callback);
}

StripCurrent::~StripCurrent()
{
	delete[] this->buffer;
	delete[] this->averages;
}

HAL_StatusTypeDef StripCurrent::Init()
{
	if (HAL_ADC_Start_DMA(this->adc, (uint32_t *)this->buffer, STRIP_CURR_BUFFER_LEN) != HAL_OK)
	{
		return HAL_ERROR;
	}
	return HAL_TIM_Base_Start(this->timer);
}

uint8_t StripCurrent::GetChannelValue(StripIndecies ch)
{
	return buffer[ch];
}

void StripCurrent::Calc()
{
	// Get each channels value from the DMA buffer
	// and calc the average.
	for (int i = 0; i < ADC_CHANNELS; ++i) {
		static uint16_t sum;
		for (int offset = 0; offset < STRIP_CURR_BUFFER_LEN; offset += ADC_CHANNELS) {
			sum += buffer[i + offset];
		}
		averages[i] = sum / SAMPLE_SIZE;
//		averages[i] += *buffer + (i * 8);
//		uint8_t aver = buffer[i * SAMPLE_SIZE];
//		averages[i] += buffer[i * SAMPLE_SIZE];
	}
	this->temp = averages[TEMP_INDEX];
	this->vref = averages[VREF_INDEX];
//	this->CheckCurrents();
}

StripCurrentStatus StripCurrent::CheckCurrents()
{
	int i = 0;
	StripCurrentStatus status = GOOD;
	while (i < STRIP_SIZE && status == GOOD)
	{
		if (this->averages[i] >= ABS_MAX_CURRENT)
		{
			status = OCP_CUT;
		}
		else if (this-> averages[i] >= OVER_CURRENT_THR)
		{
			status = OC_WARN;
		}
		i++;
	}
	if (status != GOOD && this->alertCallback != NULL)
	{
		if (this->alertCallback != NULL)
		{
			this->alertCallback(status);
		}
	}
	return status;
}

void StripCurrent::CalcAverage(uint8_t *index)
{
//	for (int i = 0; i < STRIP_CURR_BUFFER_LEN; ++i)
//	{
//
//	}
}

float StripCurrent::CalcCurrent(uint8_t channel)
{
	// This is most likely wrong. Fix later.
	return this->averages[channel] / CURRENT_RATIO;
}

float StripCurrent::CalcPerc(uint8_t channel)
{
	return this->averages[channel] / UINT8_MAX;
}
