/*
 * SPDX-FileCopyrightText: 2025 TecnoClub Elburgo <tecnoinfoelburgo@gmail.com>
 * SPDX-FileContributor: 2025 EGJ-Moorington <egjmoorington@gmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef TECNOCLUB_ST7789_H
#define TECNOCLUB_ST7789_H

#include "TecnoClub_pins.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

namespace Display {
extern Adafruit_ST7789 tft;

void init(uint16_t width = 240, uint16_t height = 240,
          uint8_t spiMode = SPI_MODE3, bool test = true);

void test();
} // namespace Display

#endif
