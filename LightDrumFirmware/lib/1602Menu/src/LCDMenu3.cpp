#include <Arduino.h>
#include "LCDMenu3.h"
#include "LCDScreen.h"

LCDMenu3::LCDMenu3(LCDScreen *screen)
{
  this->_screen = screen;
}

void LCDMenu3::SetMenu(int index, uint8_t menu[32])
{
  if (index == 0)
  {
    this->Copy(this->_menuOne, menu);
  }
  else if (index == 1)
  {
    this->Copy(this->_menuTwo, menu);
  }
  else if (index == 2)
  {
    this->Copy(this->_menuThree, menu);
  }
  // else if (this->_currentMenu == 3)
  // {
  //   this->Copy(this->_menuFour, menu);
  // }
}

void LCDMenu3::Copy(uint8_t _menu[32], uint8_t menu[32])
{
  for (size_t i = 0; i < 32; i++)
  {
    _menu[i] = menu[i];
  }
}

void LCDMenu3::Begin()
{
  this->_screen->Begin();
}

void LCDMenu3::Update()
{
  if (this->_currentMenu == 0)
  {
    this->Send(this->_menuOne);
  }
  else if (this->_currentMenu == 1)
  {
    this->Send(this->_menuTwo);
  }
  else if (this->_currentMenu == 2)
  {
    this->Send(this->_menuThree);
  }
  else if (this->_currentMenu == 3)
  {
    this->Send(this->_menuFour);
  }
}

void LCDMenu3::Send(uint8_t top[16], uint8_t bot[16])
{
  this->_screen->Clear();
  for (size_t i = 0; i < 16; i++)
  {
    this->_screen->Print(top[i]);
    Serial.print(top[i]);
  }
  this->_screen->Println();
  for (size_t i = 0; i < 16; i++)
  {
    this->_screen->Print(bot[i]);
  }
}

void LCDMenu3::Send(uint8_t menu[32])
{
  this->_screen->Clear();
  for (size_t i = 0; i < 16; i++)
  {
    this->_screen->Print(menu[i]);
    Serial.print(menu[i]);
    Serial.print(' ');
  }
  Serial.println();

  this->_screen->Println();
  for (size_t i = 16; i < 32; i++)
  {
    this->_screen->Print(menu[i]);
    Serial.print(menu[i]);
    Serial.print(' ');
  }
  Serial.println();
}

#pragma region Event Handlers
void LCDMenu3::HandleUp()
{
  if (this->_currentMenu < 3)
  {
    this->_currentMenu++;
    Serial.print("UP ");
    Serial.println(this->_currentMenu);
  }
}

void LCDMenu3::HandleDown()
{
  if (this->_currentMenu > 0)
  {
    this->_currentMenu--;
    Serial.print("Down ");
    Serial.println(this->_currentMenu);
  }
}

void LCDMenu3::HandleHome()
{
  this->_currentMenu = 0;
    Serial.print("Home ");
    Serial.println(this->_currentMenu);
}

void LCDMenu3::HandleBack()
{
  Serial.println("Back - Not Used Yet.");
  this->_screen->Clear();
}
#pragma endregion