/*
 * Page.cpp
 *
 *  Created on: May 26, 2023
 *      Author: Daxxn
 */

#include <Screen/Page.h>

Page::Page(Nextion *nxt, uint8_t id, Button *btns, int btnCount, PageButton *pageBtns, int pageBtnCount): Component(nxt, id)
{
	this->buttons = btns;
	this->pageButtons = pageBtns;
	this->pageBtnCount = pageBtnCount;
	this->btnCount = btnCount;
	this->progBars = NULL;
	this->pbCount = 0;

	this->CurrentControl = &btns[0];

	uint8_t temp1 = 0;
	uint8_t temp2 = 0;
	int i = 0;
	for (i = 0; i < btnCount; ++i) {
		temp1 = this->buttons[i].GetNavX();
		if (this->maxXNav < temp1)
		{
			this->maxXNav = temp1;
		}
		temp1 = this->buttons[i].GetNavY();
		if (this->maxYNav < temp1)
		{
			this->maxYNav = temp1;
		}
	}
	for (i = 0; i < pageBtnCount; ++i)
	{
		temp2 = this->pageButtons[i].GetNavX();
		if (this->maxXNav < temp2)
		{
			this->maxXNav = temp2;
		}
		temp2 = this->pageButtons[i].GetNavY();
		if (this->maxYNav < temp2)
		{
			this->maxYNav = temp2;
		}
	}
}

Page::Page(
		Nextion *nxt,
		uint8_t id,
		Button *btns,
		int btnCount,
		PageButton *pageBtns,
		int pageBtnCount,
		ProgressBar *progBars,
		int pbCount
	): Component(nxt, id)
{
	this->buttons = btns;
	this->pageButtons = pageBtns;
	this->progBars = progBars;
	this->btnCount = btnCount;
	this->pageBtnCount = pageBtnCount;
	this->pbCount = pbCount;

	this->CurrentControl = &btns[0];

	uint8_t temp1 = 0;
	uint8_t temp2 = 0;
	for (int i = 0; i < btnCount; ++i) {
		temp1 = this->buttons[i].GetNavX();
		temp2 = this->pageButtons[i].GetNavX();
		if (this->maxXNav < temp1)
		{
			this->maxXNav = temp1;
		}
		else if (this->maxXNav < temp2)
		{
			this->maxXNav = temp2;
		}
		temp1 = this->buttons[i].GetNavY();
		temp2 = this->pageButtons[i].GetNavY();
		if (this->maxYNav < temp1)
		{
			this->maxYNav = temp1;
		}
		if (this->maxYNav < temp2)
		{
			this->maxYNav = temp2;
		}
	}
}


Page::~Page()
{
	delete[] this->buttons;
	delete[] this->pageButtons;
	delete[] this->progBars;
	this->CurrentControl = NULL;
	this->nxt = NULL;
}

void Page::Navigate(int8_t x, int8_t y)
{
	int8_t tempX = x + this->currentXNav;
	int8_t tempY = y + this->currentYNav;
	if (tempX > this->maxXNav || tempX < 0)
	{
		this->currentXNav = this->WrapXNav ? 0 : this->maxXNav;
	}
	else
	{
		this->currentXNav = tempX;
	}
	if (tempY > this->maxYNav || tempY < 0)
	{
		this->currentYNav = this->WrapYNav ? 0 : this->maxYNav;
	}
	else
	{
		this->currentYNav = tempY;
	}
	int i;
	for (i = 0; i < this->btnCount; ++i) {
		if (this->buttons[i].CheckNav(this->currentXNav, this->currentYNav))
		{
			this->buttons[i].SetNav();
			this->CurrentControl = &this->buttons[i];
		}
		else
		{
			this->buttons[i].ClearNav();
		}
	}
	for (i = 0; i < this->pageBtnCount; ++i) {
		if (this->pageButtons[i].CheckNav(currentXNav, currentYNav))
		{
			this->pageButtons[i].SetNav();
			this->CurrentControl = &this->pageButtons[i];
		}
		else
		{
			this->pageButtons[i].ClearNav();
		}
	}
}

void Page::Init()
{
	this->nxt->SetPage(ID);
	this->ResetNavigation();
}

void Page::Act()
{
	this->CurrentControl->Act();
}

Control* Page::FindControl(uint8_t id)
{
	for (int i = 0; i < this->btnCount; ++i) {
		if (this->buttons[i].ID == id)
		{
			this->CurrentControl = &this->buttons[i];
			return &this->buttons[i];
		}
	}
	return NULL;
}

void Page::ResetNavigation()
{
	this->CurrentControl = NULL;
	this->Navigate(0, 0);
}
