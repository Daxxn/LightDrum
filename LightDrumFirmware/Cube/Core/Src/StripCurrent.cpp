/*
 * StripCurrent.cpp
 *
 *  Created on: Mar 10, 2023
 *      Author: Daxxn
 */

#include <StripCurrent.h>

StripCurrent::StripCurrent()
{
}

StripCurrent::~StripCurrent()
{
}

void StripCurrent::Init(uint8_t *buffer)
{
	this->buffer = buffer;
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
