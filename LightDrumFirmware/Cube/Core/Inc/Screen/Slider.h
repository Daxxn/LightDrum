/*
 * Slider.h
 *
 *  Created on: May 27, 2023
 *      Author: Daxxn
 */

#ifndef INC_SCREEN_SLIDER_H_
#define INC_SCREEN_SLIDER_H_

#include "Control.h"

/*
 *
 */
class Slider : public Control
{
public:
	Slider(Nextion *nxt, uint8_t id, const char* name, uint8_t navX, uint8_t navY): Control(nxt, id, name, navX, navY) {};
	Slider(Nextion *nxt, uint8_t id, const char* name, uint8_t navX, uint8_t navY, uint8_t defaultValue): Control(nxt, id, name, navX, navY) {
		value = defaultValue;
	};
	virtual ~Slider();
private:
	uint8_t value;
};

#endif /* INC_SCREEN_SLIDER_H_ */
