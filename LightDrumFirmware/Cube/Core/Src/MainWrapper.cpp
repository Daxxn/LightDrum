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
#include "PCA9634.h"
#include "StripControl.h"
#include "Screen/Button.h"
#include "Screen/PageButton.h"
#include "Screen/Page.h"
#include "Screen/ProgressBar.h"
#include "ScreenControl.h"
#include "RotaryEncoder.h"

#define AUDIO_BUFFER_SIZE 128
#define AUDIO_HALF_BUFFER_SIZE 64
#define TEST_OFFSET -32000

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
Nextion next = Nextion();

StripCurrent stripCurr;
StripControl stripCtrl;

PCA9634 ledA;

uint8_t ledCount = 0;

uint8_t count = 0;
uint8_t page = 0;

PCA9634Settings settings;

uint32_t audioBuffer[AUDIO_BUFFER_SIZE];

bool indicator = false;

GPIO_PinState menuLeftPrev = GPIO_PIN_RESET;

GPIO_PinState relayState = GPIO_PIN_RESET;
uint32_t adcReading = 0;

RotaryEncoder encoder1;
RotaryEncoder encoder2;

/* Screen Components ---------------------------------------------------------*/
ScreenControl screenCtrl;

void ScreenChangeCallback(uint8_t pageID)
{
	screenCtrl.ChangePage(pageID);
}

// Global
PageButton homeBtn = PageButton(&next, 1, "pb1", 0, 0, 1, ScreenChangeCallback);
PageButton settingsBtn = PageButton(&next, 2, "pb5", 1, 0, 5, ScreenChangeCallback);

PageButton subMenuPageBtns[] = {
		homeBtn,
		settingsBtn
};

// MainMenu
PageButton mainPageBtn   = PageButton(&next, 7, "pb1", 0, 0, 2, ScreenChangeCallback);
PageButton chnPageBtn    = PageButton(&next, 1, "pb2", 0, 1, 3, ScreenChangeCallback);
PageButton chCfgPageBtn  = PageButton(&next, 6, "pb3", 0, 2, 4, ScreenChangeCallback);
PageButton audPageBtn    = PageButton(&next, 4, "pb5", 0, 3, 6, ScreenChangeCallback);
PageButton patPageBtn    = PageButton(&next, 5, "pb7", 1, 1, 8, ScreenChangeCallback);
PageButton colPageBtn    = PageButton(&next, 8, "pb6", 1, 2, 7, ScreenChangeCallback);
PageButton settPageBtn   = PageButton(&next, 2, "pb4", 1, 3, 5, ScreenChangeCallback);

PageButton mainBtns[] = {
		mainPageBtn,
		chnPageBtn,
		chCfgPageBtn,
		audPageBtn,
		patPageBtn,
		colPageBtn,
		settPageBtn
};

Page homePage = Page(&next, 1, NULL, 0, mainBtns, 7);

// Run

Button runBtn = Button(&next, 2, "b0", 0, 1);

Button runBtns[] = {
		runBtn
};

PageButton runHomeBtn = PageButton(&next, 2, "pb1", 0, 0, 1, ScreenChangeCallback);
PageButton runSettingsBtn = PageButton(&next, 3, "pb5", 1, 0, 5, ScreenChangeCallback);

PageButton runPageBtns[] = {
		runHomeBtn,
		runSettingsBtn
};

Page runPage = Page(&next, 2, runBtns, 1, runPageBtns, 2);

//Channel Vis
Button srcCh1Btn = Button(&next, 3, "b0", 0, 1);
Button srcCh2Btn = Button(&next, 21, "b1", 1, 1);
Button srcCh3Btn = Button(&next, 22, "b2", 2, 1);
Button srcCh4Btn = Button(&next, 23, "b3", 3, 1);
Button srcCh5Btn = Button(&next, 24, "b4", 4, 1);
Button srcCh6Btn = Button(&next, 25, "b5", 5, 1);
Button srcCh7Btn = Button(&next, 26, "b6", 6, 1);
Button srcCh8Btn = Button(&next, 27, "b7", 7, 1);

ProgressBar ch1Bar = ProgressBar(&next, 1, "j0");
ProgressBar ch2Bar = ProgressBar(&next, 4, "j1");
ProgressBar ch3Bar = ProgressBar(&next, 6, "j2");
ProgressBar ch4Bar = ProgressBar(&next, 8, "j3");
ProgressBar ch5Bar = ProgressBar(&next, 10, "j4");
ProgressBar ch6Bar = ProgressBar(&next, 12, "j5");
ProgressBar ch7Bar = ProgressBar(&next, 14, "j6");
ProgressBar ch8Bar = ProgressBar(&next, 16, "j7");

PageButton chVisHomeBtn = PageButton(&next, 18, "pb1", 0, 0, 1, ScreenChangeCallback);
PageButton chVisSettingsBtn = PageButton(&next, 19, "pb5", 1, 0, 5, ScreenChangeCallback);

PageButton chVisPageBtns[] = {
		chVisHomeBtn,
		chVisSettingsBtn
};

Button chVisBtns[] = {
		srcCh1Btn,
		srcCh2Btn,
		srcCh3Btn,
		srcCh4Btn,
		srcCh5Btn,
		srcCh6Btn,
		srcCh7Btn,
		srcCh8Btn
};

ProgressBar progBars[] = {
		ch1Bar,
		ch2Bar,
		ch3Bar,
		ch4Bar,
		ch5Bar,
		ch6Bar,
		ch7Bar,
		ch8Bar,
};

Page channelVisPage = Page(&next, 3, chVisBtns, 8, chVisPageBtns, 2, progBars, 8);

// Channel Config
Button ch1Btn = Button(&next, 13, "b0", 0, 2);
Button ch2Btn = Button(&next, 13, "b1", 1, 2);
Button ch3Btn = Button(&next, 13, "b2", 2, 2);
Button ch4Btn = Button(&next, 13, "b3", 3, 2);
Button ch5Btn = Button(&next, 13, "b4", 4, 2);
Button ch6Btn = Button(&next, 13, "b5", 5, 2);
Button ch7Btn = Button(&next, 13, "b6", 6, 2);
Button ch8Btn = Button(&next, 13, "b7", 7, 2);

PageButton chCfgHomeBtn = PageButton(&next, 3, "pb1", 0, 0, 1, ScreenChangeCallback);
PageButton chCfgSettingsBtn = PageButton(&next, 4, "pb5", 1, 0, 5, ScreenChangeCallback);

PageButton chCfgPageBtns[] = {
		chCfgHomeBtn,
		chCfgSettingsBtn
};

Button chCfgBtns[] = {
		ch1Btn,
		ch2Btn,
		ch3Btn,
		ch4Btn,
		ch5Btn,
		ch6Btn,
		ch7Btn,
		ch8Btn,
};

Page channelConfigPage = Page(&next, 4, chCfgBtns, 8, chCfgPageBtns, 2);

//Settings
Button saveBtn = Button(&next, 0, "b0", 0, 2);

Button settBtns[] = {
		saveBtn
};

PageButton settPageBtns[] = {
		homeBtn
};

Page settingsPage = Page(&next, 5, settBtns, 1, settPageBtns, 1);

// Audio
Button audSrcXlrBtn = Button(&next, 12, "b7", 2, 1);
Button audSrcJackBtn = Button(&next, 13, "b0", 3, 1);

PageButton audHomeBtn = PageButton(&next, 15, "pb1", 0, 0, 1, ScreenChangeCallback);
PageButton audSettingsBtn = PageButton(&next, 16, "pb5", 1, 0, 5, ScreenChangeCallback);

PageButton audPageBtns[] = {
		audHomeBtn,
		audSettingsBtn
};

Button audBtns[] = {
		audSrcXlrBtn,
		audSrcJackBtn
};

Page audioPage = Page(&next, 6, audBtns, 2, audPageBtns, 2);

// Colors
Button colChSelBtn = Button(&next, 0, "b0", 0, 2);
Button colorBtns[] = {
		colChSelBtn
};

PageButton colHomeBtn = PageButton(&next, 5, "pb1", 0, 0, 1, ScreenChangeCallback);
PageButton colSettingsBtn = PageButton(&next, 6, "pb5", 1, 0, 5, ScreenChangeCallback);

PageButton colPageBtns[] = {
		colHomeBtn,
		colSettingsBtn
};

Page colorPage = Page(&next, 7, colorBtns, 0, colPageBtns, 2);

// Pattern

//Button patternBtns[] = {};

PageButton patHomeBtn = PageButton(&next, 4, "pb1", 0, 0, 1, ScreenChangeCallback);
PageButton patSettingsBtn = PageButton(&next, 5, "pb5", 1, 0, 5, ScreenChangeCallback);

PageButton patPageBtns[] = {
		patHomeBtn,
		patSettingsBtn
};

Page patternPage = Page(&next, 7, NULL, 0, patPageBtns, 2);

// Screen Control
Page pages[] = {
		homePage,
		runPage,
		channelVisPage,
		channelConfigPage,
		settingsPage,
		audioPage,
		colorPage
};

#define NAV_BACKLIGHT  0
#define MENU_BACK_IND  1
#define MENU_DOWN_IND  2
#define MENU_UP_IND    3
#define MENU_LEFT_IND  4
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
//	double sum = 0;
//	double average = 0;
//	for (int i = 0; i < AUDIO_BUFFER_SIZE; ++i) {
//		sum += audioBuffer[i];
//	}
//	average = sum / 64;
}

void ReadAudioTest()
{
//	if (HAL_I2S_Receive(audioHandle, audioBuffer, AUDIO_BUFFER_SIZE, 200) == HAL_OK)
//	{
//		AudioLevelsAverage();
//	}
}

float rms = 0;
float sum = 0;
int rmsI = 0;
void RMSTest()
{
	sum = 0;
	for (rmsI = 0; rmsI < AUDIO_HALF_BUFFER_SIZE; rmsI += 2) {
		sum += pow(audioBuffer[rmsI], 2);
	}
	rms = sqrt(1.0 / (float)AUDIO_HALF_BUFFER_SIZE * sum) + TEST_OFFSET;

	__HAL_TIM_SET_COMPARE(pwm3Handle, TIM_CHANNEL_4, (uint32_t)rms);
}

void AudioFullCallback()
{
	RMSTest();
//	AudioLevelsAverage();
//	double max = 0;
//	for (int i = 0; i < AUDIO_HALF_BUFFER_SIZE; ++i) {
//		if (max < audioBuffer[i])
//		{
//			max += audioBuffer[i];
//		}
//	}
//	uint32_t avg = max / AUDIO_BUFFER_SIZE;
//	__HAL_TIM_SET_COMPARE(pwm3Handle, TIM_CHANNEL_4, avg);
}

void AudioHalfFullCallback()
{

}

void CurrentConvFullCallback()
{
	stripCurr.Calc();
}

void PageChangeCallbackHandle(uint8_t pageNumber)
{
	screenCtrl.ChangePageEvent(pageNumber);
}

void TouchEventCallbackHandle(uint8_t pageID, uint8_t compID, uint8_t event)
{
	screenCtrl.TouchEvent(pageID, compID, event);
}

void ScreenReceiveCallback()
{
	next.Receive();
}

void StripCurrentAlertCallback(StripCurrentStatus status)
{

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
	HAL_TIM_PWM_Start(in_htim3, TIM_CHANNEL_4);
	__HAL_TIM_SET_COMPARE(in_htim3, TIM_CHANNEL_4, UINT16_HALF);

	Pin graphLE = Pin(GRAPH_LE_GPIO_Port, GRAPH_LE_Pin);
	Pin graphOE = Pin(GRAPH_OE_GPIO_Port, GRAPH_OE_Pin);
	Pin pwmOE = Pin(PWM_OE_GPIO_Port, PWM_OE_Pin, ACTIVE_LOW);

	Pin enc1Sw = Pin(ENC1_SW_GPIO_Port, ENC1_SW_Pin, ACTIVE_LOW);
	Pin enc2Sw = Pin(ENC2_SW_GPIO_Port, ENC2_SW_Pin, ACTIVE_LOW);

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


	encoder1 = RotaryEncoder(ENC1_A_GPIO_Port, ENC1_A_Pin, ENC1_B_GPIO_Port, ENC1_B_Pin, enc1Sw);
	encoder2 = RotaryEncoder(ENC2_A_GPIO_Port, ENC2_A_Pin, ENC2_B_GPIO_Port, ENC2_B_Pin, enc2Sw);

	encoder1.Init();
	encoder2.Init();

	shiftReg = ShiftRegs(graphHandle, graphOE, graphLE);
	stripCurr = StripCurrent(currentADCHandle, adcTimHandle, StripCurrentAlertCallback);
	stripCtrl = StripControl(&stripCurr);
	ledA = PCA9634(0x2A, stripI2cHandle, pwmOE);

	HAL_TIM_PWM_Start(pwm1Handle, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(pwm1Handle, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(pwm3Handle, TIM_CHANNEL_1);


//	HAL_GPIO_WritePin(GRAPH_LE_GPIO_Port, GRAPH_LE_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GRAPH_OE_GPIO_Port, GRAPH_OE_Pin, GPIO_PIN_SET);

	settings = PCA9634Settings();
	settings.Driver = PCA9634_OUTPUT_DRIVER::TOTEM_POLE;
	settings.Invert = PCA9634_OUTPUT_LOGIC::INVERTED;
	ledA.ChangeSettings(settings);

	shiftReg.Init();

	if (stripCurr.Init() != HAL_OK)
	{
		return HAL_ERROR;
	}

	stripCtrl.Init();

	NextionCallbacks callbacks = NextionCallbacks();
	callbacks.PageChange = PageChangeCallbackHandle;
	callbacks.TouchEvent = TouchEventCallbackHandle;

	next.Startup(screenHandle, callbacks);
	screenCtrl.Init(&next, pages);
	screenCtrl.HomePage();

	stripCtrl.Power(GPIO_PIN_SET);

//	HAL_I2S_Receive_DMA(audioHandle, (uint16_t*)audioBuffer, AUDIO_BUFFER_SIZE);

	__HAL_TIM_SET_COMPARE(pwm3Handle, TIM_CHANNEL_4, 0);
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
	__HAL_TIM_SET_COMPARE(pwm1Handle, TIM_CHANNEL_1, indicator ? UINT16_MAX / 2 : 0);
	__HAL_TIM_SET_COMPARE(pwm1Handle, TIM_CHANNEL_3, !indicator ? UINT16_MAX : 0);

//	stripCtrl.Check();
//
//	if (screenCtrl.CheckPage(1))
//	{
//		screenCtrl.ChangeText("t1", indicator ? AUDIO_SRC_BTN_XLR : AUDIO_SRC_BTN_JACK, 4);
//	}
//	else
//	{
//		screenCtrl.ChangeText("b0", indicator ? AUDIO_SRC_BTN_XLR : AUDIO_SRC_BTN_JACK, 4);
//	}
//
//	stripCtrl.Power(indicator ? GPIO_PIN_SET : GPIO_PIN_RESET);
//	HAL_Delay(500);
//	stripCtrl.Check();
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

//	next.CheckForTouchEvents();
}

void MenuUpInterruptCallback()
{
//	shiftReg.ToggleValue(MENU_UP_IND);
	screenCtrl.NavigateVert(-1);
}
void MenuDownInterruptCallback()
{
//	shiftReg.ToggleValue(MENU_DOWN_IND);
	screenCtrl.NavigateVert(1);
}
void MenuLeftInterruptCallback()
{
	screenCtrl.NavigateHorz(-1);
}
void MenuRightInterruptCallback()
{
//	shiftReg.ToggleValue(MENU_RIGHT_IND);
	screenCtrl.NavigateHorz(1);
}
void MenuActInterruptCallback()
{
	shiftReg.ToggleValue(8);
	screenCtrl.Act();
}
void MenuBackInterruptCallback()
{
	screenCtrl.HomePage();
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
	encoder1.Decode();
	// Need to move to an "Encoder" class.
//	static GPIO_PinState enc1b = HAL_GPIO_ReadPin(ENC1_B_GPIO_Port, ENC1_B_Pin);
//	if (enc1b == GPIO_PIN_SET)
//	{
//
//	}
}
void Enc2TurnInterruptCallback()
{
	encoder2.Decode();
	// Need to move to an "Encoder" class.
//	static GPIO_PinState enc2b = HAL_GPIO_ReadPin(ENC2_B_GPIO_Port, ENC2_B_Pin);
}
