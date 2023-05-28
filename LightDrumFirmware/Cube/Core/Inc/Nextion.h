/*
 * Nextion.h
 *
 *  Created on: Feb 11, 2023
 *      Author: Daxxn
 */

#ifndef INC_NEXTION_H_
#define INC_NEXTION_H_

#include "main.h"

typedef void (*PageChangeCallback)(uint8_t pageNum);
typedef void (*TouchEventCallback)(uint8_t pageID, uint8_t compID, uint8_t event);

typedef struct
{
	PageChangeCallback PageChange;
	TouchEventCallback TouchEvent;
} NextionCallbacks;

const uint8_t NEXT_END[] = {0xFF, 0xFF, 0xFF};

#if __cplusplus

class Nextion {
public:
	Nextion();
	virtual ~Nextion();

	void Startup(UART_HandleTypeDef *uart, NextionCallbacks callbacks);
	void Reset();
	void SetBaud(int baud, bool save = true);

	void HomePage();
	void SetPage(uint8_t id);

	void ToggleSleep();
	void ToggleSleep(bool sleep);

	void SetBrightness(uint8_t bright, bool save = false);
	void FullBrightness(bool save = false);

	void SetNumber(uint8_t objId, int value);
	void SetNumber(const char *objId, int value);
	void SetProgressBar(uint8_t objId, uint8_t value);
	void SetProgressBar(const char *objId, uint8_t value);
	void SetGauge(uint8_t objId, uint16_t angle);
	void SetGauge(const char *objId, uint16_t angle);
	void SetText(uint8_t id, const char *str, int len);
	void SetText(const char *id, const char *str, int len);

	void SetClick(uint8_t id, bool en);
	void MenuNav(uint8_t id);

	void UpdateGraph(uint8_t id, uint8_t ch, uint8_t value);
	void ClearGraph(uint8_t id, uint8_t ch);
	void SetGraphScale(uint8_t objId, uint16_t scale);
	void SetGraphScale(const char *objId, uint16_t scale);

	void Receive();

	HAL_StatusTypeDef CheckForTouchEvents();
private:
	bool                sleep;
	uint8_t             bright;
	uint8_t             index;
	uint8_t            *cmdBuffer;
	uint8_t            *recBuffer;
	char               *buffer;

	UART_HandleTypeDef *uart;
	NextionCallbacks callbacks;

	bool SendCommand();
	bool SendCommand(const char *buffer);

	bool CommandCheck();

	void ParseCommands();
};

#endif /* __cplusplus */
#endif /* INC_NEXTION_H_ */
