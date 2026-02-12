#pragma once

#ifdef ARDUINO
#include <FastLED.h>

#else
#include <iostream>
#include <iomanip>
#endif

#include "system.h"
#include "animator.h"
#include "display.h"

// Hardware setup

constexpr const unsigned char MaxPower = 255;

constexpr const long FramePeriodInMs = 1024 / 32;

extern Display display;
extern Animator animator;

