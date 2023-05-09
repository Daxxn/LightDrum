/*
 * PCA9634.cpp
 *
 *  Created on: Feb 11, 2023
 *      Author: Daxxn
 */

#include <string.h>
#include "PCA9634.h"

/* PCA9634Settings Methods ---------------------------------------------------*/

/*
 * @brief Convert settings into two bytes and add them to the buffer.
 * @param buffer The buffer to store the settings in.
 * @param offset sets an offset from the start of the buffer to save the settings. Default = 0.
 */
void PCA9634Settings::ToBytes(uint8_t *buffer, size_t offset = 0)
{
	uint8_t upper = (uint8_t)this->Enable;
	upper |= (uint8_t)this->Driver << 2;
	upper |= (uint8_t)this->Change << 3;
	upper |= (uint8_t)this->Invert << 4;
	upper |= (uint8_t)this->GroupCtrl << 5;

	uint8_t lower = (uint8_t)this->AllCallEnable;
	lower |= ((uint8_t)this->SubAddrEn1 << 1) +
			 ((uint8_t)this->SubAddrEn2 << 2) +
			 ((uint8_t)this->SubAddrEn3 << 3);
	lower |= (uint8_t)this->Sleep << 4;

	buffer[0 + offset] = lower;
	buffer[1 + offset] = upper;
}

PCA9634Settings PCA9634Settings::FromBytes(uint8_t *buffer, size_t offset = 0)
{
	PCA9634Settings result = PCA9634Settings();
	result.Enable = (PCA9634_OUTPUT_ENABLE)(buffer[1 + offset] & 0b00000011);
	result.Driver = (PCA9634_OUTPUT_DRIVER)(buffer[1 + offset] & 0b00000100);
	result.Change = (PCA9634_OUTPUT_CHANGE)(buffer[1 + offset] & 0b00001000);
	result.Invert =  (PCA9634_OUTPUT_LOGIC)(buffer[1 + offset] & 0b00010000);
	result.GroupCtrl = (PCA9634_GROUP_CTRL)(buffer[1 + offset] & 0b00100000);
	result.AllCallEnable =           (bool)(buffer[0 + offset] & 0b00000001);
	result.SubAddrEn3 =              (bool)(buffer[0 + offset] & 0b00000010);
	result.SubAddrEn2 =              (bool)(buffer[0 + offset] & 0b00000100);
	result.SubAddrEn1 =              (bool)(buffer[0 + offset] & 0b00001000);
	result.Sleep =          (PCA9634_SLEEP)(buffer[0 + offset] & 0b00010000);
	return result;
}

/* PCA9634 Class Methods -----------------------------------------------------*/

PCA9634::PCA9634(FMPI2C_HandleTypeDef *i2cBus, Pin oePin)
{
	this->i2cBus = i2cBus;
	this->channels = new uint8_t[RGB_CHANNELS];
	this->channelState = new PCA9634_LEDOUT[RGB_CHANNELS];
	this->oePin = oePin;
}

PCA9634::~PCA9634()
{
	delete[] channels;
}

/*
 * @brief Initialize the PCA9634 IC with the provided settings.
 * @param settings The settings to apply to the PCA9634.
 * @retval HAL status
 */
HAL_StatusTypeDef PCA9634::Init(PCA9634Settings settings)
{
	this->oePin.Clear();

	if (Reset() == HAL_OK)
	{
		if (SendSettings(settings))
		{
			this->settings = settings;
			return HAL_OK;
		}
	}
		// Debug Light
	return HAL_ERROR;
}

/*
 * @brief Sends the I2C reset command over the bus.
 * @retval HAL_OK if the reset was acknowledged.
 */
HAL_StatusTypeDef PCA9634::Reset()
{
	uint8_t temp[] = { PCA9634_RST_HIGH, PCA9634_RST_LOW };
	if (HAL_FMPI2C_Master_Transmit(this->i2cBus, this->address, temp, 2, FMPI2C_TIMEOUT) != HAL_OK)
	{
		return HAL_ERROR;
	}
	HAL_Delay(1);
	return HAL_OK;
}

/*
 * @brief Update the current settings and send it to the PCA9634.
 * @param settings The new esttings to apply.
 * @retval HAL status
 */
HAL_StatusTypeDef PCA9634::ChangeSettings(PCA9634Settings settings)
{
	if (SendSettings(settings) == HAL_OK)
	{
		this->settings = settings;
		return HAL_OK;
	}
	return HAL_ERROR;
}

PCA9634Settings PCA9634::ReadSettings()
{
	uint8_t buffer[2] = {0,0};
	HAL_FMPI2C_Master_Receive(i2cBus, this->address, buffer, 2, 200);
	return PCA9634Settings::FromBytes(buffer);
}

void PCA9634::ToggleLEDs(GPIO_PinState state)
{
	this->oePin.Write(state);
}

void PCA9634::SetChannel(uint8_t index, uint8_t pwm)
{
	this->channels[index] = pwm;
}

void PCA9634::SetChannelState(uint8_t index, PCA9634_LEDOUT state)
{
	this->channelState[index] = state;
}

void PCA9634::ResetChannels(int8_t except = -1)
{
	uint8_t value = 0;
	if (except >= 0)
	{
		value = this->channels[except];
	}
	memset(this->channels, 0, RGB_CHANNELS);
	this->channels[except] = value;
}

uint8_t PCA9634::GetChannel(uint8_t index)
{
	return this->channels[index];
}

HAL_StatusTypeDef PCA9634::Update()
{
	uint16_t ledOut0 = 0;
	for (size_t i = 0; i < RGB_CHANNELS; ++i) {
		ledOut0 |= (uint8_t)this->channelState[i] << (i * 2);
	}
	uint8_t buffer[2] = {(uint8_t)(ledOut0 >> 8), (uint8_t)(ledOut0 & 0xFF)};
	HAL_StatusTypeDef pwmStatus = WriteBytes(PCA9634_AUTO_INC::LED_REGS, PCA9634_CTRL_REGISTER::PWMStart, this->channels, RGB_CHANNELS);
	return pwmStatus + WriteBytes(PCA9634_AUTO_INC::ALL_REGS, PCA9634_CTRL_REGISTER::LEDOUT0, buffer, 2) == 0 ? HAL_OK : HAL_ERROR;
}

/*
 * @brief PRIVATE - Sends the provided settings to the PCA9634.
 * @param settings The new esttings to send.
 * @retval HAL status
 */
HAL_StatusTypeDef PCA9634::SendSettings(PCA9634Settings settings)
{
	uint8_t buffer[3] = {0,0,0};
	settings.ToBytes(buffer, 1);
	return WriteBytes(PCA9634_AUTO_INC::ALL_REGS, PCA9634_CTRL_REGISTER::MODE1, buffer, 3);
}

/*
 * @brief PRIVATE - Writes the byte to the PCA9634 at the desired register address.
 * @param inc Auto-Increment register option.
 * @param reg The register to send to.
 * @retval HAL status
 */
HAL_StatusTypeDef PCA9634::WriteByte(PCA9634_CTRL_REGISTER reg, uint8_t byte)
{
	uint8_t temp[2] = { this->CombineCommand(PCA9634_AUTO_INC::NONE, reg) , byte};
	return HAL_FMPI2C_Master_Transmit(this->i2cBus, this->address, temp, 2, FMPI2C_TIMEOUT);
}

/*
 * @brief PRIVATE - Writes the bytes to the PCA9634 at the starting register address.
 * @param inc Auto-Increment register option.
 * @param reg The starting register to send to.
 * @retval HAL status
 */
HAL_StatusTypeDef PCA9634::WriteBytes(PCA9634_AUTO_INC inc, PCA9634_CTRL_REGISTER reg, uint8_t *bytes, size_t len)
{
	uint8_t temp[len + 1] = { this->CombineCommand(inc, reg) };
	for (size_t i = 1, j = 0; i < len + 1; ++i, ++j) {
		temp[j] = bytes[i];
	}
	return HAL_FMPI2C_Master_Transmit(this->i2cBus, this->address, temp, len + 1, FMPI2C_TIMEOUT);
}

/*
 * @brief PRIVATE - Combines the Auto-Increment options with the register. (Possibly replace with a macro. Might be faster.)
 * @param inc Auto-Increment register option.
 * @param reg Desired register.
 * @retval HAL status
 */
uint8_t PCA9634::CombineCommand(PCA9634_AUTO_INC inc, PCA9634_CTRL_REGISTER reg)
{
	return (uint8_t)reg | ((uint8_t)inc << 5);
}
