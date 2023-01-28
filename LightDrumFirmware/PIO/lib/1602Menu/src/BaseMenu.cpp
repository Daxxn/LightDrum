#include <Arduino.h>
#include "BaseMenu.h"

BaseMenu::BaseMenu(uint8_t& topLine, uint8_t& bottomLine)
{
  this->Index = 0;
  this->IsMainMenu = false;
  // this->TopLine = 0;
  // this->BottomLine = 0;
  // this->TopLine = topLine;
  // this->BottomLine = bottomLine;
}

byte BaseMenu::GetIndex()
{
  return this->Index;
}

// uint8_t* BaseMenu::GetLine(LineType type)
// {
//   if (type == LineType::TOP) {
//     return this->TopLine;
//   }
//   return this->BottomLine;
// }

// uint8_t* BaseMenu::GetTopLine()
// {
//   return this->TopLine;
// }

// uint8_t* BaseMenu::GetBottomLine()
// {
//   return this->BottomLine;
// }

BaseMenu* BaseMenu::GetNextMenu()
{
  return this->NextMenu;
}

BaseMenu* BaseMenu::GetPrevMenu()
{
  return this->PrevMenu;
}