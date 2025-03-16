#ifndef TECNOCLUB_ST7789_H
#define TECNOCLUB_ST7789_H

#include "Tecnoclub_pins.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

namespace Display {
extern Adafruit_ST7789 tft;
void init(uint16_t width, uint16_t height, uint8_t spiMode = (uint8_t)0U,
          bool test = true);

// This is perfect forwarding. This means that print can take any argument
// and forward it to Print::print with the appropriate type.
// This way, it isn't necessary to write one overload for each overload of
// Print::print. They have to be defined in the .h file.
template <typename T,
          typename... Args> // The first argument is separate from the rest,
                            // because it determines which overload to call
size_t print(T &&value,
             Args &&...args) { // First argument is of type
                               // T. The rest are of types
                               // Args.
  return tft.print(std::forward<T>(value), std::forward<Args>(args)...);
}

template <typename T, typename... Args>
size_t println(T &&value, Args &&...args) {
  return tft.println(std::forward<T>(value), std::forward<Args>(args)...);
}

// Some overloads won't work with templates:

// Templates don't understand default values
size_t print(double n, int digits = 2);
size_t println(double n, int digits = 2);

// __FlashStringHelper* might be confused with char*
size_t print(const __FlashStringHelper *f);
size_t println(const __FlashStringHelper *f);

// Printable defines custom printing properties
size_t print(const Printable &obj);
size_t println(const Printable &obj);

size_t println();

void test();
} // namespace Display

#endif
