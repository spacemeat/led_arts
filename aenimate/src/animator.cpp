#include "animator.hpp"
#include "system.hpp"

Animator::Animator() {}

void Animator::wait_for_frame() {
  auto time = _time;
  while (time - _prev_time < FramePeriodInMs) {
    time = millis();
  }
}

void Animator::tick() {
  _prev_time = _time;
  _time = millis();

  for (int i = 0; i < _animations.size(); ++i) {
    _animations[i]->animate(_time, _time - _prev_time);
  }
}

Animator animator;
