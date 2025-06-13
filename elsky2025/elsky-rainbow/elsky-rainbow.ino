#include <FastLED.h>

// ----- Pinouts
const int LED_STRIP0 = 14;

// ----- Frame buffer setup -----
const int LEDS_PER_METER = 60;
const int METERS_PER_STRIP = 5;
const int LEDS_PER_STRIP = LEDS_PER_METER * METERS_PER_STRIP;
CRGB frame_buffer[LEDS_PER_STRIP];

// ----- Timing setup -----
long current_time;
long frame_time;
// Each "frame" of animation is 1/30 of a second. (1/30 of 1000 milliseconds.)
const int FRAME_DURATION = 1000 / 30;

// This is called once when the board powers on.
void setup()
{
  // Set up the FastLED array.
  FastLED.addLeds<WS2812B, LED_STRIP0, GRB>(frame_buffer, LEDS_PER_STRIP);
  memset(frame_buffer, 0, sizeof(CRGB) * LEDS_PER_STRIP);

  // Initialize the timing.
  current_time = millis();
  frame_time = current_time;
}

// This is called every 30th of a second from loop().
void animate_strip()
{
  // led_idx_offset cycles [0, LEDS_PER_STRIP) every 0.1 seconds
  int led_idx_offset = (current_time / 100) % LEDS_PER_STRIP;

  // for each LED,
  for (int led_idx = 0; led_idx < LEDS_PER_STRIP; ++led_idx)
  {
    // Compute where to start the rainbow (red; hue 0). Cycles
    // around to 0 and back.
    int led_idx_mod = (led_idx + led_idx_offset) % LEDS_PER_STRIP;

    // [0.0, 1.0)
    float hue_factor = (float)led_idx / (float)LEDS_PER_STRIP;

    // Paint that LED full color, half bright
    frame_buffer[led_idx_mod] = CHSV(
      (int)(256.0f * hue_factor), // hue
      255,  // saturation
      127); // value
  }

  // And that's it. We animated each segment, and so all the frame buffer's colors
  // should be set.
}

// This is called by loop(). It computes how much time we have to wait
// for the next frame of animation to begin, delays by that much, and
// then sets up the next wait time.
void wait_for_time()
{
  // Get the number of milliseconds since the board was powered on.
  current_time = millis();
  // If there is time left in this frame, 
  if (current_time < frame_time)
  {
    // sleep through it,
    delay(frame_time - current_time);
    // and set the next frame time.
    frame_time += FRAME_DURATION;
  }
  else
  {
    // If the last frame took longer than it should have, simply set
    // the next frame time to the desired duration from now.
    frame_time = current_time + FRAME_DURATION;
  }
}

// This is called likely more than every 30th of a second.
void loop()
{
  // Delay until we're ready to animate the next frame. Should be no more 
  // than the frame duration (1/30 of a second).
  wait_for_time();
  // Animate the LED strip itself by filling in the frame buffer with new
  // CRGB color values.
  animate_strip();
  // This drives the frame_buffer onto the LED strip.
 	FastLED.show();
}
