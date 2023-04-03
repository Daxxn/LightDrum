/*
 * StripCurrent.h
 *
 *  Created on: Mar 10, 2023
 *      Author: Daxxn
 */

#ifndef INC_STRIPCURRENT_H_
#define INC_STRIPCURRENT_H_

#include "main.h"

#define STRIP_CURR_BUFFER_LEN 4096

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
	IC_TEMP
} StripIndecies;

/*
 *
 */
class StripCurrent
{
public:
	StripCurrent();
	virtual ~StripCurrent();

	void Init(uint8_t *buffer);

	uint8_t GetChannel(StripIndecies ch);

	void Calc();
private:
	uint8_t *buffer;
	uint16_t sampleSize;

	void CalcAverage(uint8_t index);
};

#endif /* INC_STRIPCURRENT_H_ */
