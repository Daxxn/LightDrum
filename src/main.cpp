#include <Arduino.h>
#include "LCDScreen.h"
#include "LCDMenu.h"
#include "Button.h"

int dataPins[8] = {
  36,34,32,30,28,26,24,22
};
int enPin = 38;
int rsPin = 42;
int rwPin = 40;

String menus[] = {
  "Menu 1        /\\  The Main Menu ",
  "Menu 2        /\\  Second Menu   ",
  "Menu 3        /\\  Third Menu    ",
  "Menu 4        /\\  Fourth Menu   "
};

LCDScreen lcd = LCDScreen(dataPins, rsPin, rwPin, enPin);
LCDMenu menu = LCDMenu(&lcd);

Button upBtn;
Button downBtn;
Button homeBtn;
Button backBtn;

// String data1 = "12345678901234567890123456789012345678901234567890";
// String data2 = "9876543210";

#pragma region Button Handlers
void UpdateButtons() {
  upBtn.Update();
  downBtn.Update();
  homeBtn.Update();
  backBtn.Update();
}
#pragma endregion

void setup() {
  Serial.begin(115200);

  Serial.println("Starting LCD Test Mode");
  upBtn   = Button(27, [] () { menu.HandleUp();   });
  downBtn = Button(29, [] () { menu.HandleDown(); });
  homeBtn = Button(25, [] () { menu.HandleHome(); });
  backBtn = Button(23, [] () { menu.HandleBack(); });

  menu.SetMenus(menus, 4);

  menu.Begin();
  // lcd.Begin();
}

void loop() {
// //   for (auto &&d : data)
// //   {
// //     lcd.print(d);
// //     Serial.print(d);
// //     delay(250);
// //   }
//   // Serial.println("Line1");
//   Serial.println("LongLine");
//   lcd.Println(data1);
//   delay(1000);
//   // Serial.println("Line2");
//   // lcd.Print(data2);
  
//   delay(1000);
//   Serial.println("Clear");
//   lcd.Clear();
//   delay(2000);
  UpdateButtons();
}