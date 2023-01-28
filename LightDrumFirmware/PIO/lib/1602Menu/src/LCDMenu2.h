#pragma once

#include <Arduino.h>
#include "LCDScreen.h"
#include "BaseMenu.h"

class LCDMenu2
{
public:
  LCDMenu2(LCDScreen *screen);

  void Begin(BaseMenu *rootMenu);
  void Begin();

  void HandleUp();
  void HandleDown();
  void HandleHome();
  void HandleBack();

  void Update();

  void Test(const uint8_t arr[16]);
private:
  LCDScreen *_screen;
  BaseMenu *_currentMenu;
  BaseMenu *_rootMenu;
};