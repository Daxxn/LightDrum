/*
 * CheckBox.h
 *
 *  Created on: May 28, 2023
 *      Author: Daxxn
 */

#ifndef INC_SCREEN_CHECKBOX_H_
#define INC_SCREEN_CHECKBOX_H_

#include "Control.h"

/*
 *
 */
class CheckBox : public Control
{
public:
	CheckBox(Nextion *nxt, uint8_t id, const char *name, uint8_t navX, uint8_t navY): Control(nxt, id, name, navX, navY) {};
	virtual ~CheckBox();
private:
	bool isChecked;
};

#endif /* INC_SCREEN_CHECKBOX_H_ */
