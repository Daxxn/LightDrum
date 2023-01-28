#include <Arduino.h>
#include "LCDMenu2.h"
#include "BaseMenu.h"
#include "Menus/MenuTest.h"

LCDMenu2::LCDMenu2(LCDScreen *screen)
{
  this->_screen = screen;
}

void LCDMenu2::Begin(BaseMenu *rootMenu)
{
  this->_screen->Begin();
  this->_rootMenu = rootMenu;
};

void LCDMenu2::Begin()
{
  this->_screen->Begin();
};

void LCDMenu2::Update()
{
  // BaseMenu* menu = this->_currentMenu;
  // Serial.println("TOP");
  // for (size_t i = 0; i < 16; i++)
  // {
  //   static uint8_t& arr = (*menu).TopLine;
  //   uint8_t val = arr[i];
  //   this->_screen->Print(val);
  //   Serial.print(val);
  //   Serial.print(' ');
  //   delayMicroseconds(40);
  // }
  // Serial.println();
  // delay(10);
  // this->_screen->Println();
  // delay(10);
  // Serial.println("BOT");
  // for (size_t i = 0; i < 16; i++)
  // {
  //   uint8_t val = menu.BottomLine[i];
  //   this->_screen->Print(val);
  //   Serial.print(val);
  //   Serial.print(' ');
  //   delayMicroseconds(40);
  // }
  // Serial.println();
}

void LCDMenu2::HandleUp()
{
  this->_currentMenu = this->_currentMenu->NextMenu;
}

void LCDMenu2::HandleDown()
{
  this->_currentMenu = this->_currentMenu->PrevMenu;
}

void LCDMenu2::HandleHome()
{
  this->_currentMenu = this->_rootMenu;
}

void LCDMenu2::HandleBack()
{
  this->_currentMenu = this->_currentMenu->PrevMenu;
}

void LCDMenu2::Test(const uint8_t arr[16])
{
  for (size_t i = 0; i < 16; i++)
  {
    this->_screen->Print(arr[i]);
    // delay(1000);
    // this->_screen->Clear();
    // delay(100);
  }
  delay(1000);
  this->_screen->Clear();
}