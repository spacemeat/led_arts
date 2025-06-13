#include <FastLED.h>

// ----- Pinouts
const int LED_STRIP0 = 13;

// ----- Frame buffer setup -----
const int LEDS_PER_METER = 60;
const int METERS_PER_STRIP = 5;
const int LEDS_PER_STRIP = LEDS_PER_METER * METERS_PER_STRIP;
CRGB frame_buffer[LEDS_PER_STRIP];

int starting_led_idx = 0;

// This is called once when the board powers on.
void setup()
{
  // Set up the FastLED array.
  FastLED.addLeds<WS2812B, LED_STRIP0, GRB>(frame_buffer, LEDS_PER_STRIP);
  memset(frame_buffer, 0, sizeof(CRGB) * LEDS_PER_STRIP);
}

// This is called every 30th of a second from loop().
void animate_strip()
{
  delay(1000/30);
  
  starting_led_idx += 1;
  for (int led_count = 0; led_count < LEDS_PER_STRIP; ++led_count)
  {
    int led_idx = (starting_led_idx + led_count) % LEDS_PER_STRIP;
    CHSV hsv { led_count, 255, (LEDS_PER_STRIP - led_count) % 127 };
    frame_buffer[led_idx] = hsv;
  }
}

// This is called likely more than every 30th of a second.
void loop()
{
  // Animate the LED strip itself by filling in the frame buffer with new
  // CRGB color values.
  animate_strip();
  // This drives the frame_buffer onto the LED strip.
 	FastLED.show();
}