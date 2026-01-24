#pragma once

#include "system.h"

enum class Color : uint8_t
{
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    LT_BLACK,
    LT_RED,
    LT_GREEN,
    LT_YELLOW,
    LT_BLUE,
    LT_MAGENTA,
    LT_CYAN,
    LT_WHTIE
};

struct ColorPair
{
    //ColorPair(uint8_t bg, uint8_t fg) :  bg{bg}, fg{fg} {}
    uint8_t bg : 4;
    uint8_t fg : 4;
};

extern CRGB ansi_colors[16];

