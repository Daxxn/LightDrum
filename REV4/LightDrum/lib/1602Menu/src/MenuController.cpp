#include <Arduino.h>
#include "MenuController.h"

MenuController::MenuController(LCDScreen2* screen)
{
  this->screen = screen;
}

void MenuController::Begin(Menu* root)
{
  this->screen->Begin();
  this->root = root;
  this->currentMenu = root;
  this->Update();
}

void MenuController::Update()
{
  this->screen->SetBuffers(
    this->currentMenu->GetTopMenu(),
    this->currentMenu->GetBotMenu()
  );
}

#pragma region Event Handlers
void MenuController::Next()
{
  Menu* temp = this->currentMenu->GetNext();
  if (temp != nullptr)
  {
    this->currentMenu = temp;
  }
  this->Update();
}

void MenuController::Prev()
{
  Menu* temp = this->currentMenu->GetPrev();
  if (temp != nullptr)
  {
    this->currentMenu = temp;
  }
  this->Update();
}

void MenuController::Home()
{
  this->currentMenu = root;
  this->Update();
}

void MenuController::Act()
{
  
}
#pragma endregion