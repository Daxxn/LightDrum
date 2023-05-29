/*
 * PageButton.h
 *
 *  Created on: May 27, 2023
 *      Author: Daxxn
 */

#ifndef INC_SCREEN_PAGEBUTTON_H_
#define INC_SCREEN_PAGEBUTTON_H_

#include "Control.h"

typedef void (*ChangePageCallback)(uint8_t pageID);

/*
 *
 */
class PageButton : public Control
{
public:
	PageButton(Nextion *nxt, uint8_t id, const char* name, uint8_t navX, uint8_t navY, uint8_t pageID, ChangePageCallback callback): Control(nxt, id, name, navX, navY) {
		this->pageID = pageID;
		this->callback = callback;
	};
	virtual ~PageButton();

	void Press(bool press);

	void UpdateState();

	void Act();
private:
	uint8_t pageID;
	ChangePageCallback callback;
};

#endif /* INC_SCREEN_PAGEBUTTON_H_ */
