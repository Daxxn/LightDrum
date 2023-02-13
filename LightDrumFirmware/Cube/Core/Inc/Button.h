/*
 * Button.h
 *
 *  Created on: Feb 12, 2023
 *      Author: Daxxn
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#include "main.h"
#include "Utils.h"

typedef enum
{
	PRESS = 1,
	RELEASE = 0
}Button_State;

/*
 *
 */
class Button
{
public:
	Button();
	virtual ~Button();

	void Init(void (*handler)(Button_State));
private:
	Pin *_pin;
	Button_State _state;

	void (*handler)(Button_State);
};

#endif /* SRC_BUTTON_H_ */
