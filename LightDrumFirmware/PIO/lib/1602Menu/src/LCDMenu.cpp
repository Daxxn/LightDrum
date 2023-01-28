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

LCDMenu::LCDMenu(LCDScreen *screen, String *menus, uint8_t menuCount)
{
  this->_screen = screen;
  this->_mainMenu = 0;
  this->SetMenus(menus, menuCount);
}

LCDMenu::LCDMenu(LCDScreen *screen, String *menus, uint8_t menuCount, uint8_t mainMenu)
{
  this->_screen = screen;
  this->_mainMenu = mainMenu;
  this->SetMenus(menus, menuCount);
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
  // OLD
  // String output[menuCount];
  // for (uint8_t i = 0; i < menuCount; i++)
  // {
  //   output[i] = this->SetMenu(menus[i]);
  //   Serial.print("Menu ");
  //   Serial.print(i);
  //   Serial.println(output[i]);
  // }
  // this->_menus = output;
  MenuItem output[menuCount];
  for (uint8_t i = 0, j = 0; i < menuCount; i++, j += 2)
  {
    MenuItem temp = MenuItem(menus[j], menus[j + 1]);
    output[i] = temp;
  }
  this->_menus = output;
}

String LCDMenu::SetMenu(String menu)
{
  String line1 = menu.substring(0, 16);
  String line2 = menu.substring(16);
  line1 += LINE_PADDING;
  line2 += LINE_PADDING;
  return line1 + line2;
}

void LCDMenu::Update()
{
  if (this->_currentMenu != this->_selectedMenu)
  {
    Serial.print(this->_selectedMenu);
    Serial.print(' ');
    Serial.println(this->_currentMenu);
    this->_screen->Clear();
    delay(100);
    this->_currentMenu = this->_selectedMenu;
    // this->_screen->Print(this->_menus[this->_currentMenu]);
    this->_screen->Println(this->_menus[this->_currentMenu].line1);
    this->_screen->Print(this->_menus[this->_currentMenu].line2);
    delay(100);
  }
}

void LCDMenu::HandleUp()
{
  Serial.println("UP");
  if (this->_selectedMenu < this->_menuCount)
  {
    this->_selectedMenu++;
  }
  else
  {
    this->_selectedMenu = 0;
  }
  this->Update();
}

void LCDMenu::HandleDown()
{
  Serial.println("DOWN");
  if (this->_selectedMenu > 0)
  {
    this->_selectedMenu--;
  }
  else
  {
    this->_selectedMenu = this->_menuCount - 1;
  }
  this->Update();
}

void LCDMenu::HandleHome()
{
  Serial.println("HOME");
  this->_selectedMenu = this->_mainMenu;
  this->Update();
}

void LCDMenu::HandleBack()
{
  Serial.println("BACK");
  this->_selectedMenu = this->_prevMenu;
  this->Update();
}