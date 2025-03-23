// SPDX-FileCopyrightText: 2025 TecnoClub Elburgo <tecnoinfoelburgo@gmail.com>
// SPDX-FileContributor: EGJ-Moorington <egjmoorington@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "TecnoClub_ST7789.h"

namespace {
// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable.

float p = 3.1415926;

// TFT test functions:
void testlines(uint16_t color) {
  Display::tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < Display::tft.width(); x += 6) {
    Display::tft.drawLine(0, 0, x, Display::tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < Display::tft.height(); y += 6) {
    Display::tft.drawLine(0, 0, Display::tft.width() - 1, y, color);
    delay(0);
  }

  Display::tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < Display::tft.width(); x += 6) {
    Display::tft.drawLine(Display::tft.width() - 1, 0, x,
                          Display::tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < Display::tft.height(); y += 6) {
    Display::tft.drawLine(Display::tft.width() - 1, 0, 0, y, color);
    delay(0);
  }

  Display::tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < Display::tft.width(); x += 6) {
    Display::tft.drawLine(0, Display::tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < Display::tft.height(); y += 6) {
    Display::tft.drawLine(0, Display::tft.height() - 1,
                          Display::tft.width() - 1, y, color);
    delay(0);
  }

  Display::tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < Display::tft.width(); x += 6) {
    Display::tft.drawLine(Display::tft.width() - 1, Display::tft.height() - 1,
                          x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < Display::tft.height(); y += 6) {
    Display::tft.drawLine(Display::tft.width() - 1, Display::tft.height() - 1,
                          0, y, color);
    delay(0);
  }
}

void testdrawtext(char *text, uint16_t color) {
  Display::tft.setCursor(0, 0);
  Display::tft.setTextColor(color);
  Display::tft.setTextWrap(true);
  Display::tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  Display::tft.fillScreen(ST77XX_BLACK);
  for (int16_t y = 0; y < Display::tft.height(); y += 5) {
    Display::tft.drawFastHLine(0, y, Display::tft.width(), color1);
  }
  for (int16_t x = 0; x < Display::tft.width(); x += 5) {
    Display::tft.drawFastVLine(x, 0, Display::tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  Display::tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < Display::tft.width(); x += 6) {
    Display::tft.drawRect(Display::tft.width() / 2 - x / 2,
                          Display::tft.height() / 2 - x / 2, x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  Display::tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = Display::tft.width() - 1; x > 6; x -= 6) {
    Display::tft.fillRect(Display::tft.width() / 2 - x / 2,
                          Display::tft.height() / 2 - x / 2, x, x, color1);
    Display::tft.drawRect(Display::tft.width() / 2 - x / 2,
                          Display::tft.height() / 2 - x / 2, x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = radius; x < Display::tft.width(); x += radius * 2) {
    for (int16_t y = radius; y < Display::tft.height(); y += radius * 2) {
      Display::tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = 0; x < Display::tft.width() + radius; x += radius * 2) {
    for (int16_t y = 0; y < Display::tft.height() + radius; y += radius * 2) {
      Display::tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  Display::tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 0xF800;
  int t;
  int w = Display::tft.width() / 2;
  int x = Display::tft.height() - 1;
  int y = 0;
  int z = Display::tft.width();
  for (t = 0; t <= 15; t++) {
    Display::tft.drawTriangle(w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}

void testroundrects() {
  Display::tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 100;
  int i;
  int t;
  for (t = 0; t <= 4; t += 1) {
    int x = 0;
    int y = 0;
    int w = Display::tft.width() - 2;
    int h = Display::tft.height() - 2;
    for (i = 0; i <= 16; i += 1) {
      Display::tft.drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}

void tftPrintTest() {
  Display::tft.setTextWrap(false);
  Display::tft.fillScreen(ST77XX_BLACK);
  Display::tft.setCursor(0, 30);
  Display::tft.setTextColor(ST77XX_RED);
  Display::tft.setTextSize(1);
  Display::tft.println("Hello World!");
  Display::tft.setTextColor(ST77XX_YELLOW);
  Display::tft.setTextSize(2);
  Display::tft.println("Hello World!");
  Display::tft.setTextColor(ST77XX_GREEN);
  Display::tft.setTextSize(3);
  Display::tft.println("Hello World!");
  Display::tft.setTextColor(ST77XX_BLUE);
  Display::tft.setTextSize(4);
  Display::tft.print(1234.567);
  delay(1500);
  Display::tft.setCursor(0, 0);
  Display::tft.fillScreen(ST77XX_BLACK);
  Display::tft.setTextColor(ST77XX_WHITE);
  Display::tft.setTextSize(0);
  Display::tft.println("Hello World!");
  Display::tft.setTextSize(1);
  Display::tft.setTextColor(ST77XX_GREEN);
  Display::tft.print(p, 6);
  Display::tft.println(" Want pi?");
  Display::tft.println(" ");
  Display::tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  Display::tft.println(" Print HEX!");
  Display::tft.println(" ");
  Display::tft.setTextColor(ST77XX_WHITE);
  Display::tft.println("Sketch has been");
  Display::tft.println("running for: ");
  Display::tft.setTextColor(ST77XX_MAGENTA);
  Display::tft.print(millis() / 1000);
  Display::tft.setTextColor(ST77XX_WHITE);
  Display::tft.print(" seconds.");
}
} // namespace

namespace Display {
// For 1.14", 1.3", 1.54", 1.69", and 2.0" TFT with ST7789:
Adafruit_ST7789 tft = Adafruit_ST7789(&SPI1, ST7789_CS, ST7789_DC, ST7789_RST);

void init(uint16_t width, uint16_t height, uint8_t spiMode, bool test) {
  Serial.print(F("[ST7789] Hello! Initialising..."));

  // Init ST7789 240x240
  tft.init(width, height, spiMode);

  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can
  // override it here Note that speed allowable depends on chip and quality of
  // wiring, if you go too fast, you may end up with a black screen some times,
  // or all the time.
  // tft.setSPISpeed(40000000);

  tft.fillScreen(ST77XX_BLACK);

  Serial.println(F(" done!"));

  if (test) {
    Display::test();
  }

  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextWrap(true);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1, 2);
}

void test() {
  Serial.print(F("[ST7789] Testing..."));

  uint16_t time = millis();
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  // line draw test
  testlines(ST77XX_YELLOW);
  delay(500);

  // optimized lines
  testfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(500);

  testdrawrects(ST77XX_GREEN);
  delay(500);

  testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
  delay(500);

  tft.fillScreen(ST77XX_BLACK);
  testfillcircles(10, ST77XX_BLUE);
  testdrawcircles(10, ST77XX_WHITE);
  delay(500);

  testroundrects();
  delay(500);

  testtriangles();
  delay(500);

  // tft print function!
  tftPrintTest();
  delay(1500);

  Serial.println(F(" done!"));
}
} // namespace Display
