#pragma once

#include <Arduino.h>
#include "Menu.h"
#include "LCDScreen2.h"

class MenuController
{
public:
  MenuController(LCDScreen2* screen);
  void Begin(Menu* root);

  void Next();
  void Prev();
  void Home();
  void Act();
private:
  LCDScreen2* screen;
  Menu* currentMenu;
  Menu* root;

  void Update();
};