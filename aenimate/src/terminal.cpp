#ifndef ARDUINO

// #include "effects/effect.h"

int skipLines = NumTentacles * 3 + 12;

void report_effects() {
  std::cout << off << "\e[" << term_h - skipLines << ";" << 0 << "H";

  auto controller = display._octopus.get_controller();

  controller->report();
}

#endif
