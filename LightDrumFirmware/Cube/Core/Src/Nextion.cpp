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
	memset(this->cmdBuffer, 0, NEXTION_BUFFER);
	memset(this->recBuffer, 0, NEXTION_REC_SIZE);
	memset(this->buffer, 0, NEXTION_BUFFER);
	this->index = 0;
}

Nextion::~Nextion()
{
	delete[] this->cmdBuffer;
	delete[] this->recBuffer;
	delete[] this->buffer;
}

void Nextion::Startup(UART_HandleTypeDef *uart, NextionCallbacks callbacks)
{
	this->uart = uart;
	this->callbacks = callbacks;
//	SetBaud(BAUD_RATE, false);
	HAL_UART_Receive(uart, this->recBuffer, NEXTION_REC_SIZE, UART_TIMEOUT);
	SendCommand("bkcmd=2");
#if DISABLE_TOUCH == 1
	// There doesnt seem to be a global "Disable Touch" command...
	SendCommand("");
#endif
	HAL_Delay(50);
	this->Reset();
}

void Nextion::Reset()
{
	SendCommand("rest");
	HAL_Delay(250);
}

bool Nextion::CommandCheck()
{
	if (this->recBuffer[0] == 0 || this->recBuffer[0] == NEX_RET_CMD_FINISHED)
	{
		return true;
	}
	if (this->recBuffer[0] == NEX_RET_CURRENT_PAGE_ID_HEAD)
	{
		this->callbacks.PageChange(this->recBuffer[1]);
		return true;
	}
	if (this->recBuffer[0] == NEX_RET_EVENT_TOUCH_HEAD)
	{
		this->callbacks.TouchEvent(this->recBuffer[1], this->recBuffer[2], this->recBuffer[3]);
		return true;
	}
	return false;
}

bool Nextion::SendCommand()
{
	HAL_UART_Transmit(this->uart, (unsigned char*)this->buffer, strlen(this->buffer), UART_TIMEOUT);
	HAL_UART_Transmit(this->uart, NEXT_END, 3, UART_TIMEOUT);
	HAL_UART_Receive(this->uart, this->recBuffer, NEXTION_REC_SIZE, UART_TIMEOUT);
	return CommandCheck();
}

bool Nextion::SendCommand(const char *buffer)
{
	HAL_UART_Transmit(this->uart, (unsigned char*)buffer, strlen(buffer), UART_TIMEOUT);
	HAL_UART_Transmit(this->uart, NEXT_END, 3, UART_TIMEOUT);
	HAL_UART_Receive(this->uart, this->recBuffer, NEXTION_REC_SIZE, UART_TIMEOUT);
	return CommandCheck();
}

void Nextion::SetBaud(int baud, bool save)
{
	const char* cmdStr = save ? "bauds" : "baud";
	snprintf(this->buffer, 12, "%s=%d", cmdStr, baud);
	SendCommand();
}

void Nextion::ToggleSleep()
{
	bool en = !this->sleep;
	snprintf(this->buffer, 0, "sleep=%d", (uint8_t)en);
	if (SendCommand())
	{
		this->sleep = en;
	}
}

void Nextion::ToggleSleep(bool en)
{
	snprintf(this->buffer, 0, "sleep=%d", (uint8_t)en);
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
	snprintf(this->buffer, 8, "page %d", id);
	SendCommand();
}

void Nextion::SetBrightness(uint8_t bright, bool save)
{
	const char* cmdStr = save ? "dims" : "dim";
	snprintf(this->buffer, 7, "%s=%d", cmdStr, bright);
	if (SendCommand())
	{
		this->bright = bright;
	}
}

void Nextion::FullBrightness(bool save)
{
	SetBrightness(100, save);
}

void Nextion::SetNumber(uint8_t objId, int value)
{
	snprintf(this->buffer, 12, "n%d.val=%d", objId, value);
	SendCommand();
}

void Nextion::SetNumber(const char* objId, int value)
{
	snprintf(this->buffer, 12, "%s.val=%d", objId, value);
	SendCommand();
}

void Nextion::SetProgressBar(uint8_t objId, uint8_t value)
{
	snprintf(this->buffer, 10, "j%d.val=%d", objId, value);
	SendCommand();
}

void Nextion::SetProgressBar(const char* objId, uint8_t value)
{
	snprintf(this->buffer, 10, "%s.val=%d", objId, value);
	SendCommand();
}

void Nextion::SetGauge(uint8_t objId, uint16_t angle)
{
	snprintf(this->buffer, 10, "z%d.val=%d", objId, angle);
	SendCommand();
}

void Nextion::SetGauge(const char* objId, uint16_t angle)
{
	snprintf(this->buffer, 10, "%s.val=%d", objId, angle);
	SendCommand();
}

void Nextion::SetText(uint8_t objId, const char *str, int len)
{
	snprintf(this->buffer, len + 10, "t%d.txt=\"%s\"", objId, str);
	SendCommand();
}

void Nextion::SetText(const char *objId, const char *str, int len)
{
	snprintf(this->buffer, len + 10, "%s.txt=\"%s\"", objId, str);
	SendCommand();
}

void Nextion::UpdateGraph(uint8_t id, uint8_t ch, uint8_t value)
{
	snprintf(this->buffer, 12, "add %d,%d,%d", id, ch, value);
	SendCommand();
}

void Nextion::ClearGraph(uint8_t id, uint8_t ch)
{
	snprintf(this->buffer, 8, "cle %d,%d", id, ch);
	SendCommand();
}

void Nextion::SetGraphScale(uint8_t objId, uint16_t scale)
{
	snprintf(this->buffer, 11, "s%d.dis=%d", objId, scale);
	SendCommand();
}

void Nextion::SetGraphScale(const char* objId, uint16_t scale)
{
	snprintf(this->buffer, 11, "%s.dis=%d", objId, scale);
	SendCommand();
}

void Nextion::SetClick(uint8_t id, bool en)
{
	snprintf(this->buffer, 10, "click %d,%d", id, (uint8_t)en);
	SendCommand();
}

void Nextion::MenuNav(uint8_t id)
{
	this->SetClick(id, true);
}

void Nextion::Receive()
{
	if (HAL_UART_Receive(uart, this->recBuffer, NEXTION_REC_SIZE, UART_TIMEOUT) == HAL_OK)
	{
		CommandCheck();
	}
}

HAL_StatusTypeDef Nextion::CheckForTouchEvents()
{
	if (HAL_UART_Receive(uart, this->recBuffer, NEXTION_REC_SIZE, UART_TIMEOUT) == HAL_OK)
	{
		if (this->recBuffer[0] != 0)
		{
			this->ParseCommands();
		}
	}
	return HAL_OK;
}

void Nextion::ParseCommands()
{
	for (int i = 0; i < NEXTION_REC_SIZE; ++i)
	{
		uint8_t value = (uint8_t)this->recBuffer[i];
		if (this->recBuffer[i] == NEX_RET_EVENT_TOUCH_HEAD && this->recBuffer[i + 4] == NXT_END_VAL && this->recBuffer[i + 5] == NXT_END_VAL && this->recBuffer[i + 6] == NXT_END_VAL)
		{
			this->callbacks.TouchEvent(this->recBuffer[i + 1], this->recBuffer[i + 2], this->recBuffer[i + 3]);
		}
	}
}
