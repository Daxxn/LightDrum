/*
 * Component.h
 *
 *  Created on: May 26, 2023
 *      Author: Daxxn
 */

#ifndef INC_SCREEN_COMPONENT_H_
#define INC_SCREEN_COMPONENT_H_

#include "main.h"
#include "Nextion.h"

/*
 *
 */
class Component
{
public:
	Component(Nextion *next, uint8_t id) { nxt = next; ID = id; };
	virtual ~Component();

	uint8_t ID;
	bool IsActive = false;

	virtual void Act() {};
protected:
	Nextion *nxt;
};

#endif /* INC_SCREEN_COMPONENT_H_ */
