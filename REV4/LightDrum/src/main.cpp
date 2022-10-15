#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "LCDScreen2.h"
#include "Button.h"
#include "MenuController.h"
#include "Menu.h"
#include "MenuData.h"
#include "STP16Driver.h"
#include "LightDrumPinoutREV5.h"
#include "PCA9634.h"
#include "CurrentSense.h"
#include "LEDString.h"
#include "ADC0838.h"

using namespace Digitl;

#pragma region Constants
namespace Constants
{
  const float senseResistance = 0.06;
  const int senseGain = 100;
} // namespace Constants

#pragma endregion

#pragma region LCD Screen Pins
int dataPins[8] = {
  ScreenPins::D0_PIN,
  ScreenPins::D1_PIN,
  ScreenPins::D2_PIN,
  ScreenPins::D3_PIN,
  ScreenPins::D4_PIN,
  ScreenPins::D5_PIN,
  ScreenPins::D6_PIN,
  ScreenPins::D7_PIN,
};
int enPin = ScreenPins::EN_PIN;
int rsPin = ScreenPins::RS_PIN;
int rwPin = ScreenPins::RW_PIN;
#pragma endregion

#pragma region Class Definitions
PCA9634 pwm0(
  &Wire,
  Ser::I2C::StripA_ADDR,
  Digitl::StripPins::OE_PIN
);
PCA9634 pwm1(
  &Wire,
  Ser::I2C::StripB_ADDR,
  Digitl::StripPins::OE_PIN
);
PCA9634 pwm2(
  &Wire,
  Ser::I2C::StripC_ADDR,
  Digitl::StripPins::OE_PIN
);

#pragma region LEDs
// LEDs red[8] = {
//   LEDs(1, 1), // 1
//   LEDs(2, 3), // 2
//   LEDs(2, 5), // 3
//   LEDs(3, 7), // 4
//   LEDs(1, 0), // 5
//   LEDs(2, 2), // 6
//   LEDs(2, 4), // 7
//   LEDs(3, 6), // 8
// };

// LEDs green[8] = {
//   LEDs(1, 3), // 1
//   LEDs(1, 5), // 2
//   LEDs(2, 7), // 3
//   LEDs(3, 1), // 4
//   LEDs(1, 2), // 5
//   LEDs(1, 4), // 6
//   LEDs(2, 6), // 7
//   LEDs(3, 0), // 8
// };

// LEDs blue[8] = {
//   LEDs(1, 7), // 1
//   LEDs(2, 1), // 2
//   LEDs(3, 3), // 3
//   LEDs(3, 5), // 4
//   LEDs(1, 6), // 5
//   LEDs(2, 0), // 6
//   LEDs(3, 2), // 7
//   LEDs(3, 4), // 8
// };
#pragma endregion

// LEDString ledPWM(&pwm0, &pwm1, &pwm2, red, green, blue, 8);

CurrentSense currentMonitors[8] = {
  CurrentSense(
    Anlg::CurrentPins::STRIP_1_PIN,
    Constants::senseResistance,
    Constants::senseGain
  ),
  CurrentSense(
    Anlg::CurrentPins::STRIP_2_PIN,
    Constants::senseResistance,
    Constants::senseGain
  ),
  CurrentSense(
    Anlg::CurrentPins::STRIP_3_PIN,
    Constants::senseResistance,
    Constants::senseGain
  ),
  CurrentSense(
    Anlg::CurrentPins::STRIP_4_PIN,
    Constants::senseResistance,
    Constants::senseGain
  ),
  CurrentSense(
    Anlg::CurrentPins::STRIP_5_PIN,
    Constants::senseResistance,
    Constants::senseGain
  ),
  CurrentSense(
    Anlg::CurrentPins::STRIP_6_PIN,
    Constants::senseResistance,
    Constants::senseGain
  ),
  CurrentSense(
    Anlg::CurrentPins::STRIP_7_PIN,
    Constants::senseResistance,
    Constants::senseGain
  ),
  CurrentSense(
    Anlg::CurrentPins::STRIP_8_PIN,
    Constants::senseResistance,
    Constants::senseGain
  )
};

LCDScreen2 lcd(dataPins, rsPin, rwPin, enPin);
MenuController menu(&lcd);

STP16Driver leds(
  GraphPins::SDI_PIN,
  GraphPins::CLK_PIN,
  GraphPins::LE_PIN,
  GraphPins::OE_PIN
);

Menu root(MenuData::MenuOne);
Menu m2(MenuData::MenuTwo);
Menu m3(MenuData::MenuThree);

Button UpBtn;
Button DownBtn;
Button HomeBtn;
Button ActBtn;
Button ModeBtn;

ADC0838 adc(
  Ser::SPI::ADC_ADDR,
  Digitl::ADCPins::STATUS_PIN,
  ADC0838Enums::Signal::SINGLE
);

#pragma endregion

#pragma region Loose Variables
byte count = 0;
bool flip = false;
byte indCount = 0;

uint8_t testLEDStates[8] = {
  32, 64, 96, 128, 160, 192, 224, 0
};

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
void UpdateButtons()
{
  UpBtn.Update();
  DownBtn.Update();
  HomeBtn.Update();
  ModeBtn.Update();
  ActBtn.Update();
}
#pragma endregion

// byte val = 0;

#pragma region System Test Functions
void IndicatorTest(int del, int pin)
{
  Serial.println("Debug Indicator Test");
  digitalWrite(pin, HIGH);
  delay(del);
  digitalWrite(pin, LOW);
  delay(del);
  digitalWrite(pin, HIGH);
  delay(del);
  digitalWrite(pin, LOW);
  delay(del);
  digitalWrite(pin, HIGH);
  delay(del);
  digitalWrite(pin, LOW);
  delay(del);
  digitalWrite(pin, HIGH);
  delay(del);
  digitalWrite(pin, LOW);
  delay(del);
  digitalWrite(pin, HIGH);
  delay(del);
  digitalWrite(pin, LOW);
  delay(del);
}

void RelayTest()
{
  digitalWrite(PowerPins::STRIP_EN_PIN, HIGH);
  delay(1000);
  digitalWrite(PowerPins::STRIP_EN_PIN, LOW);
  // delay(1000);
}

void DebugSignal(uint8_t value, int del)
{
  Serial.println("Debug Sig");
  digitalWrite(DiagPins::DEBUG_PIN, HIGH);
  delay(del * 2);
  digitalWrite(DiagPins::DEBUG_PIN, LOW);
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, bitRead(value, 7));
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, LOW);
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, bitRead(value, 6));
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, LOW);
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, bitRead(value, 5));
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, LOW);
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, bitRead(value, 4));
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, LOW);
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, bitRead(value, 3));
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, LOW);
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, bitRead(value, 2));
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, LOW);
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, bitRead(value, 1));
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, LOW);
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, bitRead(value, 0));
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, LOW);
  delay(del);
  digitalWrite(DiagPins::DEBUG_PIN, HIGH);
  delay(del * 2);
  digitalWrite(DiagPins::DEBUG_PIN, LOW);
}
#pragma endregion

#pragma region Update Functions
void UpdatePWM()
{
  pwm0.Update();
  pwm1.Update();
  pwm2.Update();

  // Testing
  // PWM0
  // delay(250);
  // pwm0.ReadSettings();
  // DebugSignal(pwm0.GetMode1Settings(), 10);
  // delay(250);
  // PWM1
  // delay(250);
  // pwm1.ReadSettings();
  // DebugSignal(pwm1.GetMode1Settings(), 10);
  // delay(250);
  // // PWM2
  // delay(250);
  // pwm2.ReadSettings();
  // DebugSignal(pwm2.GetMode1Settings(), 10);
  // delay(250);
}

void UpdateCurrentMonitors()
{
  for (auto &&cm : currentMonitors)
  {
    cm.Read();
  }
}
#pragma endregion

void setup() {
  #ifdef USB
  Serial.begin(115200);

  Serial.println("Startup");
  #endif


  #pragma region Power Init
  pinMode(PowerPins::STRIP_EN_PIN, OUTPUT);

  digitalWrite(PowerPins::STRIP_EN_PIN, LOW);
  #pragma endregion

  #pragma region Encoders
  pinMode(EncoderPins::A1_PIN, INPUT_PULLUP);
  // pinMode(EncoderPins::B1_PIN, INPUT_PULLUP);
  pinMode(EncoderPins::A2_PIN, INPUT_PULLUP);
  // pinMode(EncoderPins::B2_PIN, INPUT_PULLUP);
  pinMode(EncoderPins::SW1_PIN, INPUT_PULLUP);
  pinMode(EncoderPins::SW2_PIN, INPUT_PULLUP);
  #pragma endregion

  delay(100);

  Wire.begin();
  SPI.begin();

  #pragma region Init
  #pragma region PWM
  // Not sure if the address thing is fixed. Test later.
  pwm0.Begin(
    PCAEnums::Drive::TOTEM,
    PCAEnums::BlinkMode::DIMMING,
    PCAEnums::OutputEnMode::NORM
  );
  pwm1.Begin(
    PCAEnums::Drive::TOTEM,
    PCAEnums::BlinkMode::DIMMING,
    PCAEnums::OutputEnMode::NORM
  );
  pwm2.Begin(
    PCAEnums::Drive::TOTEM,
    PCAEnums::BlinkMode::DIMMING,
    PCAEnums::OutputEnMode::NORM
  );

  delay(50);

  pwm0.ToggleMode(PCAEnums::OpMode::NORM);
  pwm0.ToggleEnable(true);
  pwm1.ToggleEnable(true);
  pwm2.ToggleEnable(true);

  pwm0.SetLEDOutput(PCAEnums::PWMState::PWM);
  pwm1.SetLEDOutput(PCAEnums::PWMState::PWM);
  pwm2.SetLEDOutput(PCAEnums::PWMState::PWM);
  pwm0.SetGroupFrequency(250);
  pwm0.SetGroupPWM(127);
  pwm1.SetGroupPWM(127);
  pwm2.SetGroupPWM(127);
  // ledPWM.SetGlobalPWM(10);
  #pragma endregion

  #pragma region Inicator LEDs
  // pinMode(INDPins::ACT_PIN, OUTPUT);
  // pinMode(INDPins::HOME_PIN, OUTPUT);
  // pinMode(INDPins::M_DN_PIN, OUTPUT);
  // pinMode(INDPins::M_UP_PIN, OUTPUT);
  // pinMode(INDPins::MODE_PIN, OUTPUT);

  leds.Begin();
  leds.Enable(true);
  #pragma endregion

  #pragma region Switches
  // UpBtn   = Button(MenuPins::RIGHT_PIN, [] () { menu.Next(); });
  // DownBtn = Button(MenuPins::LEFT_PIN,  [] () { menu.Prev(); });
  // HomeBtn = Button(MenuPins::BACK_PIN,  [] () { menu.Home(); });
  // ActBtn  = Button(MenuPins::ACT_PIN,   [] () { menu.Act(); });
  // ModeBtn = Button(MenuPins::UP_PIN,    [] () { // Blink Indicator
  //   digitalWrite(DiagPins::STATUS_PIN, HIGH);
  //   delay(100);
  //   digitalWrite(DiagPins::STATUS_PIN, LOW);
  //   delay(100);
  //   digitalWrite(DiagPins::STATUS_PIN, HIGH);
  //   delay(100);
  //   digitalWrite(DiagPins::STATUS_PIN, LOW);
  //   delay(100);
  //   digitalWrite(DiagPins::STATUS_PIN, HIGH);
  //   delay(100);
  //   digitalWrite(DiagPins::STATUS_PIN, LOW);
  //   delay(100);
  //   digitalWrite(DiagPins::STATUS_PIN, HIGH);
  // });
  #pragma endregion

  #pragma region Menu
  lcd.Begin();

  root.SetNext(&m2);
  m2.SetNext(&m3);
  m3.SetNext(&root);

  menu.Begin(&root);
  #pragma endregion

  #pragma region Audio
  pinMode(AudioPins::HP_SW_PIN, INPUT_PULLUP);
  pinMode(AudioPins::AUDIO_SEL_PIN, OUTPUT);

  digitalWrite(AudioPins::AUDIO_SEL_PIN, LOW);

  adc.Begin();
  #pragma endregion
  #pragma endregion

  digitalWrite(PowerPins::STRIP_EN_PIN, HIGH);

  #pragma region Debug
  pinMode(DiagPins::DEBUG_PIN, OUTPUT);
  pinMode(DiagPins::STATUS_PIN, OUTPUT);
  #pragma endregion

  #pragma region Remove Later
  // pinMode(MidiPins::IN_PIN, OUTPUT);
  #pragma endregion

  Serial.println("Startup Complete");

  lcd.SetBuffer(Line::TOP, "Count:");

  delay(500);
}

void loop() {
  #pragma region System Tests
  #pragma region Menu Test
  // menu.Next();

  String str(count, 10);
  lcd.SetBuffer(Line::BOT, str);
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
  // pwm0.SetState(1, count + 10);
  // pwm0.SetState(3, count + 200);
  // pwm0.SetState(7, count + 120);

  // for (auto &&st : testLEDStates)
  // {
  //   st += 10;
  // }
  

  // pwm0.SetStates(testLEDStates, 8);
  // pwm1.SetStates(firstState, 8);
  // pwm2.SetStates(secondState, 8);

  // ledPWM.SetRGB(0, 255, 0, 0);
  // ledPWM.SetRGB(1, 0, 255, 0);
  // ledPWM.SetRGB(2, 0, 0, 255);
  // ledPWM.SetRGB(3, 255, 255, 255);

  if (indCount > 15)
  {
    indCount = 0;
  }
  leds.Clear();
  leds.SetLED(indCount, LEDState::ON);
  #pragma endregion

  // IndicatorTest();
  // RelayTest();
  count++;
  indCount++;
  #pragma endregion

  // UpdateButtons();
  // ledPWM.Update();
  // UpdateCurrentMonitors();
  // analogWrite(SWITCHPins::ENC1_PIN, currentMonitors[0].ToByte());
  // DebugSignal(currentMonitors[0].ToByte(), 10);
  // DebugSignal(count, 10);
  UpdatePWM();
  delay(1000);
  // IndicatorTest(500, DiagPins::STATUS_PIN);
  // IndicatorTest(500, MidiPins::IN_PIN);
  // delay(100);
}