/*
 * MainWrapper.h
 *
 *  Created on: Feb 5, 2023
 *      Author: Daxxn
 */

#ifndef INC_MAINWRAPPER_H_
#define INC_MAINWRAPPER_H_

HAL_StatusTypeDef Init(
		ADC_HandleTypeDef    *in_hadc1,
		DMA_HandleTypeDef    *in_hdma_adc1,

		FMPI2C_HandleTypeDef *in_hfmpi2c1,
		DMA_HandleTypeDef    *in_hdma_fmpi2c1_tx,

		I2C_HandleTypeDef    *in_hi2c1,

		I2S_HandleTypeDef    *in_hi2s5,
		DMA_HandleTypeDef    *hdma_spi5_rx,

		SPI_HandleTypeDef    *in_hspi4,

		TIM_HandleTypeDef    *in_htim1,
		TIM_HandleTypeDef    *in_htim3,
		TIM_HandleTypeDef    *in_htim8,

		UART_HandleTypeDef   *in_huart1,
		UART_HandleTypeDef   *in_huart2,
		UART_HandleTypeDef   *in_huart3,

		RTC_HandleTypeDef    *in_hrtc,
		SD_HandleTypeDef     *in_hsd
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

void AudioHalfFullCallback();
void AudioFullCallback();
void CurrentConvFullCallback();

void ScreenReceiveCallback();

#endif /* INC_MAINWRAPPER_H_ */
