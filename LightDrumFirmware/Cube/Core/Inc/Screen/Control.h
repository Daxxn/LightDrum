/*
 * Control.h
 *
 *  Created on: May 26, 2023
 *      Author: Daxxn
 */

#ifndef INC_SCREEN_CONTROL_H_
#define INC_SCREEN_CONTROL_H_

#include "Component.h"

#define IGNORE_NAV 255

/*
 *
 */
class Control : public Component
{
public:
	Control(Nextion *nxt, uint8_t id, const char* name, uint8_t navX, uint8_t navY): Component(nxt, id) {
		ObjName = name;
		navXIndex = navX;
		navYIndex = navY;
	};
	Control(Nextion *nxt, uint8_t id, const char* name): Component(nxt, id) {
		navXIndex = IGNORE_NAV;
		navYIndex = IGNORE_NAV;
	}
	virtual ~Control();

	bool CheckNav(uint8_t &x, uint8_t &y) { return x == this->navXIndex && y == this->navYIndex; };

	uint8_t GetNavX() { return this->navXIndex; };
	uint8_t GetNavY() { return this->navYIndex; };

	virtual void UpdateState() {};
	virtual void SetNav();
	virtual void ClearNav();
protected:
	const char* ObjName;
	uint8_t navXIndex;
	uint8_t navYIndex;
};

#endif /* INC_SCREEN_CONTROL_H_ */
