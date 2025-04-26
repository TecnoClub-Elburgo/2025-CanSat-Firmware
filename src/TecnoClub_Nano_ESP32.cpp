// SPDX-FileCopyrightText: 2025 TecnoClub Elburgo <tecnoinfoelburgo@gmail.com>
// SPDX-FileContributor: 2025 EGJ-Moorington <egjmoorington@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "TecnoClub_Nano_ESP32.h"

namespace {}

namespace Camera {
void init() { Serial3.begin(115200); }

void read() {
  Serial3.println("Hello from Teensy!");
  Serial.println(Serial3.readString());
}
} // namespace Camera
