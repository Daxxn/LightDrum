#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "LCDScreen2.h"
#include "Button.h"
#include "MenuController.h"
#include "Menu.h"
#include "MenuData.h"
#include "Logger.h"
#include "STP16Driver.h"
#include "LightDrumPinout.h"
#include "PCA9634.h"
#include "CurrentSense.h"

using namespace Digitl;

#pragma region Constants
const float senseResistance = 0.06;
const int senseGain = 100;
#pragma endregion

#pragma region LCD Pins
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
PCA9634 pwm0(&Wire, Ser::I2C::PWM0_ADDR, Ser::I2C::PWM_OE, true);
PCA9634 pwm1(&Wire, Ser::I2C::PWM1_ADDR, Ser::I2C::PWM_OE, true);
PCA9634 pwm2(&Wire, Ser::I2C::PWM2_ADDR, Ser::I2C::PWM_OE, true);

CurrentSense currentMonitors[8] = 
{
  CurrentSense(Anlg::CURR_SENSEPins::S0_PIN, senseResistance, senseGain),
  CurrentSense(Anlg::CURR_SENSEPins::S1_PIN, senseResistance, senseGain),
  CurrentSense(Anlg::CURR_SENSEPins::S2_PIN, senseResistance, senseGain),
  CurrentSense(Anlg::CURR_SENSEPins::S3_PIN, senseResistance, senseGain),
  CurrentSense(Anlg::CURR_SENSEPins::S4_PIN, senseResistance, senseGain),
  CurrentSense(Anlg::CURR_SENSEPins::S5_PIN, senseResistance, senseGain),
  CurrentSense(Anlg::CURR_SENSEPins::S6_PIN, senseResistance, senseGain),
  CurrentSense(Anlg::CURR_SENSEPins::S7_PIN, senseResistance, senseGain)
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
  // pwm0.Update();
  // pwm0.ReadSettings();
  // pwm1.ReadSettings();
  pwm1.Update();
  // pwm2.Update();
}
#pragma endregion

// byte val = 0;

#pragma region System Test Functions
void IndicatorTest()
{
  digitalWrite(INDICATORPins::ACT_PIN, HIGH);
  digitalWrite(INDICATORPins::HOME_PIN, HIGH);
  digitalWrite(INDICATORPins::M_DOWN_PIN, HIGH);
  digitalWrite(INDICATORPins::M_UP_PIN, HIGH);
  digitalWrite(INDICATORPins::MODE_PIN, HIGH);
  delay(1000);
  digitalWrite(INDICATORPins::ACT_PIN, LOW);
  digitalWrite(INDICATORPins::HOME_PIN, LOW);
  digitalWrite(INDICATORPins::M_DOWN_PIN, LOW);
  digitalWrite(INDICATORPins::MODE_PIN, LOW);
  digitalWrite(INDICATORPins::M_UP_PIN, LOW);
}

void RelayTest()
{
  digitalWrite(POWERPins::RELAY_PIN, HIGH);
  // delay(1000);
  // digitalWrite(POWERPins::RELAY_PIN, LOW);
  // delay(1000);
}
#pragma endregion

void setup() {
  delay(100);

  Wire.begin();
  SPI.begin();

  // pwm0.Begin();
  pwm1.Begin();

  // pwm0.ToggleMode(PCAEnums::OpMode::NORM);
  // pwm0.ToggleEnable(true);
  pwm1.ToggleEnable(true);

  pinMode(INDICATORPins::ACT_PIN, OUTPUT);
  pinMode(INDICATORPins::HOME_PIN, OUTPUT);
  pinMode(INDICATORPins::M_DOWN_PIN, OUTPUT);
  pinMode(INDICATORPins::M_UP_PIN, OUTPUT);
  pinMode(INDICATORPins::MODE_PIN, OUTPUT);

  pinMode(POWERPins::RELAY_PIN, OUTPUT);

  // for (auto &&c : currentMonitors)
  // {
  //   c.Begin();
  // }

  Logger::Log("Starting LCD Test Mode");
  // Serial.println("Starting LCD Test Mode");

  upBtn   = Button(BUTTONSPins::M_UP_PIN, [] () { menu.Next(); });
  downBtn = Button(BUTTONSPins::M_DOWN_PIN, [] () { menu.Prev(); });
  homeBtn = Button(BUTTONSPins::HOME_PIN, [] () { menu.Home(); });
  ActBtn = Button(BUTTONSPins::ACT_PIN, [] () { menu.Act(); });
  ModeBtn = Button(BUTTONSPins::MODE_PIN, [] () { // Blink Indicator
    digitalWrite(INDICATORPins::MODE_PIN, HIGH);
    delay(100);
    digitalWrite(INDICATORPins::MODE_PIN, LOW);
    delay(100);
    digitalWrite(INDICATORPins::MODE_PIN, HIGH);
    delay(100);
    digitalWrite(INDICATORPins::MODE_PIN, LOW);
    delay(100);
    digitalWrite(INDICATORPins::MODE_PIN, HIGH);
    delay(100);
    digitalWrite(INDICATORPins::MODE_PIN, LOW);
    delay(100);
    digitalWrite(INDICATORPins::MODE_PIN, HIGH);
  });

  Logger::Log("Button INIT Complete");
  // Serial.println("Button INIT Complete");

  root.SetNext(&m2);
  m2.SetNext(&m3);
  m3.SetNext(&root);


  Logger::Log("Menu Set Complete");
  // Serial.println("Menu Set Complete");

  menu.Begin(&root);
  // lcd.Begin();

  Logger::Log("Menu INIT Complete");
  // Serial.println("Menu INIT Complete");

  IndicatorTest();
  digitalWrite(POWERPins::RELAY_PIN, HIGH);
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
  flip = !flip;
  if (flip)
  {
    pwm1.SetStates(firstState, 8);
  }
  else
  {
    pwm1.SetStates(secondState, 8);
  }
  
  #pragma endregion

  // IndicatorTest();
  // RelayTest();
  // count++;
  #pragma endregion
  UpdateButtons();
  UpdatePWM();
  delay(500);
}