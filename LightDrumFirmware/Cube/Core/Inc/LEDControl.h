/*
 * LEDControl.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Daxxn
 */

#ifndef INC_LEDCONTROL_H_
#define INC_LEDCONTROL_H_

#include "main.h"
#include "PCA9634.h"
#include "StripControl.h"

#define STRIP_DRIVER_COUNT 3

struct LEDStrip
{
	LEDStrip() {
		this->driverIndex = -1;
		this->driverChannel = -1;
	};
	LEDStrip(uint8_t driver, uint8_t channel) {
		this->driverIndex = driver;
		this->driverChannel = channel;
	};
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;

	uint8_t driverIndex;
	uint8_t driverChannel;
};

/*
 *
 */
class LEDControl
{
public:
	LEDControl(PCA9634 *drivers, StripControl *control);
	virtual ~LEDControl();

	HAL_StatusTypeDef Init();

	void UpdateStrip(uint8_t strip, uint8_t red, uint8_t green, uint8_t blue);

	void Update();
private:
	PCA9634 *drivers;
	LEDStrip *strips;
	StripControl *control;

	int i = 0;
};

#endif /* INC_LEDS_LEDCONTROL_H_ */
