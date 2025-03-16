#ifndef TECNOCLUB_BME280_TSL2591_H
#define TECNOCLUB_BME280_TSL2591_H

#include <BlueDot_BME280_TSL2591.h>
#include <Wire.h>

namespace WeatherStation {
void init();

String getMeasurements();
} // namespace WeatherStation

#endif
