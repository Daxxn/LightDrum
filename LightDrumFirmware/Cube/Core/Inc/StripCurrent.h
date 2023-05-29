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
#define STRIP_SIZE 9

#define TEMP_INDEX 9
#define VREF_INDEX 10

#define ABS_MAX_CURRENT 240
#define OVER_CURRENT_THR 200

#define RESISTOR_VALUE 0.075
#define AMP_GAIN 50
#define CURRENT_RATIO 3.75
#define STRIP_VOLTAGE 12

typedef enum
{
	GOOD,
	OC_WARN,
	OCP_CUT,
} StripCurrentStatus;

typedef void (*pStripCurrentAlertTypeDef)(StripCurrentStatus status);

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
	SOLID_LGTS,
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
	StripCurrent(ADC_HandleTypeDef *adcHandle, TIM_HandleTypeDef *timer, pStripCurrentAlertTypeDef callback);
	~StripCurrent();

	HAL_StatusTypeDef Init();

	uint8_t GetChannelValue(StripIndecies ch);
	float CalcCurrent(uint8_t channel);
	float CalcPerc(uint8_t channel);

	void Calc();
	StripCurrentStatus CheckCurrents();
private:
	void (*alertCallback)(StripCurrentStatus status);
	ADC_HandleTypeDef *adc;
	TIM_HandleTypeDef *timer;
	uint8_t *buffer;
	uint16_t sampleSize;
	uint8_t vref;
	uint8_t temp;

	uint8_t *averages;

	void CalcAverage(uint8_t *index);
};

#endif /* INC_STRIPCURRENT_H_ */
