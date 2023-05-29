/*
 * ProgressBar.cpp
 *
 *  Created on: May 27, 2023
 *      Author: Daxxn
 */

#include <Screen/ProgressBar.h>

ProgressBar::~ProgressBar()
{
}

void ProgressBar::UpdateState()
{
	this->nxt->SetProgressBar(ID, value);
}
