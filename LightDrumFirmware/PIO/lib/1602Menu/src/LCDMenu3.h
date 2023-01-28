#pragma once

#include <Arduino.h>
#include "LCDScreen.h"

class LCDMenu3
{
public:
  LCDMenu3(LCDScreen *screen);

  void SetMenu(int index, uint8_t menu[32]);
  void Copy(uint8_t _menu[32], uint8_t menu[32]);
  
  void Begin();

  void HandleUp();
  void HandleDown();
  void HandleHome();
  void HandleBack();

  void Update();
private:
  LCDScreen *_screen;
  uint8_t _menuOne[32] = {};
  uint8_t _menuTwo[32] = {};
  uint8_t _menuThree[32] = {};
  uint8_t _menuFour[32] = {};
  int _currentMenu = 0;

  void Send(uint8_t top[16], uint8_t bot[16]);
  void Send(uint8_t menu[32]);
};