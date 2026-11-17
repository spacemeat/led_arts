#ifndef ANIMATOR_h
#define ANIMATOR_h

#include <array>

#include "animated.hpp"
#include "system.hpp"

// Animator

template <int NumAnimations, int FramePeriodInMs>
//
class Animator {
public:
  Animator() {}
  void wait_for_frame() {
    auto time = _time;
    while (time - _prev_time < FramePeriodInMs) {
      time = millis();
    }
  }
  void tick() {
    _prev_time = _time;
    _time = millis();

    for (size_t i = 0; i < _animations.size(); ++i) {
      _animations[i]->animate(_time, _time - _prev_time);
    }
  }

  long get_time() { return _time; }
  long get_prev_time() { return _prev_time; }

  void set_animation(int idx, Animated *animation) {
    if (idx >= 0 && idx < NumAnimations) {
      _animations[idx] = animation;
    }
  }

private:
  long _time = 0;
  long _prev_time = 0;

  std::array<Animated *, NumAnimations> _animations;
};

#endif // #ifndef ANIMATOR_h
