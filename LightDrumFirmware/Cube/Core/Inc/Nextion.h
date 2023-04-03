/*
 * Nextion.h
 *
 *  Created on: Feb 11, 2023
 *      Author: Daxxn
 */

#ifndef INC_NEXTION_H_
#define INC_NEXTION_H_

#include "main.h"

//typedef struct NextionElement
//{
//	const char *Name;
//	const char *ObjID;
//	uint8_t ID;
//	uint8_t Type;
//};

const uint8_t NEXT_END[] = {0xFF, 0xFF, 0xFF};

#if __cplusplus

class Nextion {
public:
	Nextion();
	virtual ~Nextion();

	void Startup(UART_HandleTypeDef *uart);

	void SetBaud(int baud, bool save = true);

	void HomePage();
	void SetPage(uint8_t id);

	void ToggleSleep();
	void ToggleSleep(bool sleep);

	void SetBrightness(uint8_t bright, bool save = false);
	void FullBrightness(bool save = false);

	void SetNumber(uint8_t id, int value);
	void SetText(uint8_t id, const char *str, int len);
	void SetProgressBar(uint8_t id, uint8_t value);
	void SetGauge(uint8_t id, uint16_t angle);

	void SetClick(uint8_t id, bool en);

	void UpdateGraph(uint8_t id, uint8_t ch, uint8_t value);
	void ClearGraph(uint8_t id, uint8_t ch);
	void SetGraphScale(uint8_t id, uint16_t scale);
private:
	bool                sleep;
	uint8_t             bright;
	uint8_t             index;
	uint8_t            *cmdBuffer;
	uint8_t            *recBuffer;
	char               *buffer;
	UART_HandleTypeDef *uart;

	bool SendCommand();
	bool SendCommand(const char *buffer);

	bool CommandCheck();
};

#endif /* __cplusplus */
#endif /* INC_NEXTION_H_ */
