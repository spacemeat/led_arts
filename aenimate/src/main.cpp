#include "main.hpp"

VeinDisplay veins{frame_buffer, &segment_buffer[0]};
VeinAnimator animator;

void main_setup(int term_width, int term_height) {
  veins.set_term_extents(term_width, term_height);
  veins.reset();
  animator.set_animation(0, &veins);

  // for (int i = 0; i < skipLines; ++i) {
  //  std::cout << '\n';
  //}
}

void main_loop() {
  animator.wait_for_frame();
  animator.tick();
  veins.present();
}
