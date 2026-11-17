#include "hardware.hpp"

CRGB frame_buffer[NumLeds];

#ifndef ARDUINO

void setup_hardware() {}

void setup_led_segment(int segment_idx, int led_idx, int num_leds) {}

#else

#define ESP32_VROOM_32D_38pin 1

/* For DOIT ESP32 DEVKIT V1   (ESP32-VROOM-32D 30-pin layout)
 * EN
 * SENSOR VP
 * SENSOR VN
 * 34  - strip 8
 * 36  - strip 7
 * 32  - strip 6
 * 33  - strip 5
 * 25  - strip 4
 * 26  - strip 3
 * 27  - strip 2
 * 14
 * 12
 * 13  - strip 1
 * GND - ground to board
 * 5V  - 5V to src
 */

#ifdef ESP32_VROOM_32D_30pin
const std::array<int> led_pins = {13, 27, 26, 25, 33, 32, 36, 34};

#elif ESP32_VROOM_32D_38pin
const std::array<int> led_pins = {13, 27, 26, 25, 33, 32, 23, 12};

#endif

std::array<bool> led_segment_was_set = {false, false, false, false,
                                        false, false, false, false};

void setup_led_segment(int segment_idx, int led_idx, int num_leds) {
  if (led_segment_was_set[segment_idx] == false) {
    int pin = led_pins[segment_idx];
    pinMode(LED_S1, OUTPUT);
    FastLED.addLeds<WS2812B, pin, GRB>(frame_buffer + led_idx, num_leds);
    led_segment_was_set[segment_idx] = true;
  }
}
/*
const int LED_S1 = 13;
const int LED_S2 = 27;
const int LED_S3 = 26;
const int LED_S4 = 25;
const int LED_S5 = 33;
const int LED_S6 = 32;
const int LED_S7 = 23;
const int LED_S8 = 12;

  pinMode(LED_S1, OUTPUT);
  pinMode(LED_S2, OUTPUT);
  pinMode(LED_S3, OUTPUT);
  pinMode(LED_S4, OUTPUT);
  pinMode(LED_S5, OUTPUT);
  pinMode(LED_S6, OUTPUT);
  pinMode(LED_S7, OUTPUT);
  pinMode(LED_S8, OUTPUT);

  FastLED.addLeds<WS2812B, LED_S2, GRB>(frame_buffer + NumLedsPerTentacle * 1,
                                        NumLedsPerTentacle);
  FastLED.addLeds<WS2812B, LED_S3, GRB>(frame_buffer + NumLedsPerTentacle * 2,
                                        NumLedsPerTentacle);
  FastLED.addLeds<WS2812B, LED_S4, GRB>(frame_buffer + NumLedsPerTentacle * 3,
                                        NumLedsPerTentacle);
  FastLED.addLeds<WS2812B, LED_S5, GRB>(frame_buffer + NumLedsPerTentacle * 4,
                                        NumLedsPerTentacle);
  FastLED.addLeds<WS2812B, LED_S6, GRB>(frame_buffer + NumLedsPerTentacle * 5,
                                        NumLedsPerTentacle);
  FastLED.addLeds<WS2812B, LED_S7, GRB>(frame_buffer + NumLedsPerTentacle * 6,
                                        NumLedsPerTentacle);
  FastLED.addLeds<WS2812B, LED_S8, GRB>(frame_buffer + NumLedsPerTentacle * 7,
                                        NumLedsPerTentacle);
*/

#endif // #ifndef ARDUINO
