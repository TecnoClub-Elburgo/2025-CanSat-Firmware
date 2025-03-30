// SPDX-FileCopyrightText: 2025 TecnoClub Elburgo <tecnoinfoelburgo@gmail.com>
// SPDX-FileContributor: 2025 EGJ-Moorington <egjmoorington@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "TecnoClub_BME280_TSL2591.h"
#include "TecnoClub_ST7789.h"

namespace {
BlueDot_BME280_TSL2591 bme280;
BlueDot_BME280_TSL2591 tsl2591;

float temperature;
float humidity;
float pressure;
float illuminance;
} // namespace

namespace WeatherStation {
void init() {
  bme280.parameter.I2CAddress =
      0x77; // The BME280 is hardwired to use the I2C Address 0x77
  tsl2591.parameter.I2CAddress = 0x29;
  Wire.begin();

  // Set BME280 + TSL2591 up
  tsl2591.parameter.gain = 0b01;
  tsl2591.parameter.integration = 0b000;
  tsl2591.config_TSL2591();

  bme280.parameter.sensorMode = 0b11;
  bme280.parameter.IIRfilter = 0b100;
  bme280.parameter.humidOversampling = 0b101;
  bme280.parameter.tempOversampling = 0b101;
  bme280.parameter.pressOversampling = 0b101;
  bme280.parameter.pressureSeaLevel = 1013.25;
  bme280.parameter.tempOutsideCelsius = 15;

  bool bmeFound = bme280.init_BME280() == 0x60;
  bool tslFound = tsl2591.init_TSL2591() == 0x50;
  if (!bmeFound) {
    Serial.print(F("BME280 could not be found! "));
    Display::tft.print(F("BME not found! "));
  }
  if (!tslFound) {
    Serial.print(F("TSL2591 could not be found!"));
    Display::tft.print(F("TSL not found!"));
  }
  if (bmeFound && tslFound) {
    Serial.print(F("success!"));
    Display::tft.print(F("success!"));
  }

  Serial.println();
  Display::tft.println();
}

String getMeasurements() {
  temperature = bme280.readTempC();
  humidity = bme280.readHumidity();
  pressure = bme280.readPressure();
  illuminance = tsl2591.readIlluminance_TSL2591();

  return "T: " + (String)temperature + " H: " + (String)humidity +
         " P: " + (String)pressure + " I: " + (String)illuminance;
}
} // namespace WeatherStation
