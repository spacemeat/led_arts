#ifndef HARDWARE_h
#define HARDWARE_h

#ifdef ARDUINO
#include <FastLED.h>
#endif // #ifdef ARDUINO

void setup_hardware();
void setup_led_segment(int segment_idx, int led_idx, int num_leds);

constexpr const unsigned char MaxPower = 255;

#endif // #ifdef HARDWARE_h
