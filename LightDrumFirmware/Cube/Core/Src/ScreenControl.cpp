/*
 * ScreenControl.cpp
 *
 *  Created on: May 21, 2023
 *      Author: Daxxn
 */

#include "ScreenControl.h"

ScreenControl::~ScreenControl()
{
	this->nxt = NULL;
	delete[] this->pages;
}

HAL_StatusTypeDef ScreenControl::Init(Nextion *nxt, Page *pages)
{
	this->nxt = nxt;
	this->pages = pages;
	return HAL_OK;
}

void ScreenControl::NavigateHorz(int8_t x)
{
	this->currentPage->Navigate(x, 0);
}

void ScreenControl::NavigateVert(int8_t y)
{
	this->currentPage->Navigate(0, y);
}

void ScreenControl::Navigate(int8_t x, int8_t y)
{
	this->currentPage->Navigate(x, y);
}

void ScreenControl::ChangePageEvent(uint8_t pageID)
{
	this->currentPage = &this->pages[pageID];
	this->currentPage->Init();
}

void ScreenControl::ChangePage(uint8_t pageID)
{
	for (int i = 0; i < PAGE_COUNT; ++i) {
		if (this->pages[i].ID == pageID)
		{
			if (this->currentPage != NULL)
			{
				this->prevPage = this->currentPage->ID;
			}
			this->currentPage = &this->pages[i];
			this->currentPage->Init();
			return;
		}
	}
}

void ScreenControl::PageBack()
{
	if (this->prevPage != NULL_PAGE)
	{
		this->ChangePage(this->prevPage);
	}
}

void ScreenControl::HomePage()
{
	this->ChangePage(HOME_PAGE);
}

void ScreenControl::ChangePage_Index(uint8_t index)
{
	this->currentPage = &this->pages[index];
	this->currentPage->Init();
}

void ScreenControl::TouchEvent(uint8_t pageID, uint8_t compID, uint8_t event)
{
	if (this->CheckPage(pageID))
	{
		Control* ctrl = this->currentPage->FindControl(compID);
		if (ctrl != NULL)
		{
			ctrl->Act();
		}
	}
}

void ScreenControl::Act()
{
	this->currentPage->Act();
}

void ScreenControl::ChangeText(const char *objId, const char* text, uint8_t len)
{
	this->nxt->SetText(objId, text, len);
}

bool ScreenControl::CheckPage(uint8_t pageID)
{
	return this->currentPage->ID == pageID;
}
