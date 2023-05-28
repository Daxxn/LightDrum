/*
 * Page.h
 *
 *  Created on: May 26, 2023
 *      Author: Daxxn
 */

#ifndef INC_SCREEN_PAGE_H_
#define INC_SCREEN_PAGE_H_

#include "Control.h"
#include "Button.h"
#include "PageButton.h"
#include "ProgressBar.h"

/*
 *
 */
class Page : public Component
{
public:
	Page(
			Nextion *nxt,
			uint8_t id,
			Button *btns,
			int btnCount,
			PageButton *pageBtns,
			int pageBtnCount
		);
	Page(
			Nextion *nxt,
			uint8_t id,
			Button *btns,
			int btnCount,
			PageButton *pageBtns,
			int pageBtnCount,
			ProgressBar *progBars,
			int pbCount
		);
	virtual ~Page();

	void Init();

	void Navigate(int8_t x, int8_t y);
	void ResetNavigation();
	void Act();

	Control* FindControl(uint8_t id);

	bool WrapXNav;
	bool WrapYNav;
	Control *CurrentControl;
private:
	PageButton *pageButtons;
	Button *buttons;
	ProgressBar *progBars;
	int btnCount;
	int pageBtnCount;
	int pbCount;

	uint8_t currentXNav;
	uint8_t currentYNav;

	uint8_t maxXNav;
	uint8_t maxYNav;
};

#endif /* INC_SCREEN_PAGE_H_ */
