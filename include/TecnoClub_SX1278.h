/*
 * SPDX-FileCopyrightText: 2025 TecnoClub Elburgo <tecnoinfoelburgo@gmail.com>
 * SPDX-FileContributor: 2025 EGJ-Moorington <egjmoorington@gmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef TECNOCLUB_SX1278_H
#define TECNOCLUB_SX1278_H

#include "TecnoClub_pins.h"
#include <Arduino.h>
#include <RadioLib.h>

namespace Radio {
void init();

int16_t startTransmit(String &str, uint8_t addr = (uint8_t)0U);
int16_t startTransmit(const char *str, uint8_t addr = (uint8_t)0U);
int16_t startTransmit(const uint8_t *data, size_t len,
                      uint8_t addr = (uint8_t)0U);

bool checkTransmitFinish();
} // namespace Radio

#endif
