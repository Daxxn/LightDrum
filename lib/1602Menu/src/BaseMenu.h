#pragma once

#include <Arduino.h>

enum LineType {
  TOP = 0,
  BOTTOM = 0,
};

class BaseMenu
{
public:
  BaseMenu(uint8_t& topLine, uint8_t& bottomLine);
  uint8_t Index;
  bool IsMainMenu;
  uint8_t* TopLine;
  uint8_t* BottomLine;
  BaseMenu* NextMenu;
  BaseMenu* PrevMenu;

  uint8_t GetIndex();
  // uint8_t* GetLine(LineType type);
  // uint8_t* GetTopLine();
  // uint8_t* GetBottomLine();

  BaseMenu* GetNextMenu();
  BaseMenu* GetPrevMenu();

private:
};