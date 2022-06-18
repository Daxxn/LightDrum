#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "LCDScreen2.h"
#include "Button.h"
#include "MenuController.h"
#include "Menu.h"
#include "MenuData.h"
#include "STP16Driver.h"
#include "LightDrumPinout.h"
#include "PCA9634.h"
#include "CurrentSense.h"

using namespace Digitl;

#pragma region Constants
const float senseResistance = 0.06;
const int senseGain = 100;
#pragma endregion

#pragma region LCD Screen Pins
int dataPins[8] = {
  LCDPins::D0_PIN,
  LCDPins::D1_PIN,
  LCDPins::D2_PIN,
  LCDPins::D3_PIN,
  LCDPins::D4_PIN,
  LCDPins::D5_PIN,
  LCDPins::D6_PIN,
  LCDPins::D7_PIN,
};
int enPin = LCDPins::EN_PIN;
int rsPin = LCDPins::RS_PIN;
int rwPin = LCDPins::RW_PIN;
#pragma endregion

#pragma region Class Definitions
PCA9634 pwm0(&Wire, Ser::I2C::LED1_ADDR, Digitl::LEDPins::PWM_OE_PIN, true);
PCA9634 pwm1(&Wire, Ser::I2C::LED2_ADDR, Digitl::LEDPins::PWM_OE_PIN, true);
PCA9634 pwm2(&Wire, Ser::I2C::LED3_ADDR, Digitl::LEDPins::PWM_OE_PIN, true);

CurrentSense currentMonitors[8] = 
{
  CurrentSense(Anlg::CURRPins::SNS_1_PIN, senseResistance, senseGain),
  CurrentSense(Anlg::CURRPins::SNS_2_PIN, senseResistance, senseGain),
  CurrentSense(Anlg::CURRPins::SNS_3_PIN, senseResistance, senseGain),
  CurrentSense(Anlg::CURRPins::SNS_4_PIN, senseResistance, senseGain),
  CurrentSense(Anlg::CURRPins::SNS_5_PIN, senseResistance, senseGain),
  CurrentSense(Anlg::CURRPins::SNS_6_PIN, senseResistance, senseGain),
  CurrentSense(Anlg::CURRPins::SNS_7_PIN, senseResistance, senseGain),
  CurrentSense(Anlg::CURRPins::SNS_8_PIN, senseResistance, senseGain)
};

LCDScreen2 lcd(dataPins, rsPin, rwPin, enPin);
MenuController menu(&lcd);
STP16Driver leds(
  LEDPins::SDI_PIN,
  LEDPins::CLK_PIN,
  LEDPins::LE_PIN,
  LEDPins::OE_PIN
);

Menu root(MenuData::MenuOne);
Menu m2(MenuData::MenuTwo);
Menu m3(MenuData::MenuThree);

Button upBtn;
Button downBtn;
Button homeBtn;
Button ActBtn;
Button ModeBtn;
#pragma endregion

#pragma region Loose Variables
byte count = 0;
bool flip = false;

uint8_t firstState[8] = {
  200,0,200,0,
  200,0,200,0
};
uint8_t secondState[8] = {
  0,200,0,200,
  0,200,0,200
};
#pragma endregion

#pragma region Button Handlers
void UpdateButtons() {
  upBtn.Update();
  downBtn.Update();
  homeBtn.Update();
  ModeBtn.Update();
  ActBtn.Update();
}

void UpdatePWM()
{
  pwm0.Update();
  // pwm0.ReadSettings();
  // pwm1.ReadSettings();
  // pwm1.Update();
  // pwm2.Update();
}
#pragma endregion

// byte val = 0;

#pragma region System Test Functions
void IndicatorTest()
{
  digitalWrite(INDPins::ACT_PIN, HIGH);
  digitalWrite(INDPins::HOME_PIN, HIGH);
  digitalWrite(INDPins::M_DN_PIN, HIGH);
  digitalWrite(INDPins::M_UP_PIN, HIGH);
  digitalWrite(INDPins::MODE_PIN, HIGH);
  delay(1000);
  digitalWrite(INDPins::ACT_PIN, LOW);
  digitalWrite(INDPins::HOME_PIN, LOW);
  digitalWrite(INDPins::M_DN_PIN, LOW);
  digitalWrite(INDPins::MODE_PIN, LOW);
  digitalWrite(INDPins::M_UP_PIN, LOW);
}

void RelayTest()
{
  digitalWrite(PWRPins::PWR_EN_PIN, HIGH);
  // delay(1000);
  // digitalWrite(POWERPins::RELAY_PIN, LOW);
  // delay(1000);
}
#pragma endregion

void setup() {
  #pragma region Power Init
  pinMode(PWRPins::PWR_EN_PIN, OUTPUT);
  pinMode(PWRPins::INV_EN_PIN, OUTPUT);

  digitalWrite(PWRPins::INV_EN_PIN, HIGH);
  digitalWrite(PWRPins::PWR_EN_PIN, LOW);
  #pragma endregion

  delay(100);

  Wire.begin();
  SPI.begin();

  #pragma region Init
  #pragma region PWM
  pwm0.Begin();
  // pwm1.Begin();

  delay(50);

  pwm0.ToggleMode(PCAEnums::OpMode::NORM);
  // pwm0.ToggleEnable(true);
  pwm0.ToggleEnable(true);
  // pwm1.ToggleEnable(true);

  pwm0.SetLEDOutput(PCAEnums::PWMState::PWM);

  pinMode(LEDPins::PWM_OE_PIN, OUTPUT);
  digitalWrite(LEDPins::PWM_OE_PIN, LOW);
  #pragma endregion

  #pragma region Inicator LEDs
  pinMode(INDPins::ACT_PIN, OUTPUT);
  pinMode(INDPins::HOME_PIN, OUTPUT);
  pinMode(INDPins::M_DN_PIN, OUTPUT);
  pinMode(INDPins::M_UP_PIN, OUTPUT);
  pinMode(INDPins::MODE_PIN, OUTPUT);
  #pragma endregion

  #pragma region Switches
  upBtn   = Button(SWITCHPins::M_UP_PIN, [] () { menu.Next(); });
  downBtn = Button(SWITCHPins::M_DN_PIN, [] () { menu.Prev(); });
  homeBtn = Button(SWITCHPins::HOME_PIN, [] () { menu.Home(); });
  ActBtn = Button(SWITCHPins::ACT_PIN, [] () { menu.Act(); });
  ModeBtn = Button(SWITCHPins::MODE_PIN, [] () { // Blink Indicator
    digitalWrite(SWITCHPins::MODE_PIN, HIGH);
    delay(100);
    digitalWrite(INDPins::MODE_PIN, LOW);
    delay(100);
    digitalWrite(INDPins::MODE_PIN, HIGH);
    delay(100);
    digitalWrite(INDPins::MODE_PIN, LOW);
    delay(100);
    digitalWrite(INDPins::MODE_PIN, HIGH);
    delay(100);
    digitalWrite(INDPins::MODE_PIN, LOW);
    delay(100);
    digitalWrite(INDPins::MODE_PIN, HIGH);
  });
  #pragma endregion

  #pragma region Menu
  root.SetNext(&m2);
  m2.SetNext(&m3);
  m3.SetNext(&root);

  menu.Begin(&root);
  // lcd.Begin();
  #pragma endregion
  #pragma endregion

  IndicatorTest();
  digitalWrite(PWRPins::PWR_EN_PIN, HIGH);
  delay(2000);
}

void loop() {
  #pragma region System Tests
  #pragma region Menu Test
  // menu.Update();
  // lcd.Test();
  #pragma endregion

  #pragma region PWM Tests
  // if (count == 0)
  // {
  //   pwm0.SetStates(firstState, 8);
  // }
  // else if(count == 127)
  // {
  //   pwm0.SetStates(secondState, 8);
  // }
  // flip = !flip;
  // if (flip)
  // {
  //   pwm0.SetStates(firstState, 8);
  //   // pwm1.SetStates(firstState, 8);
  // }
  // else
  // {
  //   pwm0.SetStates(secondState, 8);
  //   // pwm1.SetStates(secondState, 8);
  // }
  // pwm0.Test();
  pwm0.SetState(0, 1);
  
  #pragma endregion

  // IndicatorTest();
  RelayTest();
  // count++;
  #pragma endregion
  UpdateButtons();
  UpdatePWM();
  delay(500);
}