#include "display.h"

#define COLOR(bg, fg) ColorPair {static_cast<uint8_t>(Color::bg), static_cast<uint8_t>(Color::fg)}

Display::Display()
: pixel_board_{}, text_board_8x16_{pixel_board_}, mandel_board_{pixel_board_}
{
}

void Display::reset()
{
    [[maybe_unused]] std::array<ColorPair, 8> failMsgColors = { {
        COLOR(BLACK, WHITE),
        COLOR(BLACK, RED),
        COLOR(BLACK, RED),
        COLOR(BLACK, RED),
        COLOR(BLACK, RED),
        COLOR(BLACK, RED),
        COLOR(BLACK, RED),
        COLOR(BLACK, WHITE)
    } };

    [[maybe_unused]] std::array<ColorPair, 8> okMsgColors { {
        COLOR(BLACK, WHITE),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, GREEN),
        COLOR(BLACK, WHITE)
    } };

    pixel_board_.reset();
    text_board_8x16_.reset();
    text_board_8x16_.append_string("[FAILED]", failMsgColors);
    text_board_8x16_.append_string("[  OK  ]", okMsgColors);
    text_board_8x16_.append_string("[SALMON]", failMsgColors);
    mandel_board_.reset();
}

void Display::animate(long ticks)
{
    //text_board_8x16_.animate(ticks);
    mandel_board_.animate(ticks);
}

void Display::render()
{
    //text_board_8x16_.render();
    mandel_board_.render();
}

Display display;

