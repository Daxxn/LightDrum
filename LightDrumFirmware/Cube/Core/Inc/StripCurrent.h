/*
 * StripCurrent.h
 *
 *  Created on: Mar 10, 2023
 *      Author: Daxxn
 */

#ifndef INC_STRIPCURRENT_H_
#define INC_STRIPCURRENT_H_

#include "main.h"

#define STRIP_CURR_BUFFER_LEN 110
#define ADC_CHANNELS 11
#define SAMPLE_SIZE 10

typedef enum
{
	CH_0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7,
	IC_TEMP,
	VREF
} StripIndecies;

/*
 *
 */
class StripCurrent
{
public:
	StripCurrent() {};
	StripCurrent(ADC_HandleTypeDef *adcHandle, TIM_HandleTypeDef *timer);
	~StripCurrent();

	HAL_StatusTypeDef Init();

	uint8_t GetChannel(StripIndecies ch);

	void Calc();
private:
	ADC_HandleTypeDef *adc;
	TIM_HandleTypeDef *timer;
	uint8_t *buffer;
	uint16_t sampleSize;

	uint8_t *averages;

	void CalcAverage(uint8_t *index);
};

#endif /* INC_STRIPCURRENT_H_ */
