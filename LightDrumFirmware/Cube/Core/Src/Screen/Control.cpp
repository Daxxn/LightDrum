/*
 * Control.cpp
 *
 *  Created on: May 26, 2023
 *      Author: Daxxn
 */

#include <Screen/Control.h>

Control::~Control()
{
}

void Control::SetNav()
{
	if (!this->IsActive) {
		this->IsActive = true;
		this->nxt->SetClick(ID, true);
	}
}

void Control::ClearNav()
{
	if (this->IsActive)
	{
		this->IsActive = false;
		this->nxt->SetClick(ID, false);
	}
}
