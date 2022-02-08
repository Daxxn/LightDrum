#include <Arduino.h>
#include "LCDMenu.h"
#include "LCDScreen.h"

LCDMenu::LCDMenu(LCDScreen *screen)
{
  this->_screen = screen;
  this->_mainMenu = 0;
}

LCDMenu::LCDMenu(LCDScreen *screen, uint8_t mainMenu)
{
  this->_screen = screen;
  this->_mainMenu = mainMenu;
}

void LCDMenu::Begin()
{
  this->_screen->Begin();
  this->_selectedMenu = this->_mainMenu;
  this->Update();
}

void LCDMenu::SetMenus(String menus[], uint8_t menuCount)
{
  this->_menuCount = menuCount;
  for (size_t i = 0; i < menuCount; i++)
  {
    this->_menus[i] = this->SetMenu(menus[i]);
  }
}

String LCDMenu::SetMenu(String menu)
{
  String line1 = menu.substring(0, 16);
  String line2 = menu.substring(16, 16 * 2);
  line1.concat(LINE_PADDING);
  line2.concat(LINE_PADDING);
  return line1 + line2;
}

void LCDMenu::Update()
{
  if (this->_currentMenu != this->_selectedMenu)
  {
    this->_screen->Clear();
    this->_screen->Print(this->_menus[this->_selectedMenu]);
    this->_currentMenu = this->_selectedMenu;
  }
}

void LCDMenu::HandleUp()
{
  if (this->_selectedMenu < this->_menus->length())
  {
    this->_selectedMenu++;
  }
  this->Update();
}

void LCDMenu::HandleDown()
{
  if (this->_selectedMenu > 0)
  {
    this->_selectedMenu--;
  }
  this->Update();
}

void LCDMenu::HandleHome()
{
  this->_selectedMenu = this->_mainMenu;
  this->Update();
}

void LCDMenu::HandleBack()
{
  this->_selectedMenu = this->_prevMenu;
  this->Update();
}