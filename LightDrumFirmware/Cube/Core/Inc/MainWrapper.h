/*
 * MainWrapper.h
 *
 *  Created on: Feb 5, 2023
 *      Author: Daxxn
 */

#ifndef INC_MAINWRAPPER_H_
#define INC_MAINWRAPPER_H_

void Init(
		ADC_HandleTypeDef    *in_hadc1,
		DMA_HandleTypeDef    *in_hdma_adc1,
		FMPI2C_HandleTypeDef *in_hfmpi2c1,
		DMA_HandleTypeDef    *in_hdma_fmpi2c1_tx,
		I2C_HandleTypeDef    *in_hi2c1,
		I2S_HandleTypeDef    *in_hi2s3,
		DMA_HandleTypeDef    *in_hdma_spi3_rx,
		RTC_HandleTypeDef    *in_hrtc,
		SD_HandleTypeDef     *in_hsd,
		SPI_HandleTypeDef    *in_hspi4,
		TIM_HandleTypeDef    *in_htim1,
		TIM_HandleTypeDef    *in_htim2,
		TIM_HandleTypeDef    *in_htim3,
		UART_HandleTypeDef   *in_huart1,
		UART_HandleTypeDef   *in_huart2,
		UART_HandleTypeDef   *in_huart3
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
