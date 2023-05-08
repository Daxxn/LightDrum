/*
 * PCA9634.h
 *
 *  Created on: Feb 11, 2023
 *      Author: Daxxn
 */

#ifndef INC_PCA9634_H_
#define INC_PCA9634_H_

#include "main.h"

/*
 *
 */
class PCA9634
{
public:
	PCA9634();
	virtual ~PCA9634();
private:
	FMPI2C_HandleTypeDef *i2cBus;
};

#endif /* INC_PCA9634_H_ */
