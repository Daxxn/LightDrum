/*
 * PageButton.h
 *
 *  Created on: May 27, 2023
 *      Author: Daxxn
 */

#ifndef INC_SCREEN_PAGEBUTTON_H_
#define INC_SCREEN_PAGEBUTTON_H_

#include "Control.h"

/*
 *
 */
class PageButton : public Control
{
public:
	PageButton(Nextion *nxt, uint8_t id, const char* name, uint8_t navX, uint8_t navY, uint8_t pageID): Control(nxt, id, name, navX, navY) {};
	virtual ~PageButton();

	void Press(bool press);

	void UpdateState();

	void Act();
private:
	uint8_t pageID;
};

#endif /* INC_SCREEN_PAGEBUTTON_H_ */
