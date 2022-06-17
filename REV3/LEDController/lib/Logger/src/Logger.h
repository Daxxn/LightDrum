#pragma once

#include <Arduino.h>

class Logger
{
public:
  static void Log(const char msg[]);
  static void Log(uint8_t& data);
  static void Log(const char msg[], uint8_t& data);
  static void Log(const char msg[], const char data[]);
  
  static void LogArr(uint8_t* arr, unsigned int length);
  static void LogArr(const char msg[], uint8_t* arr, unsigned int length);
  
  static void LogByte(uint8_t& data);
  static void LogByte(const char msg[], uint8_t& data);
private:
  #ifdef DEBUG
  static const bool enable = true;
  #else
  static const bool enable = false;
  #endif
};