#include <Arduino.h>
#include "LCDScreen2.h"
#include "Button.h"
#include "MenuController.h"
#include "Menu.h"
#include "MenuData.h"
#include "Logger.h"
#include "STP16Driver.h"

#pragma region Old Menu Data
// uint8_t MenuOne[32] = {
//   0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
// //  97    98    99   100   101   102   103   104
// //   a     b     c     d     e     f     g     h
//   0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,
// // 105   106   107   108   109   110   111   112
// //   i     j     k     l     m     n     o     p
//   0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
// // 113   114   115   116   117   118   119   120
// //   q     r     s     t     u     v     w     x
//   0x79, 0x7A, 0x10, 0x11, 0x1E, 0x1F, 0x91, 0x14
// // 121   122   123   124   125   126   127   128
// //   y     z    RA    LA   DEG   BLK   OHM    PI
// };
// uint8_t MenuTwo[32] = {
//   0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
// //  65    66    67    68    69    70    71    72
// //   A     B     C     D     E     F     G     H
//   0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
// //  73    74    75    76    77    78    79    80
// //   I     J     K     L     M     N     O     P
//   0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
// //  81    82    83    84    85    86    87    88
// //   Q     R     S     T     U     V     W     X
//   0x59, 0x5A, 0x15, 0x9D, 0x9A, 0xB0, 0x30, 0x31
// //  89    90    91    92    93    94    95    96
// //   Y     Z    PI   INF   BLK  WBLK   MIC    WL
// };
// uint8_t MenuThree[32] = {
//   0x74, 0x65, 0x73, 0x74, 0x20, 0x6D, 0x65, 0x6E,
// // 116   101   115   116    32   109   101   110
//   0x75, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
// // 117     0     0     0     0     0     0     0
//   0x10, 0x11, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
// //  16    17     0     0     0     0     0     0
//   0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
// //   0     0     0     0     0     0     0     0
// };
#pragma endregion

#pragma region Pins
#pragma region LCD Pins
int dataPins[8] = {
  36,34,32,30,28,26,24,22
};
int enPin = 38;
int rsPin = 42;
int rwPin = 40;
#pragma endregion

#pragma region name
const int ledDPin = 39;
const int ledCPin = 37;
const int ledLPin = 35;
const int ledEPin = 33;
#pragma endregion
#pragma endregion

LCDScreen2 lcd(dataPins, rsPin, rwPin, enPin);
MenuController menu(&lcd);

STP16Driver leds(ledDPin, ledCPin, ledLPin, ledEPin);

// Menu root(MenuData::MenuOne);
// Menu m2(MenuData::MenuTwo);
// Menu m3(MenuData::MenuThree);

// Menu root(FunMenus::MenuOne);
// Menu m2(FunMenus::MenuTwo);
// Menu m3(FunMenus::MenuThree);

Menu root(MommasBDay::MenuOne);
Menu m2(MommasBDay::MenuTwo);
Menu m3(MommasBDay::MenuThree);

Button upBtn;
Button downBtn;
Button homeBtn;
// Button backBtn;

uint8_t tempStr[] = "Test  ";
byte count = 0;

#pragma region Button Handlers
void UpdateButtons() {
  upBtn.Update();
  downBtn.Update();
  homeBtn.Update();
  // backBtn.Update();
}
#pragma endregion

byte val = 0;

void setup() {
  delay(500);
  Serial.begin(115200);

  Logger::Log("Starting LCD Test Mode");
  // Serial.println("Starting LCD Test Mode");
  
  upBtn   = Button(27, [] () { menu.Next(); });
  downBtn = Button(29, [] () { menu.Prev(); });
  homeBtn = Button(25, [] () { menu.Home(); });

  Logger::Log("Button INIT Complete");
  // Serial.println("Button INIT Complete");

  root.SetNext(&m2);
  m2.SetNext(&m3);
  m3.SetNext(&root);


  Logger::Log("Menu Set Complete");
  // Serial.println("Menu Set Complete");

  menu.Begin(&root);
  // lcd.Begin();

  Logger::Log("Menu INIT Complete");
  // Serial.println("Menu INIT Complete");

  leds.Begin();
  Logger::Log("LED Driver INIT Complete");
}

void loop() {
  #pragma region New Screen Lib Test
  // Serial.print("Loop: ");
  // Serial.println(count);
  // tempStr[5] = count;
  // lcd.SetBuffer(Line::TOP, tempStr);
  #pragma endregion
  #pragma region Menu Test
  // menu.Update();
  lcd.Test();
  #pragma endregion

  #pragma region LED Driver Test
  
  #pragma endregion

  // count++;
  UpdateButtons();
  delay(100);
}