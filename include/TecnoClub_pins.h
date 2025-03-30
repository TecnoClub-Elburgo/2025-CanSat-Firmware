/*
 * SPDX-FileCopyrightText: 2025 TecnoClub Elburgo <tecnoinfoelburgo@gmail.com>
 * SPDX-FileContributor: 2025 EGJ-Moorington <egjmoorington@gmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

// These two statements are part of a "header guard" pattern.
// It prevents duplicate declarations.
#ifndef TECNOCLUB_PINS_H
#define TECNOCLUB_PINS_H

#define SX1278_NSS 10
#define SX1278_DIO0 2
#define SX1278_RESET 41
#define SX1278_DIO1 -1 // Pin not exposed in AI-Thinker breakout

#define ST7789_CS -1 // CS is grounded
#define ST7789_RST 9 // Or set to -1 and connect to Arduino RESET pin
#define ST7789_DC 8

#endif
