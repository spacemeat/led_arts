#include <FastLED.h>

// ----- Pinouts
const int LED_STRIP0 = 13;

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

// ----- Animation setup -----
const int LEDS_PER_SEGMENT = 15;
const int NUM_SEGMENTS = LEDS_PER_STRIP / LEDS_PER_SEGMENT;
const long TRANSITION_DURATION = 1500;  // 1.5 second transition duration
const long MIN_COLOR_DURATION = 5000; // Once finished, a transitioned color
const long MAX_COLOR_DURATION = 10000; // stays for 5-10 seconds.

const int OLD_COLOR = 0;
const int NEW_COLOR = 1;

struct Segment
{
  CRGB colors_[2];
  long transition_start_time_;
};

Segment segments[NUM_SEGMENTS];



// This is called once when the board powers on.
void setup()
{
  // Set up the FastLED array.
  FastLED.addLeds<WS2812B, LED_STRIP0, GRB>(frame_buffer, LEDS_PER_STRIP);
  memset(frame_buffer, 0, sizeof(CRGB) * LEDS_PER_STRIP);

  // Initialize the timing.
  current_time = millis();
  frame_time = current_time;

  // Set up pseudorandom number generation.

  for (int seg = 0; seg < NUM_SEGMENTS; ++seg)
  {
    segments[seg].colors_[OLD_COLOR] = CRGB(0, 0, 0);
    segments[seg].colors_[OLD_COLOR] = make_random_color();
  }
}

// This just blinks the microcontroller's on-board LED.
void animate_on_board_led()
{
  // TODO: blink the LED pin
}

// Returns a random color, within a range of saturation and at a particular brightness.
CRGB make_random_color()
{
  CHSV hsv(random(256),         // Anywhere on the hue wheel
           random(127) + 128,   // Somewhere between half and full saturation
           127);                // Always half brightness.
  return CRGB(hsv);
}

// Returns a random duration between the max and min.
long make_random_duration()
{
  return random(MAX_COLOR_DURATION - MIN_COLOR_DURATION) // 0s - 5s
              + MIN_COLOR_DURATION;                      // + 5s
                                                         // == 5s - 10s
}

// This is called every 30th of a second from loop().
void animate_strip()
{
  // Draw colors for each segment into the frame buffer.
  for (int seg = 0; seg < NUM_SEGMENTS; ++seg)
  {
    long transition_start_time = segments[seg].transition_start_time_;
    long transition_end_time = transition_start_time + TRANSITION_DURATION;

    int num_new_color_leds = 0;

    // If we're past the transition start time for this segment, we draw
    // with the new color for some of it, and the old color for the rest.
    if (current_time >= transition_start_time)
    {
      // Figure out the portion of the segment that gets drawn with new color.
      // This results in a float value from 0.0 - 1.0.
      float portion = (transition_end_time - transition_start_time) / 
            (current_time - transition_start_time);
      num_new_color_leds = portion * LEDS_PER_SEGMENT;
    }

    // Draw new colors, then old colors.

    // Each segment starts at a particular place in the frame buffer.
    int first_led_index = LEDS_PER_SEGMENT * seg;
    // During the 'duration', this loop will iterate zero times. Nothing wrong with that.
    for (int led_idx = 0; led_idx < num_new_color_leds; ++led_idx)
    {
      // Where in the patch we are painting.
      int idx_mod = first_led_index + led_idx;
      // Reverse direction on a random condition.
      if (transition_end_time % 2 == 1)
      {
        // Counting down from the end of the path to the beginning.
        idx_mod = (first_led_index + LEDS_PER_SEGMENT - 1) - idx_mod;
      }
      // Paint the color.
      frame_buffer[idx_mod] = segments[seg].colors_[NEW_COLOR];
    }
    for (int led_idx = num_new_color_leds; led_idx < LEDS_PER_SEGMENT; ++led_idx)
    {
      // Where in the patch we are painting.
      int idx_mod = first_led_index + led_idx;
      // Reverse direction on a random condition.
      if (transition_end_time % 2 == 1)
      {
        // Counting down from the end of the path to the beginning.
        idx_mod = (first_led_index + LEDS_PER_SEGMENT - 1) - idx_mod;
      }
      // Paint the color.
      frame_buffer[idx_mod] = segments[seg].colors_[OLD_COLOR];
    }

    // If the segment has fully transitioned, set it up for the next transition.
    if (current_time > transition_end_time)
    {
      // The old color becomes the new color.
      segments[seg].colors_[0] = segments[seg].colors_[1];
      // The new color becomes a pseudorandom color.
      segments[seg].colors_[1] = make_random_color();
      // The next transition occurs between the min an max color durations.
      segments[seg].transition_start_time_ = make_random_duration();
    }
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
  // Blink the on-board LED, to indicate that no matter what the strip is
  // doing, we can see that the loop is running.
  animate_on_board_led();
  // Animate the LED strip itself by filling in the frame buffer with new
  // CRGB color values.
  animate_strip();
  // This drives the frame_buffer onto the LED strip.
 	FastLED.show();
}
