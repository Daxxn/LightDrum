#include <Arduino.h>
#include "Menu.h"

Menu::Menu(const uint8_t* menuData)
{
  this->top = new uint8_t[16];
  this->bot = new uint8_t[16];
  this->SplitLines(menuData);
}

Menu::~Menu()
{
  delete[] this->top;
  delete[] this->bot;
}

// Menu::Menu(const uint8_t& top, const uint8_t& bot)
// {
//   this->top = &top;
//   this->bot = &bot;
// }

void Menu::SplitLines(const uint8_t* menuData)
{
  for (size_t t = 0, b = 16; t < 16; t++, b++)
  {
    this->top[t] = menuData[t];
    this->bot[t] = menuData[b];
  }
}

void Menu::SetNext(Menu* next)
{
  this->next = next;
  next->prev = this;
}

void Menu::SetPrev(Menu* prev)
{
  this->prev = prev;
}

Menu* Menu::GetNext() const
{
  return this->next;
}

Menu* Menu::GetPrev() const
{
  return this->prev;
}

const uint8_t* Menu::GetMenu(Line line) const
{
  if (line == Line::TOP)
  {
    return this->top;
  }
  return this->bot;
}

const uint8_t* Menu::GetTopMenu() const
{
  return this->top;
}

const uint8_t* Menu::GetBotMenu() const
{
  return this->bot;
}