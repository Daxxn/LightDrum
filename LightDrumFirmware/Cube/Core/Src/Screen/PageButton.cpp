/*
 * PageButton.cpp
 *
 *  Created on: May 27, 2023
 *      Author: Daxxn
 */

#include <Screen/PageButton.h>

PageButton::~PageButton()
{
}

void PageButton::Press(bool press)
{
	this->IsActive = press;
}

void PageButton::UpdateState()
{
	this->nxt->SetClick(ID, IsActive);
}

void PageButton::Act()
{
	this->callback(this->pageID);
}
