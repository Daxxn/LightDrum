#pragma once

#include <Arduino.h>
#include "BaseMenu.h"

class MenuOne : public BaseMenu {
  byte TopLine[16] = { 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70 };
};