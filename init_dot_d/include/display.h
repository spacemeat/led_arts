#pragma once

#include "frame.h"


class Display
{
public:
    Display();
    PixelBoard & get_pixel_board() { return pixel_board_; }
    EffectBoard * get_effect() { return effect_boards_[current_effect_]; }
    EffectBoard * get_effect(int idx) { return effect_boards_[idx % effect_boards_.size()]; }
    void reset();
    void animate(long ticks);
    void render();

private:

    PixelBoard pixel_board_;
    std::array<EffectBoard *, 3> effect_boards_;
    int current_effect_ = {};
    long current_effect_time_ = {};
};


