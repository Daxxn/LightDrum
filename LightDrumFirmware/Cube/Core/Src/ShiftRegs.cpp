/*
 * ShiftRegs.cpp
 *
 *  Created on: Feb 12, 2023
 *      Author: Daxxn
 */

#include "ShiftRegs.h"
#include "main.h"
#include "bitset"

ShiftRegs::ShiftRegs(SPI_HandleTypeDef *spi, Pin OEPin, Pin LEPin, DataDirection dir)
{
	this->_spi = spi;
	this->_dir = dir;
	this->OEPin = OEPin;
	this->LEPin = LEPin;
	this->_buffer = new uint8_t[2] {0,0};
	this->_union = new ShiftRegUnion();
}

ShiftRegs::~ShiftRegs()
{
	delete[] this->_buffer;
}

void ShiftRegs::Init()
{
//	STP16C - LE = Active HIGH | OE = Active LOW
	this->OEPin.Clear();
	this->LEPin.Clear();
}

void ShiftRegs::SetValue(LEDState value, size_t index)
{
	this->SetValue((uint8_t)value, index);
}

void ShiftRegs::SetValue(uint8_t value, size_t index)
{
	if (value == 1)
	{
		this->_union->number |= 1 << index;
	}
	else
	{
		this->_union->number &= ~(1 << index);
	}
//	this->_temp = 1 << index;
	// I dont trust this...
//	this->_union->number ^= (-value ^ this->_union->number) & (1 << index);
}

void ShiftRegs::ToggleValue(size_t index)
{
	this->SetValue(!this->GetValue(index), index);
}

void ShiftRegs::Clear()
{
	this->_union->number = 0;
}

uint8_t ShiftRegs::GetValue(size_t index)
{
	return (this->_union->number >> index) & 1;
}

void ShiftRegs::Update()
{
//	Something went incredibly silly. The connection to the debugger is lost and the thing starts
//	writing a bunch of junk data to the leds. Its probably an issue with the union. REMOVE IT!
	if (this->_dir == DataDirection::MSB)
	{
		this->_buffer[0] = this->_union->upper;
		this->_buffer[1] = this->_union->lower;
	}
	else
	{
		this->_buffer[0] = this->_union->lower;
		this->_buffer[1] = this->_union->upper;
	}
//	static uint8_t buffer[2] = {0, 0};
//	buffer[0] = this->_temp & 0xFF;
//	buffer[1] = (this->_temp & 0xFF00) >> 8;
	this->OEPin.Write(GPIO_PIN_SET);
	this->LEPin.Write(GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GRAPH_OE_GPIO_Port, GRAPH_OE_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GRAPH_LE_GPIO_Port, GRAPH_LE_Pin, GPIO_PIN_SET);
	HAL_SPI_Transmit(this->_spi, this->_buffer, 2, Timeout);
	this->OEPin.Write(GPIO_PIN_RESET);
	this->LEPin.Write(GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GRAPH_OE_GPIO_Port, GRAPH_OE_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GRAPH_LE_GPIO_Port, GRAPH_LE_Pin, GPIO_PIN_RESET);
}
