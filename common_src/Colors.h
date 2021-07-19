#ifndef __COLORS_H__
#define __COLORS_H__

#include <stdint.h>

struct Color {
    uint8_t r,g,b;
};

const struct Color WHITE = {0xff, 0xff, 0xff};
const struct Color BLACK = {0x00, 0x00, 0x00};
const struct Color HUD_COLOR = {0xAD, 0x86, 0x33};
const struct Color FONDO_ARMA = {0xFF, 0x00, 0xFF};
const struct Color ROJO_CLARO = {0xa7, 0x03, 0x03};
const struct Color ROJO = {0xff, 0x00, 0x00};
#endif