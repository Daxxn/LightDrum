/*
 * Button.h
 *
 *  Created on: May 26, 2023
 *      Author: Daxxn
 */

#ifndef INC_SCREEN_BUTTON_H_
#define INC_SCREEN_BUTTON_H_

#include "Control.h"

typedef void (*ButtonActionTypeDef)();

/*
 *
 */
class Button : public Control
{
public:
	Button(Nextion *nxt, uint8_t id, const char* name, uint8_t navX, uint8_t navY): Control(nxt, id, name, navX, navY) {};
	Button(Nextion *nxt, uint8_t id, const char* name, uint8_t navX, uint8_t navY, ButtonActionTypeDef action): Control(nxt, id, name, navX, navY) {
		btnAction = action;
	};
	virtual ~Button();

	void Press(bool press);

	void UpdateState();

	void Act();
private:
	bool pressActive;

	ButtonActionTypeDef btnAction = NULL;
};

#endif /* INC_SCREEN_BUTTON_H_ */
