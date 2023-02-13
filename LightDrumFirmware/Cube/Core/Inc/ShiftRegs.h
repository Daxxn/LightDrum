/*
 * ShiftRegs.h
 *
 *  Created on: Feb 12, 2023
 *      Author: Daxxn
 */

#ifndef INC_SHIFTREGS_H_
#define INC_SHIFTREGS_H_

#include "main.h"
#include "Utils.h"

#if __cplusplus

#define REG_SIZE 16

typedef enum
{
	MSB = 0,
	LSB = 1
}DataDirection;

typedef enum
{
	OFF = 0,
	ON = 1
}LEDState;

union ShiftRegUnion
{
	uint16_t number;
	uint8_t upper;
	uint8_t lower;
};

/*
 *
 */
class ShiftRegs
{
public:
	ShiftRegs() {};
	ShiftRegs(SPI_HandleTypeDef *spi, Pin OEPin, Pin LEPin, DataDirection dir);
	virtual ~ShiftRegs();

	void Init();

	void SetBuffer(uint8_t *buffer);

	void SetValue(LEDState value, size_t index);
	void SetValue(uint8_t value, size_t index);

	void ToggleValue(size_t index);

	void Clear();

	void Update();

	uint32_t Timeout;
private:
	Pin OEPin;
	Pin LEPin;
	uint16_t _temp;
	SPI_HandleTypeDef *_spi;
	DataDirection _dir;

	uint8_t *_buffer;
	ShiftRegUnion *_union;

	uint8_t GetValue(size_t index);
};

#endif /* __cplusplus */
#endif /* INC_SHIFTREGS_H_ */
