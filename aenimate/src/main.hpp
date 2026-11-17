#ifndef MAIN_h
#define MAIN_h

#include <algorithm>
#include <array>

#include "animator.hpp"
#include "display.hpp"
#include "vein.hpp"

template <class Emit> constexpr void make_segments(Emit emit) {
  int id = 0;
  int parentId = 0;
  int parent_pixel_offset = 0;
  int frame_buffer_start = 0;
  int branch_depth = 1;
  emit(id, parentId, 0, 0, 1, 255);
  id = 1;
  parentId = 0;
  branch_depth += 1;
  parent_pixel_offset = 20;
  emit(id, parentId, branch_depth, // parent_pixel_offset,
       frame_buffer_start + parent_pixel_offset, 50, 255 - 16 / branch_depth);
  id = 2;
  parent_pixel_offset = 30;
  emit(id, parentId, branch_depth, // parent_pixel_offset,
       frame_buffer_start + parent_pixel_offset, 50, 255 - 16 / branch_depth);
  id = 3;
  parentId = 1;
  branch_depth += 1;
  frame_buffer_start = 20;
  parent_pixel_offset = 10;
  emit(id, parentId, branch_depth, // parent_pixel_offset,
       frame_buffer_start + parent_pixel_offset, 40, 255 - 16 / branch_depth);
  id = 4;
  parentId = 2;
  frame_buffer_start = 30;
  parent_pixel_offset = 15;
  emit(id, parentId, branch_depth, // parent_pixel_offset,
       frame_buffer_start + parent_pixel_offset, 30, 255 - 16 / branch_depth);
  id = 5;
  parentId = 3;
  branch_depth += 1;
  frame_buffer_start = 20;
  parent_pixel_offset = 5;
  emit(id, parentId, branch_depth, // parent_pixel_offset,
       frame_buffer_start + parent_pixel_offset, 25, 255 - 16 / branch_depth);
}

constexpr std::size_t num_segments() {
  std::size_t n = 0;
  make_segments([&](int, int, int, int, int, int) { ++n; });
  return n;
}

constexpr int num_leds() {
  int t = 0;
  make_segments([&](int, int, int, int frame_buffer_start, int length, int) {
    if (frame_buffer_start + length > t) {
      t = frame_buffer_start + length;
    }
  });
  return t;
}

inline CRGB frame_buffer[num_leds()];

inline Vein segment_buffer[num_segments()];

constexpr void build_segments() {
  // std::array<Vein, num_segments()> out{};
  size_t i = 0;
  make_segments([&](int id, int parent_id, int branch_depth,
                    int frame_buffer_start, int length, int power) {
    segment_buffer[i++] =
        Vein{id, parent_id, branch_depth, frame_buffer_start, length, power};
  });
}

constexpr const int FramePeriod_pms = 32;
constexpr const int CycleLength_pms = 1024 * 3;

constexpr const float BubStart_nml = 0;
constexpr const float BubLength_nml = 1.0f / 5;
constexpr const float BuhStart_nml = BubStart_nml + BubLength_nml * 3.0f / 5;
constexpr const float BuhLength_nml = 1.0f / 5;
constexpr const float RbcStart_nml = BuhStart_nml + BuhLength_nml / 2;
constexpr const float RbcLength_nml = 1.0f / 2;
constexpr const float RbcSpeed = 3.0f;

constexpr const int NumRgbPins = 2;

using VeinDisplay = Display<num_leds(), Vein, num_segments(), NumRgbPins>;
using VeinAnimator = Animator<num_segments(), FramePeriod_pms>;

extern VeinDisplay display;
extern VeinAnimator animator;

/*
constexpr auto build_segments() {
  std::array<Vein, num_segments()> out{};
  size_t i = 0;
  make_segments([&](int id, int parent_id, int branch_depth,
                    int frame_buffer_start, int length, int power) {
    out[i++] =
        Vein{id, parent_id, branch_depth, frame_buffer_start, length, power};
  });
  return out;
}

inline constexpr auto segment_buffer = build_segments();
*/

template <int NumLeds, class Segment, int NumSegments, int NumRgbPins>
void Display<NumLeds, Segment, NumSegments, NumRgbPins>::reset() {
  for (int i = 0; i < num_leds(); ++i) {
    frame_buffer[i] = CRGB(255, 0, 0);
  }
}

// NOTE: _nml is 'normalized', which is the cycles as if the total
// CycleLength is one pseudosecond, or 1024 pms.
/*
constexpr const int BubStart_nml = 0;
constexpr const int BubLength_nml = 1024 / 5;
constexpr const int BuhStart_nml = BubStart_nml + BubLength_nml * 3 / 5;
constexpr const int BuhLength_nml = 1024 / 5;
constexpr const int RbcStart_nml = BuhStart_nml + BuhLength_nml / 2;
constexpr const int RbcLength_nml = 1024 / 2;
*/

template <int NumLeds, class Segment, int NumSegments, int NumRgbPins>
void Display<NumLeds, Segment, NumSegments, NumRgbPins>::animate(long time,
                                                                 long) {
  // [0, 1.0)
  auto cycle_nml = float(time % CycleLength_pms) / CycleLength_pms;

  // Animation cycle is complicated.
  // |--bub--|-----------------------------|
  // |-----|--buh--|-----------------------|
  // |---------|--rbc speeddown-----|------|

  // bub
  auto bub_nml = (cycle_nml - BubStart_nml) - BubLength_nml / 2;
  auto bub_val = -(bub_nml * bub_nml + 0.01f) * 100.0f;
  if (bub_val > 0) {
    // TODO: set bub val
  } else {
    // TODO: set bub val = 0
  }

  // buh
  auto buh_nml = (cycle_nml - BuhStart_nml) - BuhLength_nml / 2;
  auto buh_val = -(buh_nml * buh_nml + 0.01f) * 100.0f;
  if (buh_val > 0) {
    // TODO: set buh val
  } else {
    // TODO: set buh val = 0
  }

  // rbc
  auto rbc_nml = (cycle_nml - RbcStart_nml);
  float rbc_val = 0.0f;
  if (rbc_nml < RbcLength_nml) {
    rbc_val = ((cycle_nml - 1.0f) * (cycle_nml - 1.0f) * cycle_nml) / .14815f *
              RbcSpeed;
    int rbc_val_int = int(rbc_val);
    // TODO: move the rbc buffer rbc_val pixels
    std::ranges::copy_backward(frame_buffer, frame_buffer + rbc_val_int,
                               frame_buffer + num_leds() - 1);
    for (int i = 0; i < rbc_val_int; ++i) {
      // prepend a new rbc value
      frame_buffer[i] = CRGB(random(192) + 63, 0, 0);
    }
  }
}

template <int NumLeds, class Segment, int NumSegments, int NumRgbPins>
void Display<NumLeds, Segment, NumSegments, NumRgbPins>::render() {
  //
}

template <int NumLeds, class Segment, int NumSegments, int NumRgbPins>
void Display<NumLeds, Segment, NumSegments, NumRgbPins>::print_leds() {
  int w = _term_width;
  int h = _term_height;

  std::cout << off << clear_line << "w: " << w << "; h: " << h
            << " t:" << animator.get_time() << '\n';
  /*
  for (int t = 0; t < NumTentacles; ++t) {
    int fbs = display._octopus._tentacles[t]._frame_buffer_start;
    for (int l = 0; l < NumLedsPerTentacle; ++l) {
      CRGB const &rgb = frame_buffer[fbs + l];
      std::cout << "\e[38;2;" << (int)rgb.r << ";" << (int)rgb.g << ";"
                << (int)rgb.b << "m*";
      // if (l < 8) { std::cout << (int) rgb.r << "; " <<(int)  rgb.g << "; "
      // <<(int)  rgb.b << "      "; }
    }
    std::cout << '\n';
  }
  */
  std::cout << '\n';
}

void main_setup(int terminal_width = 0, int terminal_height = 0);

void main_loop();

#endif // #ifndef MAIN_h
