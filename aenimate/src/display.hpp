#ifndef DISPLAY_h
#define DISPLAY_h

// #include <concepts>
#include <iostream>

#include "animated.hpp"
#include "hardware.hpp"
#include "system.hpp"

constexpr const long FramePeriodInMs = 1024 / 32;

CHSV makeRandomColor();
CHSV makeRandomColor(CHSV inContrastTo);

constexpr auto off = "\e[0m\e[48;2;0;0;0m";
constexpr auto clear_line = "\e[K";

struct LedSegment {
  constexpr LedSegment() {}
  constexpr LedSegment(int id, int led_start_idx, int num_leds, int max_power)
      : id{id}, led_start_idx{led_start_idx}, num_leds{num_leds},
        max_power{max_power} {}
  int id = -1;
  int led_start_idx = -1;
  int num_leds = -1;
  int max_power = -1;
};

template <int NumLeds, class Segment, int NumSegments, int NumRgbPins>
// TODO: requires std::derived_from<Segment, LedSegment>
class Display : public Animated {
public:
  Display(CRGB *frame_buffer, Segment *segment_buffer)
      : _frame_buffer{frame_buffer}, _segment_buffer{segment_buffer} {}
  void set_term_extents(int term_width = 0, int term_height = 0) {
    _term_width = term_width;
    _term_height = term_height;
  }
  void add_segment(Segment const &segment) {
    if (segment.idx < NumSegments) {
      setup_led_segment(segment.idx, segment.led_start_idx, segment.num_leds);
    }
  }
  void reset() override;
  void animate(long time, long ticks) override;
  void render() override;
  void present() {
#ifdef ARDUINO
    FastLED.show();
#else
    print_leds();
#endif
  }

private:
  void print_leds();

  CRGB *_frame_buffer = nullptr;

  Segment *_segment_buffer = nullptr;

  int _term_width = 0;
  int _term_height = 0;
};

// template <int NumLeds, class Segment, int NumSegments>
//  TODO: requires std::derived_from<Segment, LedSegment>
// using LedDisplay = Display<NumLeds, Segment, NumSegments>;

// constexpr const int NumLeds = 60 * 3;

#endif // #ifndef DISPLAY_h
