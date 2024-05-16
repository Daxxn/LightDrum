/*
 * ProgressBar.h
 *
 *  Created on: May 27, 2023
 *      Author: Daxxn
 */

#ifndef INC_SCREEN_PROGRESSBAR_H_
#define INC_SCREEN_PROGRESSBAR_H_

#include "Control.h"

/*
 *
 */
class ProgressBar : public Control
{
public:
	ProgressBar(Nextion *nxt, uint8_t id, const char* name): Control(nxt, id, name) {};
	ProgressBar(Nextion *nxt, uint8_t id, const char* name, uint8_t defaultValue): Control(nxt, id, name) {
		value = defaultValue;
	};
	virtual ~ProgressBar();

	void SetValue(uint8_t val) { value = val; };
	uint8_t GetValue() { return value; };

	void UpdateState();
private:
	uint8_t value;
};

#endif /* INC_SCREEN_PROGRESSBAR_H_ */
