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
#include "PCA9634.h"

#define AUDIO_BUFFER_SIZE 128
#define AUDIO_HALF_BUFFER_SIZE 64

ADC_HandleTypeDef *currentADCHandle;
DMA_HandleTypeDef *currentADC_DMAHandle;

FMPI2C_HandleTypeDef *stripI2cHandle;
DMA_HandleTypeDef *dmaTXStripHandle;
I2C_HandleTypeDef *i2cHandle;

I2S_HandleTypeDef *audioHandle;
DMA_HandleTypeDef *dmaRXAudioHandle;

SPI_HandleTypeDef *graphHandle;

TIM_HandleTypeDef *pwm1Handle;
TIM_HandleTypeDef *pwm2Handle;
TIM_HandleTypeDef *pwm3Handle;
TIM_HandleTypeDef *pwm6Handle;
TIM_HandleTypeDef *adcTimHandle;

UART_HandleTypeDef *screenHandle;
UART_HandleTypeDef *midiHandle;
UART_HandleTypeDef *dmxHandle;

RTC_HandleTypeDef *rtcHandle;
SD_HandleTypeDef *sdHandle;

ShiftRegs shiftReg;
Nextion screen = Nextion();

Button menuUp = Button();
Button menuDown = Button();

StripCurrent stripCurr;

PCA9634 ledA;

uint8_t ledCount = 0;

uint8_t count = 0;
uint8_t page = 0;

PCA9634Settings settings;

uint16_t audioBuffer[AUDIO_BUFFER_SIZE];

bool indicator = false;

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

void AudioLevelsAverage()
{
	double sum = 0;
	double average = 0;
	for (int i = 0; i < AUDIO_BUFFER_SIZE; ++i) {
		sum += audioBuffer[i];
	}
	average = sum / 64;
}

void ReadAudioTest()
{
	if (HAL_I2S_Receive(audioHandle, audioBuffer, AUDIO_BUFFER_SIZE, 200) == HAL_OK)
	{
		AudioLevelsAverage();
	}
}

void AudioFullCallback()
{
	AudioLevelsAverage();
}

void AudioHalfFullCallback()
{

}

void CurrentConvFullCallback()
{
	stripCurr.Calc();
}

/**
  * @brief C++ Initialization Function
  * @retval None
  */
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
	)
{

	Pin graphLE = Pin(GRAPH_LE_GPIO_Port, GRAPH_LE_Pin);
	Pin graphOE = Pin(GRAPH_OE_GPIO_Port, GRAPH_OE_Pin);
	Pin pwmOE = Pin(PWM_OE_GPIO_Port, PWM_OE_Pin, GPIO_Default_State::ACTIVE_LOW);

	currentADCHandle = in_hadc1;
	currentADC_DMAHandle = in_hdma_adc1;

	stripI2cHandle = in_hfmpi2c1;
	dmaTXStripHandle = in_hdma_fmpi2c1_tx;

	i2cHandle = in_hi2c1;

	audioHandle = in_hi2s5;
	dmaRXAudioHandle = hdma_spi5_rx;

	rtcHandle = in_hrtc;
	sdHandle = in_hsd;
	graphHandle = in_hspi4;
	pwm1Handle = in_htim1;
	pwm3Handle = in_htim3;
	adcTimHandle = in_htim8;
	screenHandle = in_huart1;
	midiHandle = in_huart2;
	dmxHandle = in_huart3;

//	screen.Startup(screenHandle);
	shiftReg = ShiftRegs(graphHandle, graphOE, graphLE);
	stripCurr = StripCurrent(currentADCHandle, adcTimHandle);
	ledA = PCA9634(0x2A, stripI2cHandle, pwmOE);

	HAL_TIM_PWM_Start(pwm1Handle, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(pwm1Handle, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(pwm3Handle, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(pwm3Handle, TIM_CHANNEL_4);

//	HAL_TIM_Base_Start(adcTimHandle);

	HAL_GPIO_WritePin(GRAPH_LE_GPIO_Port, GRAPH_LE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GRAPH_OE_GPIO_Port, GRAPH_OE_Pin, GPIO_PIN_SET);

	settings = PCA9634Settings();
	settings.Driver = PCA9634_OUTPUT_DRIVER::TOTEM_POLE;
	settings.Invert = PCA9634_OUTPUT_LOGIC::INVERTED;
	ledA.ChangeSettings(settings);

	shiftReg.Init();

	if (stripCurr.Init() != HAL_OK)
	{
		return HAL_ERROR;
	}

//	if (HAL_I2S_Receive_DMA(audioHandle, audioBuffer, AUDIO_BUFFER_SIZE) != HAL_OK)
//	{
//		return HAL_ERROR;
//	}

	return HAL_OK;
}

void InitTest()
{
//	shiftReg.IndicatorTest();
}

/**
  * @brief C++ Main Loop Function
  * @retval None
  */
void Main()
{
	indicator = !indicator;
	__HAL_TIM_SET_COMPARE(pwm1Handle, TIM_CHANNEL_1, indicator ? UINT16_MAX : 0);
	__HAL_TIM_SET_COMPARE(pwm1Handle, TIM_CHANNEL_3, !indicator ? UINT16_MAX : 0);
//	ReadCurrent();
//	ReadAudioTest();
//	PCA9634Settings settings = ledA.ReadSettings();


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
