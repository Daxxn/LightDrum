/*
 * NumberBox.h
 *
 *  Created on: May 27, 2023
 *      Author: Daxxn
 */

#ifndef INC_SCREEN_NUMBERBOX_H_
#define INC_SCREEN_NUMBERBOX_H_

#include "Control.h"

/*
 *
 */
class NumberBox : public Control
{
public:
	NumberBox(Nextion *nxt, uint8_t id, const char* name): Control(nxt, id, name) {};
	virtual ~NumberBox();
private:
	int32_t value;
};

#endif /* INC_SCREEN_NUMBERBOX_H_ */
