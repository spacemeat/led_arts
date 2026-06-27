#include <FastLED.h>

// ----- Pinouts
const int LED_STRIP0 = 13;

// ----- Frame buffer setup -----
// Useful numbers for later use.
const int LEDS_PER_METER = 60;
const int METERS_PER_STRIP = 5;
const int LEDS_PER_STRIP = LEDS_PER_METER * METERS_PER_STRIP;
// Here's where the colors actually live. CRGB is a FastLED type 
// representing one pixel's color.
CRGB frame_buffer[LEDS_PER_STRIP];

int starting_led_idx = 0;

// This is called once when the board powers on.
void setup()
{
  // Set up the FastLED array.
  // It's a template! This makes a customized type. Ask if it's confusing!
  FastLED.addLeds<WS2812B, LED_STRIP0, GRB>(frame_buffer, LEDS_PER_STRIP);

  // Zero out the buffer. C/C++ don't do this automatically.
  ::memset(frame_buffer, 0, sizeof(CRGB) * LEDS_PER_STRIP);
}

// This is called every 30th of a second from loop().
void animate_strip()
{
  // delay by 33 ms. 1000ms / 30fps.
  delay(1000/30);
  
  // Every frame, we're starting at the next pixel.
  starting_led_idx += 1;
  // Loop! For each pixel.
  for (int led_idx = 0; led_idx < LEDS_PER_STRIP; ++led_idx)
  {
    // For this pixel, but starting at the starting index,
    //    - The % operator is "nodulus" - remainder by division. It's how
    //      we loop around the end of the strip back to the front.
    int computed_led_idx = (starting_led_idx + led_idx) % LEDS_PER_STRIP;
    // Colorized by Hue, Saturation, Value
    //              ^^^ = Color on the color wheel: red->yellow->green->cyan->blue->magenta
    //                   ^^^^^^^^^^ = How colorful: from gray to full color
    //                               ^^^^^ = How dark: black to full brightness
    CHSV hsv { max(255, led_idx), 255, max(0, min(127, led_idx - 127)) };
    // Set the color to the buffer. That's the LED's color when it gets banged out.
    frame_buffer[computed_led_idx] = hsv;
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
