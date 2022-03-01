#include <Arduino.h>
#include "Logger.h"


void Logger::Log(const char msg[])
{
  if (Logger::enable)
  {
    Logger::Log("Log", msg);
  }
}

void Logger::Log(const char msg[], const char data[])
{
  if (Logger::enable)
  {
    Serial.print(msg);
    Serial.print(" : ");
    Serial.println(data);
  }
}

void Logger::LogArr(uint8_t* arr, unsigned int length)
{
  if (Logger::enable)
  {
    Logger::LogArr("Array", arr, length);
  }
}

void Logger::LogArr(const char msg[], uint8_t* arr, unsigned int length)
{
  if (Logger::enable)
  {
    Serial.println(msg);
    for (size_t i = 0; i < length; i++)
    {
      Serial.print(arr[i]);
      if (i < length - 1)
      {
        Serial.print(", ");
      }
    }
    Serial.println();
  }
}

void Logger::LogByte(uint8_t& data)
{
  if (Logger::enable)
  {
    Logger::LogByte("Byte", data);
  }
}

void Logger::LogByte(const char msg[], uint8_t& data)
{
  if (Logger::enable)
  {
    Serial.print(msg);
    Serial.print(" : ");
    int size = sizeof(data) * 2;
    for (size_t i = size; i > 0; i--)
    {
      Serial.print((data >> (i - 1)) & 0b1);
    }
    Serial.println();
  }
}