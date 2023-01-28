#include <Arduino.h>

// BORKED
unsigned char *AppendArray(unsigned char arr1[], unsigned char arr2[])
{
  unsigned char output[sizeof(arr1) + sizeof(arr2)] = {};
  for (size_t i = 0, j = sizeof(arr1); i < sizeof(output); i++, j++)
  {
    output[i] = arr1[i];
    output[j] = arr2[i];
  }
}