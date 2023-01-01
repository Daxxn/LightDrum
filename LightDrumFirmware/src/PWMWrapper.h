// #pragma once

// #include <Arduino.h>

// enum RGBColor
// {
//   RED = 0,
//   GREEN = 1,
//   BLUE = 2
// };

// struct PWMChannel
// {
//   PWMChannel(uint8_t channel,
//     uint8_t ri, uint8_t rp,
//     uint8_t gi, uint8_t gp,
//     uint8_t bi, uint8_t bp
//   ) {
//     this->channel = channel;
//     this->red = PWMPin(ri, rp);
//     this->green = PWMPin(gi, gp);
//     this->blue = PWMPin(bi, bp);
//   };
//   uint8_t channel;
//   PWMPin red;
//   PWMPin green;
//   PWMPin blue;
// };

// struct PWMPin
// {
//   PWMPin() {};
//   PWMPin(uint8_t index, uint8_t pin)
//   {
//     this->index = index;
//     this->pin = pin;
//   };
//   uint8_t index = 0;
//   uint8_t pin = 0;
// };


// class PWMWrapper
// {
// public:
//   PWMWrapper();
//   ~PWMWrapper();

//   void getICValues(uint8_t* buffer, uint8_t icIndex);
// private:
//   uint8_t channels[8][3] = {};
// };