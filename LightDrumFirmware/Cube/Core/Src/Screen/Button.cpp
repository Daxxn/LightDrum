/*
 * Button.cpp
 *
 *  Created on: May 26, 2023
 *      Author: Daxxn
 */

#include <Screen/Button.h>

Button::~Button()
{
}

void Button::Press(bool press)
{
	this->pressActive = press;
}

void Button::UpdateState()
{
	this->nxt->SetClick(this->ID, this->pressActive);
}

void Button::Act()
{
	if (this->btnAction != NULL)
	{
		this->btnAction();
	}
}
