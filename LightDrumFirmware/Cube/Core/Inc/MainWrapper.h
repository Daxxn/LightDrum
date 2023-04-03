/*
 * MainWrapper.h
 *
 *  Created on: Feb 5, 2023
 *      Author: Daxxn
 */

#ifndef INC_MAINWRAPPER_H_
#define INC_MAINWRAPPER_H_

void Init(
	ADC_HandleTypeDef *in_hadc1,
//	DMA_HandleTypeDef *in_hdma_adc1,
	I2C_HandleTypeDef *in_hi2c1,
	SPI_HandleTypeDef *in_hspi2,
	SPI_HandleTypeDef *in_hspi5,
	TIM_HandleTypeDef *in_htim2,
	TIM_HandleTypeDef *in_htim3,
	UART_HandleTypeDef *in_huart1,
	UART_HandleTypeDef *in_huart2
);

void InitTest();

void Main();

void MenuUpInterruptCallback();
void MenuDownInterruptCallback();
void MenuLeftInterruptCallback();
void MenuRightInterruptCallback();
void MenuActInterruptCallback();
void MenuBackInterruptCallback();
void Enc1SwInterruptCallback();
void Enc2SwInterruptCallback();
void Enc1TurnInterruptCallback();
void Enc2TurnInterruptCallback();


#endif /* INC_MAINWRAPPER_H_ */
