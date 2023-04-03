/*
 * Nextion.cpp
 *
 *  Created on: Feb 11, 2023
 *      Author: Daxxn
 */

#include <stdio.h>
#include "Nextion.h"
#include "NextionDefs.h"
#include "string.h"
#include "math.h"

Nextion::Nextion()
{
	this->cmdBuffer = new uint8_t[NEXTION_BUFFER];
	this->recBuffer = new uint8_t[NEXTION_REC_SIZE];
	this->buffer = new char[NEXTION_BUFFER];
	this->index = 0;
}

Nextion::~Nextion()
{
	delete[] cmdBuffer;
	delete[] recBuffer;
	delete[] buffer;
}

void Nextion::Startup(UART_HandleTypeDef *uart)
{
	this->uart = uart;
	HAL_UART_Receive(uart, recBuffer, 8, UART_TIMEOUT);
	SendCommand("bkcmd=1");
	HAL_Delay(100);
}

bool Nextion::CommandCheck()
{
	if (this->recBuffer[0] == 0 || this->recBuffer[0] == NEX_RET_CMD_FINISHED)
	{
		return true;
	}
	return false;
}

bool Nextion::SendCommand()
{
	HAL_UART_Transmit(uart, (unsigned char*)buffer, strlen(buffer), UART_TIMEOUT);
	HAL_UART_Transmit(uart, NEXT_END, 3, UART_TIMEOUT);
	recBuffer[NEXTION_REC_SIZE] = {0};
	HAL_UART_Receive(uart, recBuffer, 8, UART_TIMEOUT);
	return CommandCheck();
}

bool Nextion::SendCommand(const char *buffer)
{
	HAL_UART_Transmit(uart, (unsigned char*)buffer, strlen(buffer), UART_TIMEOUT);
	HAL_UART_Transmit(uart, NEXT_END, 3, UART_TIMEOUT);
	recBuffer[NEXTION_REC_SIZE] = {0};
	HAL_UART_Receive(uart, recBuffer, 8, UART_TIMEOUT);
	return CommandCheck();
}

void Nextion::SetBaud(int baud, bool save)
{
	const char* cmdStr = save ? "bauds" : "baud";
	snprintf(buffer, 12, "%s=%d", cmdStr, baud);
	SendCommand();
}

void Nextion::ToggleSleep()
{
	bool en = !this->sleep;
	snprintf(buffer, 0, "sleep=%d", (uint8_t)en);
	if (SendCommand())
	{
		this->sleep = en;
	}
}

void Nextion::ToggleSleep(bool en)
{
	snprintf(buffer, 0, "sleep=%d", (uint8_t)en);
	if (SendCommand())
	{
		this->sleep = en;
	}
}

void Nextion::HomePage()
{
	SetPage(0);
}

void Nextion::SetPage(uint8_t id)
{
	snprintf(buffer, 8, "page %d", id);
	SendCommand();
}

void Nextion::SetBrightness(uint8_t bright, bool save)
{
	const char* cmdStr = save ? "dims" : "dim";
	snprintf(buffer, 7, "%s=%d", cmdStr, bright);
	if (SendCommand())
	{
		this->bright = bright;
	}
}

void Nextion::FullBrightness(bool save)
{
	SetBrightness(100, save);
}

void Nextion::SetNumber(uint8_t id, int value)
{
	snprintf(buffer, 12, "n%d.val=%d", id, value);
	SendCommand();
}

void Nextion::SetProgressBar(uint8_t id, uint8_t value)
{
	snprintf(buffer, 10, "j%d.val=%d", id, value);
	SendCommand();
}

void Nextion::SetGauge(uint8_t id, uint16_t angle)
{
	snprintf(buffer, 10, "z%d.val=%d", id, angle);
	SendCommand();
}

void Nextion::UpdateGraph(uint8_t id, uint8_t ch, uint8_t value)
{
	snprintf(buffer, 12, "add %d,%d,%d", id, ch, value);
	SendCommand();
}

void Nextion::ClearGraph(uint8_t id, uint8_t ch)
{
	snprintf(buffer, 8, "cle %d,%d", id, ch);
	SendCommand();
}

void Nextion::SetGraphScale(uint8_t id, uint16_t scale)
{
	snprintf(buffer, 11, "s%d.dis=%d", id, scale);
	SendCommand();
}

void Nextion::SetClick(uint8_t id, bool en)
{
	snprintf(buffer, 10, "click %d,%d", id, (uint8_t)en);
	SendCommand();
}

