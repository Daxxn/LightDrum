/*
 * MainWrapper.cpp
 *
 * This sucks. The code config generator doesnt export in *.cpp files.
 * The only way to get *.cpp code to run is to wrap the main functions.
 *
 *  Created on: Feb 5, 2023
 *      Author: Daxxn
 */

#include "main.h"

//uint8_t count = 0;
//uint8_t page = 0;

const int delay = 500;
//void Blink()
//{
//	HAL_GPIO_WritePin(EXT_LED_GPIO_Port, EXT_LED_Pin, GPIO_PIN_SET);
//	HAL_Delay(200);
//	HAL_GPIO_WritePin(EXT_LED_GPIO_Port, EXT_LED_Pin, GPIO_PIN_RESET);
//}

void ToggleTest(uint8_t count, int delay)
{
	for (int i = 0; i < count; ++i)
	{
		HAL_GPIO_WritePin(EEPROM_WP_GPIO_Port, EEPROM_WP_Pin, GPIO_PIN_SET);
		HAL_Delay(delay);
		HAL_GPIO_WritePin(EEPROM_WP_GPIO_Port, EEPROM_WP_Pin, GPIO_PIN_RESET);
		HAL_Delay(delay);
	}
}

/**
  * @brief C++ Initialization Function
  * @retval None
  */
void Init()
{

}


/**
  * @brief C++ Main Loop Function
  * @retval None
  */
void Main()
{
	ToggleTest(10, delay);
	HAL_Delay(delay * 2);
}
