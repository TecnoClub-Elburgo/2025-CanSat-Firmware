// SPDX-FileCopyrightText: 2025 TecnoClub Elburgo <tecnoinfoelburgo@gmail.com>
// SPDX-FileContributor: EGJ-Moorington <egjmoorington@gmail.com>
//
// SPDX-License-Identifier: MIT

#include <Arduino.h>

#include "Tecnoclub_BME280_TSL2591.h"
#include "Tecnoclub_ST7789.h"
#include "Tecnoclub_SX1278.h"

// put function declarations here:
int myFunction(int x, int y);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  Display::init(); // Init ST7789 240x240

  // initialize SX1278 with default settings
  Radio::init();

  // start transmitting the first packet
  Serial.println(F("[SX1278] Sending first packet ... "));
  Display::tft.println(F("[SX1278] Sending first packet ... "));

  // you can transmit C-string or Arduino string up to
  // 255 characters long
  Radio::startTransmit("Hello World!");

  // you can also transmit byte array up to 255 bytes long
  /*
    byte byteArr[] = {0x01, 0x23, 0x45, 0x67,
                      0x89, 0xAB, 0xCD, 0xEF};
    transmissionState = radio.startTransmit(byteArr, 8);
  */

  Serial.print(F("[BME280 + TSL2591] Initialising... "));
  Display::tft.print(F("[BMETSL] Initialising... "));

  WeatherStation::init();

  Display::tft.println();
  Display::tft.print("Setup took ");
  Display::tft.setTextColor(ST77XX_MAGENTA);
  Display::tft.print(millis() / 1000);
  Display::tft.setTextColor(ST77XX_WHITE);
  Display::tft.println(" seconds.");
}

// counter to keep track of transmitted packets
int count = 0;

String measurements;
void loop() {
  // put your main code here, to run repeatedly:

  measurements = WeatherStation::getMeasurements();

  Display::tft.setCursor(0, 170);
  Display::tft.fillRect(0, 170, 240, 40, ST77XX_BLACK);
  Serial.println("[BME280 + TSL2591] Measurements: " + measurements);
  Display::tft.print("[BMETSL] Measurements: " + measurements);

  // check if the previous transmission finished
  if (Radio::checkTransmitFinish()) {

    // wait a second before transmitting again
    delay(1000);

    // send another one
    Display::tft.setCursor(0, 120);
    Display::tft.fillRect(0, 120, 240, 40, ST77XX_BLACK);

    Serial.print(F("[SX1278] Sending another packet ... "));
    Serial.print(count++);
    Display::tft.print(F("[SX1278] Sending packet # "));
    Display::tft.print(count);
    Display::tft.print(F(" ... "));

    // you can transmit C-string or Arduino string up to
    // 255 characters long
    String str = "Hello World! #" + String(count) + measurements;
    Radio::startTransmit(str);

    // you can also transmit byte array up to 255 bytes long
    /*
      byte byteArr[] = {0x01, 0x23, 0x45, 0x67,
                        0x89, 0xAB, 0xCD, 0xEF};
      transmissionState = radio.startTransmit(byteArr, 8);
      */
  }
}

// put function definitions here:
int myFunction(int x, int y) { return x + y; }
