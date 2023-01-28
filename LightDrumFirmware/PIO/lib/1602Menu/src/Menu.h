#pragma once

#include <Arduino.h>
#include "LCDScreen2.h"

class Menu
{
public:
  // Menu(const uint8_t& top, const uint8_t& bot);
  Menu(const uint8_t* menuData);
  ~Menu();

  void SetNext(Menu* next);
  void SetPrev(Menu* prev);

  Menu* GetNext() const;
  Menu* GetPrev() const;

  const uint8_t* GetMenu(Line line) const;
  const uint8_t* GetTopMenu() const;
  const uint8_t* GetBotMenu() const;
private:
  // const uint8_t* top;
  // const uint8_t* bot;
  uint8_t* top;
  uint8_t* bot;
  Menu* next;
  Menu* prev;

  void SplitLines(const uint8_t* menuData);
};