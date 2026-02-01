#include "display.h"

#include "textBoard.h"
#include "mandel.h"
#include "gol.h"

Display::Display()
: pixel_board_{}, effect_boards_{
    new TextBoard<8, 16> { pixel_board_ },
    new MandelBoard { pixel_board_ },
    new GolBoard { pixel_board_ } }
{
}


void Display::reset()
{
    pixel_board_.reset();
    get_effect()->reset();
}

void Display::animate([[maybe_unused]] long ticks)
{
    get_effect()->animate(ticks);
    if (get_effect()->should_stop())
    {
        current_effect_ = (current_effect_ + 1) % effect_boards_.size();
        get_effect()->reset();
    }
}

void Display::render()
{
    get_effect()->render();
}

Display display;

