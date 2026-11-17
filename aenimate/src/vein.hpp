#ifndef VEIN_H
#define VEIN_H

#include "display.hpp"

constexpr const long NumVeins = 8;

struct Vein : public LedSegment {
  constexpr Vein() : LedSegment{} {}
  constexpr Vein(int id, int parent_id, [[maybe_unused]] int branch_depth,
                 int led_start_idx, int num_leds, int max_power)
      : LedSegment{id, led_start_idx, num_leds, max_power},
        parent_id{parent_id} {}

  int id = -1;
  int led_start_idx = 0;

  int parent_id = -1;
  int branch_depth = 1;
  int num_leds = 0;
};

#endif // #ifndef VEIN_H
