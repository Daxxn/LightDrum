#pragma once

#include <Arduino.h>
#include "LCDScreen.h"

#pragma region Definitions
#define LINE_COUNT 2
#define LINE_WIDTH 16
#define LINE_BUFFER_LEN 40

#define LINE_PADDING_LEN 24
const String LINE_PADDING = "                        ";
#pragma endregion

class LCDMenu
{
public:
  LCDMenu(LCDScreen *screen);
  LCDMenu(LCDScreen *screen, uint8_t mainMenu);

  void Begin();
  void SetMenus(String *menus, uint8_t menuCount);

  void HandleUp();
  void HandleDown();
  void HandleHome();
  void HandleBack();
private:
  LCDScreen *_screen;
  uint8_t _menuCount;
  uint8_t _selectedMenu;
  uint8_t _currentMenu;
  uint8_t _prevMenu;
  uint8_t _mainMenu;
  String *_menus;

  void Update();

  String SetMenu(String menu);
};