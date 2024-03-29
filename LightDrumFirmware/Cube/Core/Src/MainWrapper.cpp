/*
 * MainWrapper.cpp
 *
 * This sucks. The code config generator doesnt export in *.cpp files.
 * The only way to get *.cpp code to run is to wrap the main functions.
 *
 *  Created on: Feb 5, 2023
 *      Author: Daxxn
 */

#include <math.h>
#include "main.h"
#include "StripCurrent.h"
#include "Nextion.h"
#include "ShiftRegs.h"
#include "Utils.h"
#include "Button.h"

ADC_HandleTypeDef *currentADCHandle;
DMA_HandleTypeDef *currentADCMemHandle;

FMPI2C_HandleTypeDef *stripI2cHandle;
DMA_HandleTypeDef *dmaTXStripHandle;
I2C_HandleTypeDef *i2cHandle;

I2S_HandleTypeDef *audioHandle;
DMA_HandleTypeDef *dmaRXAudioHandle;

RTC_HandleTypeDef *rtcHandle;

SD_HandleTypeDef *sdHandle;

SPI_HandleTypeDef *graphHandle;

TIM_HandleTypeDef *pwm1Handle;
TIM_HandleTypeDef *pwm2Handle;
TIM_HandleTypeDef *pwm3Handle;
TIM_HandleTypeDef *pwm6Handle;

UART_HandleTypeDef *screenHandle;
UART_HandleTypeDef *midiHandle;
UART_HandleTypeDef *dmxHandle;


ShiftRegs shiftReg;
Nextion screen = Nextion();

Button menuUp = Button();
Button menuDown = Button();

StripCurrent stripCurr = StripCurrent();

uint8_t ledCount = 0;

uint8_t count = 0;
uint8_t page = 0;

GPIO_PinState menuLeftPrev = GPIO_PIN_RESET;

GPIO_PinState relayState = GPIO_PIN_RESET;
uint32_t adcReading = 0;

#define NAV_BACKLIGHT 0
#define MENU_BACK_IND 1
#define MENU_DOWN_IND 2
#define MENU_UP_IND   3
#define MENU_LEFT_IND 4
#define MENU_RIGHT_IND 5

const int delay = 50;
const int i = 127;
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
		HAL_GPIO_WritePin(AUDIO_SRC_IND_GPIO_Port, AUDIO_SRC_IND_Pin, GPIO_PIN_SET);
		HAL_Delay(delay);
		HAL_GPIO_WritePin(AUDIO_SRC_IND_GPIO_Port, AUDIO_SRC_IND_Pin, GPIO_PIN_RESET);
		HAL_Delay(delay);
	}
}

void EaseInDebug()
{
	for (int i = 0; i < 255; ++i) {
//		TIM3->CCR3 = i * 256;
		__HAL_TIM_SET_COMPARE(pwm3Handle, TIM_CHANNEL_3, i * 511);
		HAL_Delay(20);
	}
}

void EaseInStatus()
{
	for (int i = 0; i < 255; ++i) {
//		TIM3->CCR2 = i * 256;
		__HAL_TIM_SET_COMPARE(pwm3Handle, TIM_CHANNEL_2, i * 511);
		HAL_Delay(20);
	}
}

void ReadCurrent()
{
	HAL_ADC_Start(currentADCHandle);
	if (HAL_ADC_PollForConversion(currentADCHandle, 500) == HAL_OK)
	{
		adcReading = HAL_ADC_GetValue(currentADCHandle);
//		uint8_t perc = (uint8_t)((adcReading / UINT8_MAX) * 100);
//		screen.SetProgressBar(0, perc);
	}

}

/**
  * @brief C++ Initialization Function
  * @retval None
  */
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
	)
{

	Pin graphLE = Pin(GRAPH_LE_GPIO_Port, GRAPH_LE_Pin);
	Pin graphOE = Pin(GRAPH_OE_GPIO_Port, GRAPH_OE_Pin);

	currentADCHandle = in_hadc1;
	currentADCMemHandle = in_hdma_adc1;
	stripI2cHandle = in_hfmpi2c1;
	dmaTXStripHandle = in_hdma_fmpi2c1_tx;
	i2cHandle = in_hi2c1;
	audioHandle = in_hi2s3;
	dmaRXAudioHandle = in_hdma_spi3_rx;
	rtcHandle = in_hrtc;
	sdHandle = in_hsd;
	graphHandle = in_hspi4;
	pwm1Handle = in_htim1;
	pwm2Handle = in_htim2;
	pwm3Handle = in_htim3;
	screenHandle = in_huart1;
	midiHandle = in_huart2;
	dmxHandle = in_huart3;

//	screen.Startup(screenHandle);
	shiftReg = ShiftRegs(graphHandle, graphOE, graphLE);

	shiftReg.Init();
}

void InitTest()
{
	shiftReg.IndicatorTest();
}

/**
  * @brief C++ Main Loop Function
  * @retval None
  */
void Main()
{
	__HAL_TIM_SET_COMPARE(pwm2Handle, TIM_CHANNEL_1, 0);
	HAL_Delay(500);
	__HAL_TIM_SET_COMPARE(pwm2Handle, TIM_CHANNEL_1, UINT32_MAX / 2);
	HAL_Delay(500);
//		OLD Testing
//	__HAL_TIM_SET_COMPARE(pwm3Handle, TIM_CHANNEL_2, 10000);
//
//	HAL_Delay(50);
//	screen.SetProgressBar(0, count);
//	__HAL_TIM_SET_COMPARE(pwm3Handle, TIM_CHANNEL_2, 20000);
//	screen.SetNumber(0, count);
//	__HAL_TIM_SET_COMPARE(pwm3Handle, TIM_CHANNEL_2, 30000);
//	HAL_Delay(50);
////	screen.SetPage(1);
//	__HAL_TIM_SET_COMPARE(pwm3Handle, TIM_CHANNEL_2, 40000);
////	for (size_t i = 0; i < 50; ++i)
////	{
////		uint8_t val = (uint8_t)round(sin(i) * 40 + 127);
////		screen.UpdateGraph(1, 0, val);
////		screen.SetNumber(0, val);
////	}
//	HAL_Delay(100);
//	__HAL_TIM_SET_COMPARE(pwm3Handle, TIM_CHANNEL_2, 50000);
////	HAL_Delay(250);
////	screen.HomePage();
//	__HAL_TIM_SET_COMPARE(pwm3Handle, TIM_CHANNEL_2, 60000);
//	count++;
//	if (count > 100)
//	{
//		count = 0;
//	}

//	static GPIO_PinState menuLeft = HAL_GPIO_ReadPin(MENU_LEFT_GPIO_Port, MENU_LEFT_Pin);
//	if (menuLeft != menuLeftPrev)
//	{
//		if (menuLeft == GPIO_PIN_SET)
//		{
//			shiftReg.SetValue(ON, MENU_LEFT_IND);
//		}
//		else
//		{
//			shiftReg.SetValue(OFF, MENU_LEFT_IND);
//		}
//	}
//	menuLeftPrev = menuLeft;

//		Screen Nav Testing

//
//	ReadCurrent();
//	shiftReg.Update();
}

void MenuUpInterruptCallback()
{
	shiftReg.ToggleValue(MENU_UP_IND);
}
void MenuDownInterruptCallback()
{
	shiftReg.ToggleValue(MENU_DOWN_IND);
}
// Pin moved for next revision. Right now the pin is set as GPIO.
// Shares the same interrupt channel as the ENC1_A pin.
//void MenuLeftInterruptCallback()
//{
//
//}
void MenuRightInterruptCallback()
{
	shiftReg.ToggleValue(MENU_RIGHT_IND);
}
void MenuActInterruptCallback()
{
	shiftReg.ToggleValue(8);
}
void MenuBackInterruptCallback()
{
	relayState = relayState == GPIO_PIN_SET ? GPIO_PIN_RESET : GPIO_PIN_SET;
	HAL_GPIO_WritePin(STRIP_PWR_GPIO_Port, STRIP_PWR_Pin, relayState);
	shiftReg.SetValue((uint8_t)relayState, MENU_BACK_IND);
}
void Enc1SwInterruptCallback()
{
	shiftReg.ToggleValue(6);
}
void Enc2SwInterruptCallback()
{
	shiftReg.ToggleValue(7);
}
void Enc1TurnInterruptCallback()
{
	// Need to move to an "Encoder" class.
//	static GPIO_PinState enc1b = HAL_GPIO_ReadPin(ENC1_B_GPIO_Port, ENC1_B_Pin);
//	if (enc1b == GPIO_PIN_SET)
//	{
//
//	}
}
void Enc2TurnInterruptCallback()
{
	// Need to move to an "Encoder" class.
//	static GPIO_PinState enc2b = HAL_GPIO_ReadPin(ENC2_B_GPIO_Port, ENC2_B_Pin);
}
